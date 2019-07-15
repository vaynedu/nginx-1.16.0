
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_SHA1_H_INCLUDED_
#define _NGX_SHA1_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


/*
 *
 * ngx_sha1 和 ngx_md5 都是用来计算消息摘要
 *
 *
 * 只不过ngx_sha1 更安全，因为sha1有20个字节
 *
 * echo -n "1234" | md5sum
 * 81dc9bdb52d04dc20036dbd8313ed055
 *
 * echo -n "1234" | sha1sum 
 * 7110eda4d09e062aa5e4a390b0a572ac0d2c0220
 *
 * 具体使用可参考myexercise/myngx_md5目录下的练习代码
 *
 * 
 * md5 和 sha1 具体的实现原理有时间在研究下 
 *
 *
 * */



typedef struct {
    uint64_t  bytes;
    uint32_t  a, b, c, d, e, f;
    u_char    buffer[64];
} ngx_sha1_t;


void ngx_sha1_init(ngx_sha1_t *ctx);
void ngx_sha1_update(ngx_sha1_t *ctx, const void *data, size_t size);
void ngx_sha1_final(u_char result[20], ngx_sha1_t *ctx);


#endif /* _NGX_SHA1_H_INCLUDED_ */
