
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_CONNECTION_H_INCLUDED_
#define _NGX_CONNECTION_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct ngx_listening_s  ngx_listening_t;

struct ngx_listening_s {
    ngx_socket_t        fd;

    struct sockaddr    *sockaddr;
    socklen_t           socklen;    /* size of sockaddr */
    size_t              addr_text_max_len;
    ngx_str_t           addr_text;

    int                 type;

    int                 backlog;
    int                 rcvbuf;
    int                 sndbuf;
#if (NGX_HAVE_KEEPALIVE_TUNABLE)
    int                 keepidle;
    int                 keepintvl;
    int                 keepcnt;
#endif

    /* handler of accepted connection */
    ngx_connection_handler_pt   handler;

    void               *servers;  /* array of ngx_http_in_addr_t, for example */

    ngx_log_t           log;
    ngx_log_t          *logp;

    size_t              pool_size;
    /* should be here because of the AcceptEx() preread */
    size_t              post_accept_buffer_size;
    /* should be here because of the deferred accept */
    ngx_msec_t          post_accept_timeout;

    ngx_listening_t    *previous;
    ngx_connection_t   *connection;

    ngx_rbtree_t        rbtree;
    ngx_rbtree_node_t   sentinel;

    ngx_uint_t          worker;

    unsigned            open:1;
    unsigned            remain:1;
    unsigned            ignore:1;

    unsigned            bound:1;       /* already bound */
    unsigned            inherited:1;   /* inherited from previous process */
    unsigned            nonblocking_accept:1;
    unsigned            listen:1;
    unsigned            nonblocking:1;
    unsigned            shared:1;    /* shared between threads or processes */
    unsigned            addr_ntop:1;
    unsigned            wildcard:1;

#if (NGX_HAVE_INET6)
    unsigned            ipv6only:1;
#endif
    unsigned            reuseport:1;
    unsigned            add_reuseport:1;
    unsigned            keepalive:2;

    unsigned            deferred_accept:1;
    unsigned            delete_deferred:1;
    unsigned            add_deferred:1;
#if (NGX_HAVE_DEFERRED_ACCEPT && defined SO_ACCEPTFILTER)
    char               *accept_filter;
#endif
#if (NGX_HAVE_SETFIB)
    int                 setfib;
#endif

#if (NGX_HAVE_TCP_FASTOPEN)
    int                 fastopen;
#endif

};


typedef enum {
    NGX_ERROR_ALERT = 0,
    NGX_ERROR_ERR,
    NGX_ERROR_INFO,
    NGX_ERROR_IGNORE_ECONNRESET,
    NGX_ERROR_IGNORE_EINVAL
} ngx_connection_log_error_e;


typedef enum {
    NGX_TCP_NODELAY_UNSET = 0,
    NGX_TCP_NODELAY_SET,
    NGX_TCP_NODELAY_DISABLED
} ngx_connection_tcp_nodelay_e;


typedef enum {
    NGX_TCP_NOPUSH_UNSET = 0,
    NGX_TCP_NOPUSH_SET,
    NGX_TCP_NOPUSH_DISABLED
} ngx_connection_tcp_nopush_e;


#define NGX_LOWLEVEL_BUFFERED  0x0f
#define NGX_SSL_BUFFERED       0x01
#define NGX_HTTP_V2_BUFFERED   0x02

/* TCP连接结构体 */
struct ngx_connection_s {
    /* 当Nginx服务器产生新的socket时,都会创建一个ngx_connection_s 结构体，该结构体用于保存socket的属性和数据；*/

	/*
	 * 当连接未被使用时，data充当连接池中空闲连接表中的next指针；
	 * 当连接被使用时，data的意义由具体Nginx模块决定；
	 *
	 * */
    void               *data; /*用来关联其他的ngx_connection_s结构体*/
    ngx_event_t        *read; /*设置该连接的读事件*/
    ngx_event_t        *write;/*设置该连接的写事件*/

    ngx_socket_t        fd;  /*用于设置连接socket的socket描述字*/

	/*
	 * 指向完成（批量）数据接收函数的函数指针
	 * 指向完成（批量）数据发送函数的函数指针
	 *
	 * */
    ngx_recv_pt         recv;   
    ngx_send_pt         send;
    ngx_recv_chain_pt   recv_chain;
    ngx_send_chain_pt   send_chain;

	/*
	 * listening用于设置该网路连接的socket监听，它对应一个ngx_listening_s结构体
	 * 而该ngx_listening_s结构体中的*connection成员又将指向该ngx_connection_s结构体
	 *
	 *
	 * */
    ngx_listening_t    *listening;

    off_t               sent; /* 用于设置该连接已发送或者已接收数据的数量 */

    ngx_log_t          *log;

    ngx_pool_t         *pool;

    int                 type;

    struct sockaddr    *sockaddr; /*连接客户端的sockaddr结构体*/
    socklen_t           socklen;  /*连接 sockaddr结构体的 长度*/
    ngx_str_t           addr_text;/*连接客户端字符串形式的IP地址*/

    ngx_str_t           proxy_protocol_addr;
    in_port_t           proxy_protocol_port;

#if (NGX_SSL || NGX_COMPAT)
    ngx_ssl_connection_t  *ssl;
#endif

    ngx_udp_connection_t  *udp;

    struct sockaddr    *local_sockaddr;
    socklen_t           local_socklen;

	/*用于接收、缓存客户端 发来的字节流，每个事件消费模块可自由决定从连接池中分配多大空间给 buffer这个 缓存字段*/
    ngx_buf_t          *buffer;

	/*表示将当前连接作为双向连接中节点元素，添加到ngx_cycle_t结构体的成员reuseable_connections_queue的双向链表中*/
    ngx_queue_t         queue;

	/* 连接使用次数。ngx_connection_t结构体每次建立一条来自客户端的连接，或者主动向后端服务器发起连接时，number都会加1 */
    ngx_atomic_uint_t   number;

	/* 处理 请求次数 */
    ngx_uint_t          requests;

    unsigned            buffered:8;

    unsigned            log_error:3;     /* ngx_connection_log_error_e */

	/* 标志位，为1表示当前连接已经超时 */
    unsigned            timedout:1;
	/* 标志位，为1表示处理连接过程出错 */
    unsigned            error:1;
    /* 标志位，为1表示当前TCP连接已经销毁 */
    unsigned            destroyed:1;

	/* 标志位，为1表示当前连接处于空闲状态 */
    unsigned            idle:1;
	/* 标志位，为1表示当前连接可重用 */
    unsigned            reusable:1;
	/* 标志为，为1表示当前连接已经关闭 */
    unsigned            close:1;
    unsigned            shared:1;

	/* 标志位，为1表示正在将文件的数据发往对端 
	 * 这个意思应该是通过sendfile发送文件吧
	 * */
    unsigned            sendfile:1;
	/*标志位，若为1，则表示只有连接对应的发送缓冲区满足最低设置的阈值时，事件驱动模块才会分发事件*/
    unsigned            sndlowat:1;
    unsigned            tcp_nodelay:2;   /* ngx_connection_tcp_nodelay_e */
    unsigned            tcp_nopush:2;    /* ngx_connection_tcp_nopush_e */

    unsigned            need_last_buf:1;

#if (NGX_HAVE_AIO_SENDFILE || NGX_COMPAT)
    unsigned            busy_count:2;
#endif

#if (NGX_THREADS || NGX_COMPAT)
    ngx_thread_task_t  *sendfile_task;
#endif
};


#define ngx_set_connection_log(c, l)                                         \
                                                                             \
    c->log->file = l->file;                                                  \
    c->log->next = l->next;                                                  \
    c->log->writer = l->writer;                                              \
    c->log->wdata = l->wdata;                                                \
    if (!(c->log->log_level & NGX_LOG_DEBUG_CONNECTION)) {                   \
        c->log->log_level = l->log_level;                                    \
    }


ngx_listening_t *ngx_create_listening(ngx_conf_t *cf, struct sockaddr *sockaddr,
    socklen_t socklen);
ngx_int_t ngx_clone_listening(ngx_cycle_t *cycle, ngx_listening_t *ls);
ngx_int_t ngx_set_inherited_sockets(ngx_cycle_t *cycle);
ngx_int_t ngx_open_listening_sockets(ngx_cycle_t *cycle);
void ngx_configure_listening_sockets(ngx_cycle_t *cycle);
void ngx_close_listening_sockets(ngx_cycle_t *cycle);
void ngx_close_connection(ngx_connection_t *c);
void ngx_close_idle_connections(ngx_cycle_t *cycle);
ngx_int_t ngx_connection_local_sockaddr(ngx_connection_t *c, ngx_str_t *s,
    ngx_uint_t port);
ngx_int_t ngx_tcp_nodelay(ngx_connection_t *c);
ngx_int_t ngx_connection_error(ngx_connection_t *c, ngx_err_t err, char *text);

ngx_connection_t *ngx_get_connection(ngx_socket_t s, ngx_log_t *log);
void ngx_free_connection(ngx_connection_t *c);

void ngx_reusable_connection(ngx_connection_t *c, ngx_uint_t reusable);

#endif /* _NGX_CONNECTION_H_INCLUDED_ */
