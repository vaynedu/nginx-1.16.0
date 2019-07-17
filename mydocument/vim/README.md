
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
```Bash
1. yum install cscope

2. cscope -RbqC
    生成cscope.out, cscope.in.out, cscope.po.out三个索引文件

3. 打开vim(有时候需要在vim中执行set nocscopeverbose)
    :cs add cscope.out
    :cs -h
    
```



## 四、Taglist<br>
```Bash
1. 官网直接下载最新的 taglist_46.zip
   https://www.vim.org/scripts/script.php?script_id=273
2. 进入~/.vim目录， unzip taglist_46.zip

3. 进入~/.vim/doc目录，在Vim下运行"helptags ."命令。此步骤是将doc下的帮助文档加入到Vim的帮助主题中，这样我们就可以通过在Vim中运行“help taglist.txt”查看taglist帮助

4. 打开配置文件~/.vimrc,添加如下几行
    let Tlist_Show_One_File=1     "不同时显示多个文件的tag，只显示当前文件的    
    let Tlist_Exit_OnlyWindow=1   "如果taglist窗口是最后一个窗口，则退出vim   
    let Tlist_Ctags_Cmd="/usr/bin/ctags" "将taglist与ctags关联  

5. 进入vim中， :Tlist开启启用Tlist窗口

6. 基本操作
   <CR>          跳到光标下tag所定义的位置，用鼠标双击此tag功能也一样
   o             在一个新打开的窗口中显示光标下tag
   <Space>       显示光标下tag的原型定义
   u             更新taglist窗口中的tag
   s             更改排序方式，在按名字排序和按出现顺序排序间切换
   x             taglist窗口放大和缩小，方便查看较长的tag
   +             打开一个折叠，同zo
   -             将tag折叠起来，同zc
   *             打开所有的折叠，同zR
   =             将所有tag折叠起来，同zM
   [[            跳到前一个文件
   ]]            跳到后一个文件
   q             关闭taglist窗口
   <F1>          显示帮助

```






## 五、tmux<br>
终端复用神器




