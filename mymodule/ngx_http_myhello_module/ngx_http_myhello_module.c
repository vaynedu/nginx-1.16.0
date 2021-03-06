#include <ngx_http.h>
#include <ngx_core.h>
#include <ngx_config.h>



static char *ngx_http_myhello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_myhello_handler(ngx_http_request_t *r);

/*
 * 定义myhello配置结构体
 */
static ngx_command_t ngx_http_myhello_commands[] = {
	{
		
		ngx_string("myhello"),
		
		NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
		
		ngx_http_myhello,
		
		NGX_HTTP_LOC_CONF_OFFSET,
		
		0,
		
		NULL
	},
};

/* 
 * myhello指令的回调函数，主要用来赋值handler
 *
 * 这到底是哪个阶段的
 */
static char *ngx_http_myhello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	ngx_http_core_loc_conf_t *clcf;
        clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);	
	
	clcf->handler = ngx_http_myhello_handler;
	
	return NGX_CONF_OK;
}


static ngx_http_module_t ngx_http_myhello_module_ctx = {
 	NULL,   /* preconfiguration */

	NULL,   /* postconfiguration */

	NULL,   /* create main configuration */

	NULL,  /* init main configuration */

	NULL,  /* create server configuration */

	NULL,  /* merge server configuration */

	NULL,  /* create location configuration */

	NULL  /* merge location configuration */
};


ngx_module_t ngx_http_myhello_module = {
	NGX_MODULE_V1,
	
	&ngx_http_myhello_module_ctx,
	
	ngx_http_myhello_commands,
	
	NGX_HTTP_MODULE,
	
	NULL,
	
	NULL,
	
	NULL,
	
	NULL,
	
	NULL,
	
	NULL,
	
	NULL,
	
	NGX_MODULE_V1_PADDING	
};

static ngx_int_t ngx_add_diy_header(ngx_http_request_t *r,  ngx_str_t *name,  ngx_str_t *value)
{
    if(r == NULL || name == NULL || value == NULL)
    {
        return NGX_ERROR;
    }

    ngx_table_elt_t *h = ngx_list_push(&r->headers_out.headers);
    if( h == NULL)
    {
       return NGX_ERROR;
    } 

   ngx_uint_t hash = 0;
   ngx_uint_t  i = 0;
   u_char ch;  
   for(i = 0; i < name->len;  i++)
   { 
     ch = name->data[i];
     /* #define ngx_hash(key, c)   ((ngx_uint_t) key * 31 + c) */
     hash = ngx_hash(hash, ch);
   } 
   for(i = 0; i < value->len; i++)
   { 
     ch = value->data[i];
     hash = ngx_hash(hash, ch);
   }


    h->hash = hash;
    h->key.len = (*name).len;
    h->key.data = name->data;
    h->value.len = value->len;
    h->value.data = value->data;
  
    /*
     * nginx 打印无符号整型和C语言不一样，这里有自定义的格式
     *
     * src/core/ngx_string.c
     *
     * %O — off_t
     * %T — time_t
     * %z — ssize_t
     * %i — ngx_int_t
     * %p — void *
     * %V — ngx_str_t *
     * %s — u_char * (null-terminated)
     * %*s — size_t + u_char *
     *
     * 大多数类型上加上前缀来使它们无符号。 要将输出转换为十六进制，请使用X或x
     * 
     *
     *
     */
    ngx_log_debug7(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,"\nngx_add_diy_header:\n name:%s, value:%s, h->key.len:%d, h->key.data:%s ,h->value.len:%d, h->value.data:%s , h->hash:%ui \n", name->data,value->data,h->key.len,h->key.data, h->value.len, h->value.data,h->hash);


    return NGX_OK;

}

static ngx_int_t ngx_add_c_diy_header(ngx_http_request_t *r,  const u_char *name,  int name_len,  const u_char *value, int value_len)
{
   if(r == NULL || name == NULL || name_len == 0 ||  
                  value == NULL || value_len == 0)
   {
        return NGX_ERROR;
   }
   
   ngx_table_elt_t *h = ngx_list_push(&r->headers_out.headers);
   if(h == NULL)
   {
     return NGX_ERROR;
   }

   ngx_uint_t hash = 0;
   ngx_int_t  i = 0;
   u_char ch;
   for(i = 0; i < name_len;  i++)
   {
     ch = name[i];
     /* #define ngx_hash(key, c)   ((ngx_uint_t) key * 31 + c) */
     hash = ngx_hash(hash, ch);
   }
   for(i = 0; i < value_len; i++)
   {
     ch = value[i];
     hash = ngx_hash(hash, ch);
   }

   h->hash = hash;
   h->key.len = name_len;
   h->key.data = (u_char *)name;
   h->value.len = value_len;
   h->value.data = (u_char *)value;   

   ngx_log_debug7(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,"\nngx_add_c_diy_header:\n name:%s, value:%s, h->key.len:%d, h->key.data:%s ,h->value.len:%d, h->value.data:%s, h->hash:%ui\n", name,value,h->key.len,h->key.data, h->value.len, h->value.data, h->hash);

   return NGX_OK;
}



static ngx_int_t ngx_http_myhello_handler(ngx_http_request_t *r)
{
	/* 判断请求方法是否为GET或者HEAD，否则返回405 Not Allowed */
	if(!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD)))
	{
		return NGX_HTTP_NOT_ALLOWED;
	}
	
	/* 丢掉请求中的包体*/
	ngx_int_t rc = ngx_http_discard_request_body(r);
	if(rc != NGX_OK)
	{
		return rc;
	}
	
	/* 设置相应头部 */
	ngx_str_t type = ngx_string("text/plain");
	ngx_str_t response = ngx_string("Hello vaynedu, you are best\n\ncome on\n\n");
	//ngx_str_t date = ngx_string("2019-7-3 7:40:30");
	r->headers_out.status = NGX_HTTP_OK;
	r->headers_out.content_length_n = response.len;
	r->headers_out.content_type = type;

   
        /* 发送自定义头部 
         *   ngx_http_headers_out_t
         *
         * 
         * */
        ngx_table_elt_t *h = ngx_list_push(&r->headers_out.headers);
        if(h == NULL)
        {
            return NGX_ERROR;
        }

        h->hash = 1;
        h->key.len = sizeof("name") - 1;
        h->key.data = (u_char *)"name";
        h->value.len = sizeof("vaynedu") - 1;
        h->value.data = (u_char *)"vaynedu";


       
        ngx_str_t module_name = ngx_string("module");
        ngx_str_t module_value = ngx_string("ngx_http_myhello_module");
        h = ngx_list_push(&r->headers_out.headers);
        if( h == NULL)
        {
            return NGX_ERROR;
        }

        h->hash = 2;
        h->key.len = module_name.len;
        h->key.data = module_name.data;
        h->value.len = module_value.len;
        h->value.data = module_value.data;
        

        ngx_str_t header_name  = ngx_string("today");
        ngx_str_t header_value = ngx_string("2019-07-04 08:08:54");
        ngx_add_diy_header(r, &header_name, &header_value); 

        ngx_add_c_diy_header(r, (const u_char *)"tomorror", sizeof("tomorror")-1, (const u_char *)"2019-07-05 08:08:08", sizeof("2019-07-05 08:08:08")-1);
        ngx_add_c_diy_header(r, (const u_char *)"X-Cache-Status", sizeof("X-Cache-Status")-1, (const u_char *)"cluster_hit", sizeof("cluster_hit")-1);

	
	/* 发送HTTP头部 */
	rc = ngx_http_send_header(r);
	if(rc == NGX_ERROR || rc > NGX_OK || r->header_only)
	{
		return rc;
	}
	
	/* 构造ngx_buf_t 结构体准备发送包体*/
	ngx_buf_t *b;
	b = ngx_create_temp_buf(r->pool, response.len);
	if(b == NULL)
	{
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}
	
	ngx_memcpy(b->pos, response.data, response.len);
	
	b->last = b->pos +response.len;
	
	b->last_buf = 1;
	
	
	/* 构造发送时的ngx_chain_t 结构体 */
	ngx_chain_t out;
	out.buf = b;
	out.next = NULL;
	
	return ngx_http_output_filter(r, &out); 
	
	
}
