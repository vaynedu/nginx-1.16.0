
nginx-1.16.0
====
gcc_fvisibility_hidden -- 如何处理linux库的同名函数
----

[具体过程请参考我的博客](https://blog.csdn.net/lotluck/article/details/97394775)

## 一、如何验证linux库的同名函数调串？
>> #### main.c   修改 attribute_flag = 0;
>> #### makefile 修改 CFLAGS  += -g

## 二、解决方案？
>> #### main.c   修改 attribute_flag = 1; 
>> #### makefile 修改CFLAGS  += -g -fvisibility=hidden
