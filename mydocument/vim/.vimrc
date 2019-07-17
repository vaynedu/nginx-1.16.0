let Tlist_Show_One_File=1     "不同时显示多个文件的tag，只显示当前文件的    
let Tlist_Exit_OnlyWindow=1   "如果taglist窗口是最后一个窗口，则退出vim   
let Tlist_Ctags_Cmd="/usr/bin/ctags" "将taglist与ctags关联  

"cscope.out 还是写绝对路径，不然要是不在cscope.out的目录，打开文件会存在文件"
"\E429: File xxx does not exist， 
"cscope要写绝对路径，不然就直接在cscope目录下vim文件就行
set  nocscopeverbose
"cs add cscope.out
cs add /data/lotluck/nginx-1.16.0/cscope.out
 
