
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


/*
 * find the middle queue element if the queue has odd number of elements
 * or the first element of the queue's second part otherwise
 */


/*
 *  return : 返回队列链表中心元素
 * */
ngx_queue_t *
ngx_queue_middle(ngx_queue_t *queue)
{
    ngx_queue_t  *middle, *next;

    middle = ngx_queue_head(queue);

    if (middle == ngx_queue_last(queue)) {
        return middle;
    }

    next = ngx_queue_head(queue);


	/*
	 * 思想很简单， middle指针每次一定一位
	 * next指针每次移动两位，这样就找到了中间节点
	 *
	 * */
    for ( ;; ) {
        middle = ngx_queue_next(middle);

        next = ngx_queue_next(next);

		/* 队列链表有偶数个元素
		 *
		 * 这里是包括head节点计算的
		 * */
        if (next == ngx_queue_last(queue)) {
            return middle;
        }

        next = ngx_queue_next(next);

		/* 队列链表有奇数个元素
		 *
		 * 这里是包括head节点计算的
		 * */
        if (next == ngx_queue_last(queue)) {
            return middle;
        }
    }
}


/* the stable insertion sort */

/*
 * 对列表进行排序
 *
 * 从头遍历链表，每次拿出一个元素，剔除，找到一个合适的位置，插入
 *
 * cmp 是函数指针， 选择从大到小排序还是从小到大排序
 *
 * */
void
ngx_queue_sort(ngx_queue_t *queue,
    ngx_int_t (*cmp)(const ngx_queue_t *, const ngx_queue_t *))
{
    ngx_queue_t  *q, *prev, *next;

    q = ngx_queue_head(queue);

    if (q == ngx_queue_last(queue)) {
        return;
    }

    for (q = ngx_queue_next(q); q != ngx_queue_sentinel(queue); q = next) {

        prev = ngx_queue_prev(q);
        next = ngx_queue_next(q);

        ngx_queue_remove(q);

        do {
            if (cmp(prev, q) <= 0) {
                break;
            }

            prev = ngx_queue_prev(prev);

        } while (prev != ngx_queue_sentinel(queue));

        ngx_queue_insert_after(prev, q);
    }
}
