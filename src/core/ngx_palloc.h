
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_PALLOC_H_INCLUDED_
#define _NGX_PALLOC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


/*
 * NGX_MAX_ALLOC_FROM_POOL should be (ngx_pagesize - 1), i.e. 4095 on x86.
 * On Windows NT it decreases a number of locked pages in a kernel.
 */
#define NGX_MAX_ALLOC_FROM_POOL  (ngx_pagesize - 1)

#define NGX_DEFAULT_POOL_SIZE    (16 * 1024)

#define NGX_POOL_ALIGNMENT       16
#define NGX_MIN_POOL_SIZE                                                     \
    ngx_align((sizeof(ngx_pool_t) + 2 * sizeof(ngx_pool_large_t)),            \
              NGX_POOL_ALIGNMENT)


typedef void (*ngx_pool_cleanup_pt)(void *data);

typedef struct ngx_pool_cleanup_s  ngx_pool_cleanup_t;

struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt   handler; /* 自定义清理回收空间的函数指针*/ 
    void                 *data; /* 指向要清除的数据*/
    ngx_pool_cleanup_t   *next; 
};


typedef struct ngx_pool_large_s  ngx_pool_large_t;

/*
 * 分配大内存
 * */
struct ngx_pool_large_s {
    ngx_pool_large_t     *next;
    void                 *alloc;
};

/*
 * ngx_pool_data_t 内存池的数据块位置信息
 *
 */

typedef struct {
    u_char               *last; // 当前内存池分配到此处，即下一次分配从此处开始
    u_char               *end;  // 内存池结束位置
    ngx_pool_t           *next; // 内存池里面很多内存块，这些内存块就是通过该指针连成链表的
    ngx_uint_t            failed; //内存池分配失败次数
} ngx_pool_data_t;


/*
 * ngx_pool_s 内存池头部
 *
 */
struct ngx_pool_s {
    ngx_pool_data_t       d;   //内存池的数据块
    size_t                max; // 内存池数据块最大值
    ngx_pool_t           *current; // 指向当前的内存池
    ngx_chain_t          *chain;  // unclear_code_flag
    ngx_pool_large_t     *large;   //大块内存链表，即分配空间超过max的内存
    ngx_pool_cleanup_t   *cleanup; //析构函数，释放内存池的callback
    ngx_log_t            *log; 
};


/* 非常重的数据结构，目前还没有接触到,后期接触了在补上*/
typedef struct {
    ngx_fd_t              fd;
    u_char               *name;
    ngx_log_t            *log;
} ngx_pool_cleanup_file_t;


ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log);
void ngx_destroy_pool(ngx_pool_t *pool);
void ngx_reset_pool(ngx_pool_t *pool);

void *ngx_palloc(ngx_pool_t *pool, size_t size);
void *ngx_pnalloc(ngx_pool_t *pool, size_t size);
void *ngx_pcalloc(ngx_pool_t *pool, size_t size);
void *ngx_pmemalign(ngx_pool_t *pool, size_t size, size_t alignment);
ngx_int_t ngx_pfree(ngx_pool_t *pool, void *p);


ngx_pool_cleanup_t *ngx_pool_cleanup_add(ngx_pool_t *p, size_t size);
void ngx_pool_run_cleanup_file(ngx_pool_t *p, ngx_fd_t fd);
void ngx_pool_cleanup_file(void *data);
void ngx_pool_delete_file(void *data);


#endif /* _NGX_PALLOC_H_INCLUDED_ */
