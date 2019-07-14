
nginx-1.16.0
====
myngx_list.c --- [调试练习ngx_list.c的代码](https://wait.com)<br>
----

## 一、ngx_list_t 链表<br>
>> #### 非常简单的一个数据结构，封装了一个单链表，只不过增加了链表的描述信息(链表首尾、个数等)
>> #### [单链表的一些操作](https://blog.csdn.net/lotluck/article/details/50238691)<br>
>> #### [带有控制信息的单链表](https://blog.csdn.net/lotluck/article/details/50239027)<br>

## 二、问题&分析<br>
>> #### 按照nignx设计的链表， 这里存在风险，因为对我push的元素大小没有做判断, 就直接分配空间
>> #### 所以nginx链表这里使用的时候，确保每次传入的值都是小于size的


## 三、记录面试遇到链表问题<br>
### 1. 待整理<br>
```c
  整理ing
```
<br>


