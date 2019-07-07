
nginx-1.16.0
====
myngx_pool.c --- [调试练习ngx_pool.c的代码](https://wait.com)<br>
----

## 一、ngx_pool_t 内存池


### nginx内存池是一个非常的优秀的设计模块，这里需要好好了解 




## 二、遇到问题<br>
### 1. 编译出去-Werror=unused-variable<br>
```c
   a) myngx_pool.c: In function ‘main’:
      myngx_pool.c:33:17: error: unused variable ‘pool’ [-Werror=unused-variable]
            ngx_pool_t *pool = NULL; 
 
      解决办法：gcc编译过程去掉-Werror参数就行

   b) myngx_pool.c:46:9: warning: format ‘%x’ expects argument of type ‘unsigned int’, but argument 2 has type ‘struct ngx_log_t *’ [-Wformat=]
      printf("  .log = 0x%x\n", pool->log);
      解决办法：-Wformat=0
```
<br>



### 2. makefile编译文件，只要mtime变化采取重新编译，否则只改makefile不会生效<br>
```Bash
   可以touch * 修改文件mtime，达到重新编译的目的
```
<br>



### 3. 如何产生一个core文件<br>
```Bash
   echo "/data/corefiles/core-%e-%p" >/proc/sys/kernel/core_pattern
   ulimit -c unlimited 
```
<br>



### 4. 如何查看一个core文件?<br>
```Bash
  gdb ./myngx_pool /data/corefiles/core-myngx_pool-2534

  这里又涉及到gdb的调试知识，可以先bt，core在哪一行了
  (gdb) bt
  #0  ngx_memalign (alignment=alignment@entry=16, size=size@entry=1024, log=log@entry=0x0) at src/os/unix/ngx_alloc.c:84
  #1  0x0000000000400a61 in ngx_create_pool (size=1024, log=0x0) at src/core/ngx_palloc.c:23
  #2  0x0000000000403405 in main () at myngx_pool.c:58
  (gdb) f 0
  #0  ngx_memalign (alignment=alignment@entry=16, size=size@entry=1024, log=log@entry=0x0) at src/os/unix/ngx_alloc.c:84
        84	    ngx_log_debug3(NGX_LOG_DEBUG_ALLOC, log, 0,
  (gdb) 

  原来自己开启--with-debug功能，编译的时候关闭就好

  nginx debug代码不合理，至少应该判断log是否为NULL再去log->xx 成员，否则就会core掉

```
