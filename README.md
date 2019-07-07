
nginx-1.16.0
====
nginx-1.16.0源码分析及其注释--记录心路历程
----

## 一.mymodule<br>
### 1.echo-nginx-module<br>
>> ####  [echo-nginx-module原地址](https://github.com/openresty/echo-nginx-module)<br>
>> ####  nginx.conf中通过echo等指令直接输出包体， 类似于nginx的命令，方便调试配置
>> #### ./configure --prefix=/data4/nginx/nginx --add-module=./third-module/echo-nginx-module-0.61 && make -j8 && make install
 

## 二.myhello-module<br>
### 1.ngx_http_myhello_module<br>
>> #### 自己编写的一些hello模块，用来熟悉和掌握nginx
>> #### ./configure --prefix=/data4/nginx/nginx --add-module=./third-module/tmp/echo-nginx-module-0.61 --with-debug --add-module=./mymodule/ngx_http_myhello_module/  && make -j8 && make install


## [三. myexercise--练习调试一些nginx的代码](https://github.com/lotluck/nginx-1.16.0/tree/master/myexercise)<br>
### 1.myngx_hash<br>
>> #### 调试练习ngx_hash.c的代码

### 2.myngx_pool.c<br>
>> #### 调试练习ngx_pool.c的代码


