#include <stdio.h>
#include <stdint.h>

#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"
#include "ngx_array.h"
#include "ngx_hash.h"



#include "ds_common_c_lib.h" // my common c lib  DEBUG()


volatile ngx_cycle_t  *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
}

//gcc -m32 test_ngx_hash_elt_t.c
//pragma 控制内存是否对齐


//#pragma  pack(1)
typedef struct {  
    void             *value;            //即为key-value中对应的value  
    unsigned short    len;              //为key-value中key的长度  
    /*
     * name[1]为key的首地址
     * 这里是非常重要的一个技巧，C语言的柔性数组(可变长数组)
     * 可以申请一段连续的空间
     */
    unsigned char    name[1];            
} myngx_hash_elt_t;  

//#pragma  pack()

int main()
{
    printf("sizeof(myngx_hash_elt_t) = %lu\n", sizeof(myngx_hash_elt_t));
 
    printf("sizeof(ngx_hash_elt_t) = %lu\n", sizeof(ngx_hash_elt_t));
  
   
    ngx_pool_t *pool = NULL;

    pool = ngx_create_pool(8192, NULL);
    if( pool == NULL)
    {
      DEBUG("ngx_create_pool failed");
      return -1;   
    }

    const char *str = "vaynedu test";
    ngx_hash_elt_t  *elt  = ngx_palloc(pool, sizeof(ngx_hash_t) + 100);
    
    elt->value =(char *)str;
   
    elt->len = 20;

    ngx_memcpy(elt->name, "xiao guai guai", sizeof("xiao guai guai") - 1);
  

    DEBUG("elt : %x", elt);
    DEBUG("*elt : %x", *elt);
    DEBUG("")
  
   
 
    
    




    return 0;
}



