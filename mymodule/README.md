
nginx-1.16.0
====
自己编写的一些nginx模块，用来熟悉和掌握nginx
----

## 1.myhello-module<br>
./configure --prefix=/data4/nginx/nginx --add-module=./thirdpartylib/tmp/echo-nginx-module-0.61 --with-debug --add-module=./mymodule/ngx_http_myhello_module/  && make -j8 && make install
