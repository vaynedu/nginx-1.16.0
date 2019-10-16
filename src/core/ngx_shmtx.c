
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


#if (NGX_HAVE_ATOMIC_OPS)


static void ngx_shmtx_wakeup(ngx_shmtx_t *mtx);


/*
 * 基于原子操作实现锁
 *
 * mtx： 要创建的锁
 * addr：创建锁时，内部用到的原子变量
 * name：没有意义，只有上
 *
 * */
ngx_int_t
ngx_shmtx_create(ngx_shmtx_t *mtx, ngx_shmtx_sh_t *addr, u_char *name)
{
	/*
	 * 保存原子变量的地址，由于锁时多个进程之间共享的，那么原子变量一般在共享内存进行分配
	 *上面的addr就表示在共享内存中分配的内存地址
	 * */
    mtx->lock = &addr->lock;

	/*
	 * 在不支持信号量时，spin只表示锁的自旋次数，那么该值为0或负数表示不进行自旋，直接让出cpu，
	 * 当支持信号量时，它为-1表示，不要使用信号量将进程置于睡眠状态，这对 nginx 的性能至关重要
	 * */
    if (mtx->spin == (ngx_uint_t) -1) {
        return NGX_OK;
    }

	/*默认自旋次数是2048*/
    mtx->spin = 2048;

	/*支持信号量，继续执行下面代码，主要是信号量的初始化。*/
#if (NGX_HAVE_POSIX_SEM)

    mtx->wait = &addr->wait;

	/* 初始化信号量，第二个参数1表示，信号量使用在多进程环境中，第三个参数0表示信号量的初始值
     * 当信号量的值小于等于0时，尝试等待信号量会阻塞
     * 信号量大于0时，尝试等待信号量会成功，并把信号量的值减一。
	 */
    if (sem_init(&mtx->sem, 1, 0) == -1) {
        ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, ngx_errno,
                      "sem_init() failed");
    } else {
        mtx->semaphore = 1;
    }

#endif

    return NGX_OK;
}


void
ngx_shmtx_destroy(ngx_shmtx_t *mtx)
{
#if (NGX_HAVE_POSIX_SEM)

    if (mtx->semaphore) {
        if (sem_destroy(&mtx->sem) == -1) {
            ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, ngx_errno,
                          "sem_destroy() failed");
        }
    }

#endif
}

/*
 * nginx多个进程之间是如何获得锁并释放锁
 *
 * 在nginx中进程获取锁有两种方式，一种是非阻塞的方式，另外一种是循环不停的获取锁直到获取锁
 *
 *
 * ngx_shmtx_trylock 在非阻塞的实现过程中，只要是未获取锁就会立即返回失败
 * */

ngx_uint_t
ngx_shmtx_trylock(ngx_shmtx_t *mtx)
{
	/*
	 * ngx_atomic_cmp_set函数是一个原子操作
	 *
	 * 如果lock的值为0，则将lock的值更改为当前进程的id，否则返回失败
	 * */
    return (*mtx->lock == 0 && ngx_atomic_cmp_set(mtx->lock, 0, ngx_pid));
}


void
ngx_shmtx_lock(ngx_shmtx_t *mtx)
{
    ngx_uint_t         i, n;

    ngx_log_debug0(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0, "shmtx lock");

    for ( ;; ) {

        if (*mtx->lock == 0 && ngx_atomic_cmp_set(mtx->lock, 0, ngx_pid)) {
            return;
        }

		/*多核cpu,如果无法获得锁,就死等待,要是还获取不到那就一直在for循环里面转圈圈
		 *
		 * ngx_cpu_pause 的 pause指令，x86汇编pause指令到底有什么用？
		 *
		 * 简单来说： PAUSE指令提升了自旋等待循环（spin-wait loop）的性能, 因为自旋锁特别消耗性能.
		 *
		 * 详情请看vaynedu的issue
		 * https://github.com/vaynedu/nginx-1.16.0/issues/48
		 * */
        if (ngx_ncpu > 1) {

            for (n = 1; n < mtx->spin; n <<= 1) {

                for (i = 0; i < n; i++) {
                    ngx_cpu_pause();
                }

                if (*mtx->lock == 0
                    && ngx_atomic_cmp_set(mtx->lock, 0, ngx_pid))
                {
                    return;
                }
            }
        }

#if (NGX_HAVE_POSIX_SEM)

        if (mtx->semaphore) {
            (void) ngx_atomic_fetch_add(mtx->wait, 1);

            if (*mtx->lock == 0 && ngx_atomic_cmp_set(mtx->lock, 0, ngx_pid)) {
                (void) ngx_atomic_fetch_add(mtx->wait, -1);
                return;
            }

            ngx_log_debug1(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0,
                           "shmtx wait %uA", *mtx->wait);

            while (sem_wait(&mtx->sem) == -1) {
                ngx_err_t  err;

                err = ngx_errno;

                if (err != NGX_EINTR) {
                    ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, err,
                                  "sem_wait() failed while waiting on shmtx");
                    break;
                }
            }

            ngx_log_debug0(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0,
                           "shmtx awoke");

            continue;
        }

#endif

		/* 主动让出CPU*/
        ngx_sched_yield();
    }
}


void
ngx_shmtx_unlock(ngx_shmtx_t *mtx)
{
    if (mtx->spin != (ngx_uint_t) -1) {
        ngx_log_debug0(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0, "shmtx unlock");
    }

	/*释放锁，将原子变量设为0，同时唤醒在信号量上等待的进程*/
    if (ngx_atomic_cmp_set(mtx->lock, ngx_pid, 0)) {
        ngx_shmtx_wakeup(mtx);
    }
}


ngx_uint_t
ngx_shmtx_force_unlock(ngx_shmtx_t *mtx, ngx_pid_t pid)
{
    ngx_log_debug0(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0,
                   "shmtx forced unlock");

    if (ngx_atomic_cmp_set(mtx->lock, pid, 0)) {
        ngx_shmtx_wakeup(mtx);
        return 1;
    }

    return 0;
}


static void
ngx_shmtx_wakeup(ngx_shmtx_t *mtx)
{

	/*如果不支持信号量，那么该函数为空，啥也不做*/
#if (NGX_HAVE_POSIX_SEM)
    ngx_atomic_uint_t  wait;

	/*如果没有使用信号量，直接返回*/
    if (!mtx->semaphore) {
        return;
    }

	/*将在信号量上等待的进程数减1，因为是多进程环境，ngx_atomic_cmp_set不一定能一次成功，所以需要循环调用*/
    for ( ;; ) {

        wait = *mtx->wait;

		/*wait 小于等于0，说明当前没有进程在信号量上睡眠*/
        if ((ngx_atomic_int_t) wait <= 0) {
            return;
        }

        if (ngx_atomic_cmp_set(mtx->wait, wait, wait - 1)) {
            break;
        }
    }

    ngx_log_debug1(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0,
                   "shmtx wake %uA", wait);

	/*将信号量的值加1*/
    if (sem_post(&mtx->sem) == -1) {
        ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, ngx_errno,
                      "sem_post() failed while wake shmtx");
    }

#endif
}


#else

/* 
 *  基于文件锁实现的锁
 * 
 *  mtx：要创建的锁
 *  addr：使用文件锁实现互斥锁时不会用到该变量
 *  name：文件锁使用的文件
 *
 * */
ngx_int_t
ngx_shmtx_create(ngx_shmtx_t *mtx, ngx_shmtx_sh_t *addr, u_char *name)
{
    if (mtx->name) { /*mtx->name不为NULL，说明它之前已经创建过锁*/
       
		/* 之前创建过锁，且与这次创建锁的文件相同，则不需要创建，直接返回*/
        if (ngx_strcmp(name, mtx->name) == 0) {
            mtx->name = name;
            return NGX_OK;
        }

		/*销毁之前创建到锁，其实就是关闭之前创建锁时打开的文件*/
        ngx_shmtx_destroy(mtx);
    }

    mtx->fd = ngx_open_file(name, NGX_FILE_RDWR, NGX_FILE_CREATE_OR_OPEN,
                            NGX_FILE_DEFAULT_ACCESS);

    if (mtx->fd == NGX_INVALID_FILE) {
        ngx_log_error(NGX_LOG_EMERG, ngx_cycle->log, ngx_errno,
                      ngx_open_file_n " \"%s\" failed", name);
        return NGX_ERROR;
    }

	/*使用锁时只需要该文件在内核中的inode信息，所以将该文件删掉*/
    if (ngx_delete_file(name) == NGX_FILE_ERROR) {
        ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, ngx_errno,
                      ngx_delete_file_n " \"%s\" failed", name);
    }

    mtx->name = name;

    return NGX_OK;
}


void
ngx_shmtx_destroy(ngx_shmtx_t *mtx)
{
    if (ngx_close_file(mtx->fd) == NGX_FILE_ERROR) {
        ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, ngx_errno,
                      ngx_close_file_n " \"%s\" failed", mtx->name);
    }
}

/*
 * 非阻塞锁的获取
 * */

ngx_uint_t
ngx_shmtx_trylock(ngx_shmtx_t *mtx)
{
    ngx_err_t  err;

    /*与阻塞版本比较，最主要的变化是将 ngx_lock_fd 函数换成了 ngx_trylock_fd*/
    err = ngx_trylock_fd(mtx->fd);

	/* 获取锁成功，返回1*/
    if (err == 0) {
        return 1;
    }

	/*获取锁失败，如果错误码是 NGX_EAGAIN，表示文件锁正被其他进程占用，返回0*/
    if (err == NGX_EAGAIN) {
        return 0;
    }

#if __osf__ /* Tru64 UNIX */

    if (err == NGX_EACCES) {
        return 0;
    }

#endif

	/*其他错误都不应该发生，打印错误日志*/
    ngx_log_abort(err, ngx_trylock_fd_n " %s failed", mtx->name);

    return 0;
}

/*
 * 阻塞锁的获取
 *
 * 通过文件锁的方式实现互斥锁，如果该文件锁正被其他进程占有，则会导致进程阻塞。*/
void
ngx_shmtx_lock(ngx_shmtx_t *mtx)
{
    ngx_err_t  err;

	/*通过获取文件锁来进行加锁*/
    err = ngx_lock_fd(mtx->fd);

    if (err == 0) {
        return;
    }

    ngx_log_abort(err, ngx_lock_fd_n " %s failed", mtx->name);
}


void
ngx_shmtx_unlock(ngx_shmtx_t *mtx)
{
    ngx_err_t  err;

	/*调用 ngx_unlock_fd函数释放锁*/
    err = ngx_unlock_fd(mtx->fd);

    if (err == 0) {
        return;
    }

    ngx_log_abort(err, ngx_unlock_fd_n " %s failed", mtx->name);
}


ngx_uint_t
ngx_shmtx_force_unlock(ngx_shmtx_t *mtx, ngx_pid_t pid)
{
    return 0;
}

#endif
