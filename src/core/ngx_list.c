
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>

/*
 * 个人觉得nginx的list链表的方法很少
 *
 * 只有增加，没有修改和删除，也没有插入的方式（从前面插还是从后面插）
 *
 * 使用场景暂时不清楚 unclear_code_flag
 *
 * */




ngx_list_t *
ngx_list_create(ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    ngx_list_t  *list;

    list = ngx_palloc(pool, sizeof(ngx_list_t));
    if (list == NULL) {
        return NULL;
    }

    if (ngx_list_init(list, pool, n, size) != NGX_OK) {
        return NULL;
    }

    return list;
}


/* 
 * ngx_list_push 在链表中添加一个元素
 *
 * ngx_list_push 和 ngx_array_push特别相似
 *
 *  先判断列表是否“已满”。 满的话在申请一个list，挂在之前的list的上
 *
 *  不满的情况下直接分配中一个就行，代码特别简单 
 *
 * */
void *
ngx_list_push(ngx_list_t *l)
{
    void             *elt;
    ngx_list_part_t  *last;

    last = l->last;

    if (last->nelts == l->nalloc) {

        /* the last part is full, allocate a new list part */

        last = ngx_palloc(l->pool, sizeof(ngx_list_part_t));
        if (last == NULL) {
            return NULL;
        }

        last->elts = ngx_palloc(l->pool, l->nalloc * l->size);
        if (last->elts == NULL) {
            return NULL;
        }

        last->nelts = 0;
        last->next = NULL;

        l->last->next = last;
        l->last = last;
    }

    elt = (char *) last->elts + l->size * last->nelts;
    last->nelts++;

    return elt;
}
