#include <stdio.h>
#include <stdint.h>
#include "ngx_config.h"
#include "ngx_crc32.h"
#include "ngx_palloc.h"


volatile ngx_cycle_t  *ngx_cycle;

ngx_uint_t  ngx_cacheline_size = 32;

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
}


int main()
{

   if(ngx_crc32_table_init() != NGX_OK)
   {
        return 1;
   }

 
   uint32_t hash;
   
   printf("hash = %u\n",hash);   

   ngx_crc32_init(hash);

   printf("ngx_crc32_init hash = %u\n",hash);
   
   ngx_crc32_update(&hash, (u_char *)"11111", sizeof("1111") - 1);

   printf("ngx_crc32_update hash = %u\n",hash);
   
   ngx_crc32_final(hash);
   printf("ngx_crc32_final hash = %u\n",hash);


    hash = ngx_crc32_short((u_char *)"11111",sizeof("1111") - 1);
    printf("ngx_crc32_short hash = %u\n",hash); 


    hash = ngx_crc32_long((u_char *)"11111",sizeof("1111") - 1);
    printf("ngx_crc32_long hash = %u\n",hash);



   // hash = ngx_crc32_short(session_id, session_id_length);
 
  
   return 0;
}
