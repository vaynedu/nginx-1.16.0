
vmtouch
====
vmtouch - the Virtual Memory Toucher
就是用来查看linux文件缓存（page cache）使用情况，命中率

## 一、介绍
现网是真正提升能力的地方,因为机器高负载之后,会出现各种各样的问题,包括很很多"假象". 而机器高负载的原因很多,比如内存.  之前遇到的问题就是, pagecache使用过多,导致内存不足,然后接着cpu飙升,严重影响业务质量.这就是为什么要搞个vmtouch的原因. 我要查看哪些文件大量使用page cache， 然后好直接` echo 3 > /proc/sys/vm/drop_caches` ,暴力清除缓存


## 二、编译方法
```Bash
gcc -Wall -O3 -o vmtouch vmtouch.c
```


## 三、使用方法-非常的简单
```Bash
[root@VM_1_38_centos /data/lotluck/nginx-1.16.0/tools/vmtouch]# ./vmtouch vmtouch.c 
Files: 1
Directories: 0
Resident Pages: 7/7  28K/28K  100%
Elapsed: 5e-05 seconds
[root@VM_1_38_centos /data/lotluck/nginx-1.16.0/tools/vmtouch]# ./vmtouch 
./vmtouch: no files or directories specified

vmtouch v1.3.0 - the Virtual Memory Toucher by Doug Hoyte
Portable file system cache diagnostics and control

Usage: vmtouch [OPTIONS] ... FILES OR DIRECTORIES ...

Options:
  -t touch pages into memory
  -e evict pages from memory
  -l lock pages in physical memory with mlock(2)
  -L lock pages in physical memory with mlockall(2)
  -d daemon mode
  -m <size> max file size to touch
  -p <range> use the specified portion instead of the entire file
  -f follow symbolic links
  -F don't crawl different filesystems
  -h also count hardlinked copies
  -i <pattern> ignores files and directories that match this pattern
  -I <pattern> only process files that match this pattern
  -b <list file> get files or directories from the list file
  -0 in batch mode (-b) separate paths with NUL byte instead of newline
  -w wait until all pages are locked (only useful together with -d)
  -P <pidfile> write a pidfile (only useful together with -l or -L)
  -v verbose
  -q quiet
[root@VM_1_38_centos /data/lotluck/nginx-1.16.0/tools/vmtouch]# ./vmtouch -e vmtouch.c 
Files: 1
Directories: 0
Evicted Pages: 7 (28K)
Elapsed: 2.1e-05 seconds

