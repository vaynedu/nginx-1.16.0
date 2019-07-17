
nginx-1.16.0
====
nginx-1.16.0源码分析及其注释--记录心路历程
----

## [一. myexercise--练习调试一些nginx的代码](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise)<br>
### [1.myngx_pool.c](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise/myngx_pool)<br>
>> #### 调试练习ngx_pool.c的代码

### [2.myngx_hash](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise/myngx_hash)<br>
>> #### 调试练习ngx_hash.c的代码


### [3.myngx_list](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise/myngx_list)<br>
>> ####  调试练习ngx_list.c的代码


### [4.myngx_md5](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise/myngx_md5)<br>
>> ####  调试练习ngx_md5.c的代码, ngx_sha1.c亦是如此


### [5.myngx_crc](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise/myngx_crc)<br>
>> ####  调试练习ngx_crc.c的代码




## [二.mymodule--自己编写一些模块](https://github.com/lotluck/nginx-1.16.0/tree/master/mymodule)<br>
### 1.ngx_http_myhello_module<br>
>> #### 自己编写的一些hello模块，用来熟悉和掌握nginx
>> #### ./configure --prefix=/data4/nginx/nginx --add-module=./third-module/tmp/echo-nginx-module-0.61 --with-debug --add-module=./mymodule/ngx_http_myhello_module/  && make -j8 && make install


## 三.已翻译代码
### 1.HTTP模块<br>
>> #### a) HTTP的11个阶段入口   src/http/ngx_http_core_module.c -- 特别重要
>> #### b) 待添加  
 
### 2.配置相关<br>
>> #### a) 模块上下文结构体   --- 待完成
>> #### b) 模块结构体   --待完成
>> #### c) ngx_command_t 配置指令结构体 -- 待完成

### 3.数据结构<br>
>> #### a) ngx_pool_t 内存池--src/core/ngx_palloc.c、src/os/unix/ngx_alloc.c 
>> #### b) ngx_hash_elt_t  nginx哈希表 -- src/core/ngx_hash.c
>> #### c) ngx_array_t    动态数组 -- src/core/ngx_array.c
>> #### d) ngx_list_t  链表 --  src/core/ngx_list.c
>> #### e) ngx_md5_t && ngx_sha1_t  生成md5, 增加封装 --  src/core/ngx_md5.c src/core/ngx_sha1.c
>> #### f) ngx_crc32  crc使用 --  src/core/ngx_crc32.c


## [四.third-module -- 第三方模块](https://github.com/lotluck/nginx-1.16.0/tree/master/third-module)<br>
### 1.echo-nginx-module<br>
>> ####  [echo-nginx-module原地址](https://github.com/openresty/echo-nginx-module)<br>
>> ####  nginx.conf中通过echo等指令直接输出包体， 类似于nginx的命令，方便调试配置
>> ####  ./configure --prefix=/data4/nginx/nginx --add-module=./third-module/echo-nginx-module-0.61 && make -j8 && make install


## [五.mydocument -- 相关文档资料](https://github.com/lotluck/nginx-1.16.0/tree/master/books)<br>
### 1. nginx
>> #### a) 《深入理解nginx》--陶辉
>> #### b) 《深入剖析nginx》

### 2. http
>> #### a) 《图解HTTP》
>> #### b) 《图解TCP/IP》

### 3.git
>> #### a) git color着色初始化脚本


## [六.tools -- 相关工具](https://github.com/lotluck/nginx-1.16.0/tree/master/tools)
### 1. ab 压测工具
>> #### yum install httpd-tools
>> #### 直接上手ab -n 1000 -c 5 http://1.1.1.1/1.mp4
### 2. stress
>> #### 待添加


## [七.myshell]
### 记录一些常用的初始化脚本
### 待补充



