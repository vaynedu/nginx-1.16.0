
nginx-1.16.0
====
nginx-1.16.0源码分析及其注释
----

## 1.echo-nginx-module<br>
>> ####  [echo-nginx-module原地址](https://github.com/openresty/echo-nginx-module)<br>
>> #### ./configure --prefix=/data4/nginx/nginx --add-module=./third-module/echo-nginx-module-0.61 && make -j8 && make install
 

## 2.myhello-module<br>
./configure --prefix=/data4/nginx/nginx --add-module=./third-module/tmp/echo-nginx-module-0.61 --with-debug --add-module=./mymodule/ngx_http_myhello_module/  && make -j8 && make install

