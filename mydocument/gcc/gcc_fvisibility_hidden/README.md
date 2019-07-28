
nginx-1.16.0
====
gcc_fvisibility_hidden -- 如何处理linux库的同名函数
----

[具体过程请参考我的博客](https://blog.csdn.net/lotluck/article/details/97394775)

## 一、如何验证linux库的同名函数调串？
>> #### makefile 注释 CFLAGS += -D_ATTRIBUTE_FLAG -fvisibility=hidden

## 二、解决方案？
>> #### makefile 开启 CFLAGS += -D_ATTRIBUTE_FLAG -fvisibility=hidden
