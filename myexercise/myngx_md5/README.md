
nginx-1.16.0
====
myngx_md5.c --- 调试练习ngx_md5.c的代码<br>
----

## 一、ngx_md5.c

### 代码非常的简单，但是我觉得这里缺少封装，为什么就不能直接提供一个ngx_get_md5()函数，直接获取字符串的md5呢



### 自己编写ngx_get_md5()函数如下<br>
```c
void ngx_get_md5(const char *data,  size_t data_len, unsigned char *md5)
{
    ngx_md5_t ctx;

    ngx_md5_init(&ctx);
    ngx_md5_update(&ctx, (const void *)data, data_len);
    ngx_md5_final(md5, &ctx);
}
```
<br>




### md5转化成16进制也很简单<br>
```c

   char hex[32 + 1] = {0};
   for(i = 0; i < 16; i++)
   {
      snprintf(hex + i * 2, 32, "%02x", md5[i]);
   }
```





