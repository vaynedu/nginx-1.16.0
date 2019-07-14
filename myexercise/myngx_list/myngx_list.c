#include <stdio.h>
#include "nginx.h"

#include "ngx_conf_file.h"
#include "ngx_config.h"
#include "ngx_list.h"
#include "ngx_palloc.h"


#include "ds_common_c_lib.h" // my common c lib



/*
 * 按照nignx设计的链表， 这里存在风险，因为对我push的元素大小没有做判断
 *
 * 就直接分配空间
 *
 *
 * 所以nginx链表这里使用的时候，确保每次传入的值都是小于size的
 *
 *
 * */




volatile ngx_cycle_t  *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
}


void ngx_list_print(ngx_list_t *l)
{

  DEBUG("Enter ngx_list_print\n");
 
  if(l == NULL || l->last == NULL)  return;

  ngx_list_part_t *last = NULL;
  
  last = l->last; 

  int i;


  for(i = 0; i < last->nelts; i++)
  {
      void  *elt = NULL;
      
      elt = (char *) last->elts + l->size * i;

      printf("%s\n", elt);

  }
   
 
}


int main()
{
  ngx_list_t *list = NULL;
  ngx_pool_t *pool = NULL;


  pool = ngx_create_pool(2048, NULL);
  if(pool == NULL)
  {
     DEBUG("ngx_create_pool failed");    
     return -1;
  }
 

  list = ngx_list_create(pool, 10, 50);  
  if(list == NULL)
  {
     DEBUG("ngx_list_create failed");
     return -2;
  }

  char  *s = NULL;
  s  =  ngx_list_push(list); 
  ngx_memcpy(s, "aaaaa", sizeof("aaaaa"));
  DEBUG("%x\n",&s);
 
  s  =  ngx_list_push(list); 
  ngx_memcpy(s, "bbbbb", sizeof("bbbbb"));
  DEBUG("%x\n",&s);



  s  =  ngx_list_push(list); 
  ngx_memcpy(s, "cccccc", sizeof("cccccc"));
  DEBUG("%x\n",&s);

  ngx_list_print(list);
  

  return 0;
}
