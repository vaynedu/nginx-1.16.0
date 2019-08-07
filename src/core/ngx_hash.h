
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_HASH_H_INCLUDED_
#define _NGX_HASH_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


/* 基本哈希表的元素 */
typedef struct {
    void             *value; //即为key-value中对应的value
    u_short           len;   //为key-value中key的长度
   /*
    * name[1]为key的首地址
    * 这里是非常重要的一个技巧，C语言的柔性数组(可变长数组)
    * 可以申请一段连续的空间
    */
    u_char            name[1]; 
} ngx_hash_elt_t;


/* 基本哈希表结构 */
typedef struct {
    ngx_hash_elt_t  **buckets; //哈希表的首地址
    ngx_uint_t        size; //哈希表中bucket的个数
} ngx_hash_t;


/* 支持通配符的哈希表结构 */
typedef struct {
    ngx_hash_t        hash;
    void             *value;
} ngx_hash_wildcard_t;


/*
 * 保存hash数据，键值对
 *
 * 一般将多个键-值对保存在ngx_hash_key_t结构的数组中
 *
 * vaynedu没有懂
 *
 * */
typedef struct {
    ngx_str_t         key;
    //由哈希函数根据key计算出的值. 将来此元素代表的结构体会被插入bucket[key_hash % size] 
    ngx_uint_t        key_hash;
    void             *value;
} ngx_hash_key_t;


typedef ngx_uint_t (*ngx_hash_key_pt) (u_char *data, size_t len);


/* 组合类型哈希表 */
typedef struct {
    ngx_hash_t            hash;
    ngx_hash_wildcard_t  *wc_head; // 前置通配符的hash表 aa.bb.*
    ngx_hash_wildcard_t  *wc_tail; // 后置通配符的hash表 *.com
} ngx_hash_combined_t;


/* 哈希表初始化使用的结构体*/
typedef struct {
    ngx_hash_t       *hash;
    ngx_hash_key_pt   key; // hash方法的函数指针

    ngx_uint_t        max_size; // 最大槽位
    ngx_uint_t        bucket_size; // 每个槽位的大小，这就限制了关键字的最大长度

    char             *name; // hash表的名称
    ngx_pool_t       *pool;
	/*
	 * temp_pool 分配实际hash桶的时候，预算需要多少个hash桶
	 *
	 * 非常精妙的代码
	 *
	 * */
    ngx_pool_t       *temp_pool;
} ngx_hash_init_t;


#define NGX_HASH_SMALL            1
#define NGX_HASH_LARGE            2

#define NGX_HASH_LARGE_ASIZE      16384
#define NGX_HASH_LARGE_HSIZE      10007

#define NGX_HASH_WILDCARD_KEY     1
#define NGX_HASH_READONLY_KEY     2


typedef struct {
    ngx_uint_t        hsize;

    ngx_pool_t       *pool;
    ngx_pool_t       *temp_pool;

    ngx_array_t       keys; //存放所有完全匹配的key的数组
    ngx_array_t      *keys_hash;

    ngx_array_t       dns_wc_head; // 存放前置泛域名字符串，泛域名部分会被去掉
    ngx_array_t      *dns_wc_head_hash;

    ngx_array_t       dns_wc_tail; // 存放后置泛域名字符串，泛域名部分会被去掉
    ngx_array_t      *dns_wc_tail_hash;
} ngx_hash_keys_arrays_t;


/*
 * ngx_table_elt_t 主要用来存储HTTP的header头部
 *
 *  比如该头部： Content-Type: text/plain
 *  按照下列方式存储
 *  key ： Content-Type 
 *  value ： text/plain
 *  
 *
 * */

typedef struct {
    /*  hash用于快速检索头部，这个还在熟悉，查询资料hash这个还是重点:
     *  h->hash = r->header_hash;
     *  hash赋值在ngx_http_parse_header_line函数中，根据请求的头部key\value整个计算hash
     *   
     *  #define ngx_hash(key, c)   ((ngx_uint_t) key * 31 + c) 
     *
     *  hash这个还在熟悉，查询资料hash这个还是重点: 
     *
     */  
    ngx_uint_t        hash; 
    ngx_str_t         key;
    ngx_str_t         value;
    /*存放的是本结构体中key的小写字母字符串, 可以理解为忽略大小写来处理*/
    u_char           *lowcase_key; 
} ngx_table_elt_t;


void *ngx_hash_find(ngx_hash_t *hash, ngx_uint_t key, u_char *name, size_t len);
void *ngx_hash_find_wc_head(ngx_hash_wildcard_t *hwc, u_char *name, size_t len);
void *ngx_hash_find_wc_tail(ngx_hash_wildcard_t *hwc, u_char *name, size_t len);
void *ngx_hash_find_combined(ngx_hash_combined_t *hash, ngx_uint_t key,
    u_char *name, size_t len);

ngx_int_t ngx_hash_init(ngx_hash_init_t *hinit, ngx_hash_key_t *names,
    ngx_uint_t nelts);
ngx_int_t ngx_hash_wildcard_init(ngx_hash_init_t *hinit, ngx_hash_key_t *names,
    ngx_uint_t nelts);

#define ngx_hash(key, c)   ((ngx_uint_t) key * 31 + c)
ngx_uint_t ngx_hash_key(u_char *data, size_t len);
ngx_uint_t ngx_hash_key_lc(u_char *data, size_t len);
ngx_uint_t ngx_hash_strlow(u_char *dst, u_char *src, size_t n);


ngx_int_t ngx_hash_keys_array_init(ngx_hash_keys_arrays_t *ha, ngx_uint_t type);
ngx_int_t ngx_hash_add_key(ngx_hash_keys_arrays_t *ha, ngx_str_t *key,
    void *value, ngx_uint_t flags);


#endif /* _NGX_HASH_H_INCLUDED_ */
