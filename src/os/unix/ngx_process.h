
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_PROCESS_H_INCLUDED_
#define _NGX_PROCESS_H_INCLUDED_


#include <ngx_setaffinity.h>
#include <ngx_setproctitle.h>


typedef pid_t       ngx_pid_t;

#define NGX_INVALID_PID  -1

typedef void (*ngx_spawn_proc_pt) (ngx_cycle_t *cycle, void *data);

typedef struct {
    ngx_pid_t           pid; /* 进程pid */
    int                 status; /* 进程状态，waitpid调用获取 */
	/* 基于匿名socket的进程之间通信的管道，由socketpair创建，并通过fork复制给子进程。
	 * 但一般是单向通信，channel[0]只用来写，channel[1]只用来读。
	 * */
    ngx_socket_t        channel[2];

    ngx_spawn_proc_pt   proc;/*子进程的循环方法，比如worker进程是ngx_worker_process_cycle*/
    void               *data;/*fork子进程后，会执行proc(cycle,data)*/
    char               *name;/*进程名称*/

    unsigned            respawn:1; /*为1时表示受master管理的子进程，死掉可以复活*/
    unsigned            just_spawn:1; /*为1时表示刚刚新fork的子进程，在重新加载配置文件时，会使用到*/
	/*为1时表示游离的新的子进程，一般用在升级binary时，
	 *会fork一个新的master子进程，这时新master进程是detached，不受原来的master进程管理
	 */
    unsigned            detached:1; 
    unsigned            exiting:1; /*为1时表示正在主动退出，一般收到SIGQUIT或SIGTERM信号后，会置该值为1，区别于子进程的异常被动退出*/
    unsigned            exited:1; /*为1时表示进程已退出，并通过waitpid系统调用回收*/
} ngx_process_t;


typedef struct {
    char         *path;
    char         *name;
    char *const  *argv;
    char *const  *envp;
} ngx_exec_ctx_t;


#define NGX_MAX_PROCESSES         1024

/* 子进程退出时,父进程不会再次创建(在创建cache loader process时使用) */
#define NGX_PROCESS_NORESPAWN     -1
/* 区别旧/新进程的标识位 */
#define NGX_PROCESS_JUST_SPAWN    -2
/*子进程异常退出时,父进程重新生成子进程的标识位 */
#define NGX_PROCESS_RESPAWN       -3
#define NGX_PROCESS_JUST_RESPAWN  -4
/*热代码替换,父、子进程分离的标识位*/
#define NGX_PROCESS_DETACHED      -5


#define ngx_getpid   getpid
#define ngx_getppid  getppid

#ifndef ngx_log_pid
#define ngx_log_pid  ngx_pid
#endif


ngx_pid_t ngx_spawn_process(ngx_cycle_t *cycle,
    ngx_spawn_proc_pt proc, void *data, char *name, ngx_int_t respawn);
ngx_pid_t ngx_execute(ngx_cycle_t *cycle, ngx_exec_ctx_t *ctx);
ngx_int_t ngx_init_signals(ngx_log_t *log);
void ngx_debug_point(void);


#if (NGX_HAVE_SCHED_YIELD)
#define ngx_sched_yield()  sched_yield()
#else
#define ngx_sched_yield()  usleep(1)
#endif


extern int            ngx_argc;
extern char         **ngx_argv;
extern char         **ngx_os_argv;

extern ngx_pid_t      ngx_pid;
extern ngx_pid_t      ngx_parent;
extern ngx_socket_t   ngx_channel;
extern ngx_int_t      ngx_process_slot;
extern ngx_int_t      ngx_last_process;
extern ngx_process_t  ngx_processes[NGX_MAX_PROCESSES];


#endif /* _NGX_PROCESS_H_INCLUDED_ */
