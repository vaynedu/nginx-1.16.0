
vmtouch
====
vmtouch - the Virtual Memory Toucher
就是用来查看linux文件缓存（page cache）使用情况，命中率

----

## 一、介绍
>> #### 现网是真正提升能力的地方,因为机器高负载之后,会出现各种各样的问题,包括很很多"假象". 而机器高负载的原因很多,比如内存.  之前遇到的问题就是, pagecache使用过多,导致内存不足,然后接着cpu飙升,严重影响业务质量.这就是为什么要搞个vmtouch的原因. 我要查看哪些文件大量使用page cache， 然后好直接` echo 3 > /proc/sys/vm/drop_caches` ,暴力清除缓存


## 二、编译方法
```Bash
gcc -Wall -O3 -o vmtouch vmtouch.c
```


## 三、使用方法
>> #### 待添加



## 四、

