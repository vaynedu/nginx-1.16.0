#include <stdio.h>
#include <stdint.h>
#include "ngx_md5.h"
#include <assert.h>
#include <stdlib.h>

/*
 *
 * md5使用上下文初始化
 * void ngx_md5_init(ngx_md5_t *ctx);
 *
 * 根据输入的data和len更新ctx
 * void ngx_md5_update(ngx_md5_t *ctx, const void *data, size_t size);
 *
 * 输出一个unsigned char 16个字节的数组
 * void ngx_md5_final(u_char result[16], ngx_md5_t *ctx);
 *
 *
 * */



/*
 * 1234
 * md5 : 81dc9bdb52d04dc20036dbd8313ed055
 *
 * */


#define MD5TOHEX(md5) \
            *(uint32_t *)&md5[0], \
            *(uint32_t *)&md5[4], \
            *(uint32_t *)&md5[8], \
            *(uint32_t *)&md5[12]


const char HEX[16] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};

void md5_to_hex(unsigned char *md5, int md5_len, char *hex, int hex_len)
{
        assert(hex_len == (md5_len << 1) && md5 != NULL && hex != NULL);
        int i = 0;
        int j  = 0;
	 	
        for (; i < md5_len; ++i)
        {
	    hex[j++] = HEX[md5[i] / 16];
	    hex[j++] = HEX[md5[i] % 16];
	}
}

void ngx_get_md5(const char *data,  size_t data_len, unsigned char *md5)
{
    ngx_md5_t ctx;

    ngx_md5_init(&ctx);
    ngx_md5_update(&ctx, (const void *)data, data_len);
    ngx_md5_final(md5, &ctx);
}


int main()
{

   unsigned char md5[16];
   const char *data = "1234";
   size_t size = sizeof("1234") - 1;


  // ngx_get_md5
   memset(md5, 0, 16);
   ngx_get_md5(data,size , md5);
   printf("md5 : %x %x %x %x\n", MD5TOHEX(md5));

     char hex[32 + 1] = {0};
   md5_to_hex(md5, 16, hex,32);

   int i = 0;
   memset(hex,0, sizeof(hex));
   for(i = 0; i < 16; i++)
   {
      snprintf(hex + i * 2, 32, "%02x", md5[i]);
   }
   printf("md5 : %s\n", hex);

  return 0;
}











