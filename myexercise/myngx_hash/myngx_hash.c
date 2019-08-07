#include <stdio.h>
#include <stdint.h>

#include "ngx_conf_file.h"
#include "ngx_config.h"
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




typedef struct 
{
	ngx_str_t  servername;
	ngx_int_t seq;

}TestWildcardHashNode;




int main()
{
    printf("sizeof(myngx_hash_elt_t) = %lu\n", sizeof(myngx_hash_elt_t));
 
    printf("sizeof(ngx_hash_elt_t) = %lu\n", sizeof(ngx_hash_elt_t));


	ngx_int_t ret = -1;
    ngx_int_t i = 0;
    ngx_pool_t *p = NULL;
    ngx_hash_init_t hash;
	ngx_hash_keys_arrays_t ha;
	ngx_hash_combined_t combineHash;  // 支持通配符的散列表
    
	
	p = ngx_create_pool(NGX_DEFAULT_POOL_SIZE, NULL);
    if( p == NULL)
    {
      DEBUG("ngx_create_pool failed");
      return -1;   
    }


	ngx_memzero(&ha, sizeof(ngx_hash_keys_arrays_t));

	ha.temp_pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE, NULL);
	if(ha.temp_pool == NULL)
	{
		DEBUG("ha.temp_pool, ngx_create_pool error\n");
		return -2;
	}

	ha.pool = p;

	if(ngx_hash_keys_array_init(&ha, NGX_HASH_LARGE) != NGX_OK)
	{
		DEBUG("ngx_hash_keys_array_init failed");
		return -3;
	}


	TestWildcardHashNode tnode[3];
	/*前缀匹配*/
	tnode[0].servername.data = ngx_palloc(p, ngx_strlen("*.test.com"));
	tnode[0].servername.len = ngx_strlen("*.test.com");
	ngx_memcpy(tnode[0].servername.data, "*.test.com", tnode[0].servername.len);

    /*后缀匹配*/
	tnode[1].servername.data = ngx_palloc(p, ngx_strlen("www.test.*"));
	tnode[1].servername.len = ngx_strlen("www.test.*");
	ngx_memcpy(tnode[1].servername.data, "www.test.*", tnode[1].servername.len);

    /*完全匹配*/
	tnode[2].servername.data = ngx_palloc(p, ngx_strlen("www.test.com"));
	tnode[2].servername.len = ngx_strlen("www.test.com");
	ngx_memcpy(tnode[2].servername.data, "www.test.com", tnode[2].servername.len);
   
   	

	for(i = 0; i < 3; i++)
	{
		tnode[i].seq = i;
		//NGX_HASH_WILDCARD_KEY表明可以处理带通配符的关键字
		ret = ngx_hash_add_key(&ha, &tnode[i].servername, tnode[i].servername.data,NGX_HASH_WILDCARD_KEY);
		if(ret != NGX_OK)
		{
			DEBUG("ngx_hash_add_key, failed");
			return -4;
		}
	}

    ngx_cacheline_size=32;//必须包含这句否则会段错误,core的地方很奇怪，还没有看懂
	hash.key = ngx_hash_key_lc;
	hash.max_size = 100;
	hash.bucket_size = 48;
	hash.name  = "my_hash_test";
	hash.pool = p;


	//初始化精确匹配散列表
	if(ha.keys.nelts)
	{
		hash.hash  = &combineHash.hash;
		hash.temp_pool = NULL;
		/*
		 *  ngx_hash_init hash初始化函数，分配好hash桶
		 */
		if(ngx_hash_init(&hash, ha.keys.elts, ha.keys.nelts) != NGX_OK)
		{
			DEBUG("ngx_hash_init failed");
			return -5;
		}

		/*
		 *  1.计算 www.test.com的hash值
		 *
		 *  2.hash表中查找www.test.com的value值  
		 *
		 *
		 * */
		ngx_uint_t k  = ngx_hash_key_lc(tnode[2].servername.data, tnode[2].servername.len);
		DEBUG("ngx_hash_key_lc %u", k);

		char *find = (char *)ngx_hash_find(hash.hash, k, tnode[2].servername.data, tnode[2].servername.len);
		if(find)
		{
			DEBUG("ngx_hash_find %s",find);
		}
		
	}

    return 0;
}



