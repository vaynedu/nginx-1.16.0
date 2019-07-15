
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


## 二、ngx_sha1.c
ngx_sha1 和 ngx_md5 都是用来计算消息摘要
只不过ngx_sha1 更安全，因为sha1有20个字节

```Bash
echo -n "1234" | md5sum
81dc9bdb52d04dc20036dbd8313ed055

echo -n "1234" | sha1sum
7110eda4d09e062aa5e4a390b0a572ac0d2c0220
```





