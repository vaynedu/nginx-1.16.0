
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_SHMTX_H_INCLUDED_
#define _NGX_SHMTX_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
	/*通过对该变量进行原子操作来进行锁的获取与释放*/
    ngx_atomic_t   lock;
#if (NGX_HAVE_POSIX_SEM)
	/*支持信号量时才会有变量，表示当前在在变量上等待的进程数目*/
    ngx_atomic_t   wait;
#endif
} ngx_shmtx_sh_t;


/*
 * nginx中实现锁的类型是通过宏来区分的，一共三种，原子和信号量还有共享文件
 *
 * */
typedef struct {
#if (NGX_HAVE_ATOMIC_OPS) /*原子锁*/
    ngx_atomic_t  *lock;  /*指向一个共享内存区域的地址*/
#if (NGX_HAVE_POSIX_SEM)  /*信号量*/
    ngx_atomic_t  *wait;
    ngx_uint_t     semaphore;
    sem_t          sem;
#endif
#else /*文件锁*/
    ngx_fd_t       fd;    /*进程间共享文件句柄*/
    u_char        *name;  /*文件名*/
#endif
    ngx_uint_t     spin;
} ngx_shmtx_t;


ngx_int_t ngx_shmtx_create(ngx_shmtx_t *mtx, ngx_shmtx_sh_t *addr,
    u_char *name);
void ngx_shmtx_destroy(ngx_shmtx_t *mtx);
ngx_uint_t ngx_shmtx_trylock(ngx_shmtx_t *mtx);
void ngx_shmtx_lock(ngx_shmtx_t *mtx);
void ngx_shmtx_unlock(ngx_shmtx_t *mtx);
ngx_uint_t ngx_shmtx_force_unlock(ngx_shmtx_t *mtx, ngx_pid_t pid);


#endif /* _NGX_SHMTX_H_INCLUDED_ */
