
nginx-1.16.0
====
vim vim、ctags、cscope搭建linux工作环境（类似source insight）
----

## 一、vim <br>
>> #### 准备ing



## 二、ctags <br>
```Bash
1. yum install ctags
2. ctags -R
3. vim /etc/vimrc 
      set tags=/data/lotluck/nginx-1.16.0/tags
```

## 三、cscope<br>
```
1. yum install cscope

2. cscope -RbqC
    生成cscope.out, cscope.in.out, cscope.po.out三个索引文件

3. 打开vim(有时候需要在vim中执行set nocscopeverbose)
    :cs add cscope.out
    :cs -h
    

```

## 四、tmux<br>
终端复用神器

