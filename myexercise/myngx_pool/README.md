
nginx-1.16.0
====
myngx_pool.c --- [调试练习ngx_pool.c的代码](https://wait.com)<br>
----


## 引用nginx的.o文件，编写nginx的测试代码真是个技术活，重点是解决各种依赖，这才是真本事

## 同时也能熟悉nginx的hash代码，了解其精髓



## 二、遇到问题
###  1. 编译出去-Werror=unused-variable   
    ```
    myngx_pool.c: In function ‘main’:
    myngx_pool.c:33:17: error: unused variable ‘pool’ [-Werror=unused-variable]
              ngx_pool_t *pool = NULL; 

    解决办法：gcc编译过程去掉-Werror参数就行
   ```
### 2. makefile编译文件，只要mtime变化采取重新编译，否则只改makefile不会生效,可以touch *


### 3. 如何产生一个core文件？
    ```
     echo "/data/corefiles/core-%e-%p" >/proc/sys/kernel/core_pattern
     ulimit -c unlimited 
    ```
### 4. 如何查看一个core文件?
    ``` 
      gdb ./myngx_pool /data/corefiles/core-myngx_pool-2534

      这里又涉及到gdb的调试知识，可以先bt，core在哪一行了
      (gdb) bt
      #0  ngx_memalign (alignment=alignment@entry=16, size=size@entry=1024, log=log@entry=0x0) at src/os/unix/ngx_alloc.c:65
      #1  0x0000000000400a61 in ngx_create_pool (size=1024, log=0x0) at src/core/ngx_palloc.c:23
      #2  0x0000000000403405 in main () at myngx_pool.c:59

    ```
