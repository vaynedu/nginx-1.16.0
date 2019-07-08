#include <stdio.h>

#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"


/*
 * 参考如下网址，谢谢阿波作者的无私分享
 *
 * https://blog.csdn.net/livelylittlefish/article/details/6586946
 *
 */


/* 
 * 下面的定义和函数主要解决依赖问题，否则不能正常编译
 *
 * /data4/nginx-1.16.0/src/core/ngx_string.c:1991: undefined reference to `ngx_cycle'
 */
volatile ngx_cycle_t  *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
    //pass
}



void dump_pool(ngx_pool_t* pool)
{
    while (pool)
    {
        printf("sizeof(ngx_pool_t) = %ui\n", sizeof(ngx_pool_t));    
        printf("pool = 0x%x\n", pool);
        printf("  .d\n");
        printf("    .last = 0x%x\n", pool->d.last);
        printf("    .end = 0x%x\n", pool->d.end);
        printf("    .next = 0x%x\n", pool->d.next);
        printf("    .failed = %d\n", pool->d.failed);
        printf("  .max = %d\n", pool->max);
        printf("  .current = 0x%x\n", pool->current);
        printf("  .chain = 0x%x\n", pool->chain);
        printf("  .large = 0x%x\n", pool->large);
        printf("  .cleanup = 0x%x\n", pool->cleanup);
        printf("  .log = 0x%x\n", pool->log);
        printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
        pool = pool->d.next;
    }

}

int main()
{

    ngx_pool_t *pool = NULL; 
    
    // create pool
    pool = ngx_create_pool(1024, NULL);
    dump_pool(pool);    


    // ngx_palloc 
    ngx_str_t *name = ngx_palloc(pool, sizeof(ngx_str_t));
    dump_pool(pool);

    name->data = ngx_palloc(pool, sizeof("abc"));
    ngx_copy(name->data, "abc", sizeof("abc") -1);
    name->len = sizeof("abc") -1 ;
    printf("name : %s, len = %d\n", name->data, name->len);
    dump_pool(pool);
    
   
    // ngx_palloc
    ngx_palloc(pool, 512);
    dump_pool(pool);

    // ngx_reset_pool ：释放大块内存， 重新初始化ngx_pool_t内存池结构体，下次可以继续使用 
    ngx_reset_pool(pool);
    dump_pool(pool);

    // ngx_palloc
    ngx_palloc(pool, 512);
    dump_pool(pool);

    // ngx_destroy_pool ：删除整个内存池
    ngx_destroy_pool(pool);

    return 0;
}



