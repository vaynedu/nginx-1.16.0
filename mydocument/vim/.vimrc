let Tlist_Show_One_File=1     "不同时显示多个文件的tag，只显示当前文件的    
let Tlist_Exit_OnlyWindow=1   "如果taglist窗口是最后一个窗口，则退出vim   
let Tlist_Ctags_Cmd="/usr/bin/ctags" "将taglist与ctags关联  

"cscope.out 还是写绝对路径，不然要是不在cscope.out的目录，打开文件会存在文件"
"\E429: File xxx does not exist， 
"cscope要写绝对路径，不然就直接在cscope目录下vim文件就行
set  nocscopeverbose
"cs add cscope.out
cs add /data/lotluck/nginx-1.16.0/cscope.out


"下划线
set cursorline
"用浅色高亮显示当前行
autocmd InsertEnter * se cul

"显示行号
set nu

"语法高亮
syntax on

"自动缩进
"set autoindent

"C语言专用缩进
set cindent

"设置Tab长度为4格
set tabstop=4

"设置自动缩进长度为4格 
set shiftwidth=4 

"指定配色方案为256
set t_Co=256

"忽略大小写
set ignorecase

" 粘贴代码时取消自动缩进
set paste


"代码补全
set completeopt=preview,menu
set completeopt=longest,menu

"打开文件类型检测功能
filetype on


"不同文件类型采用不同缩进
filetype indent on

""允许使用插件
filetype plugin on

"分为三部分命令:file on,file plugin on,file indent on 分别是自动识别文件类型,
	"用用文件类型脚本,使用缩进定义文件""]""
filetype plugin indent on

autocmd BufNewFile *.cpp,*.[ch] exec ":call SetTitle()"
func SetTitle()
	    call setline(1,"/*******************************************************************")
		call append(line("."),   "*    > F-Name :  ".expand("%")) 
	    call append(line(".")+1, "*    > Author :  vaynedu") 
		call append(line(".")+2, "*    > E-mail :  1219345363@qq.com")
		call append(line(".")+3, "*    > C-time :  ".strftime("%c"))
		call append(line(".")+4, "*******************************************************************/")
		call append(line(".")+5, "")
		if &filetype == 'cpp'
		   call append(line(".")+6, "#include<iostream>")
		   call append(line(".")+7, "using namespace std;")
	       call append(line(".")+8, "")
		endif
       
		if &filetype == 'c'
			call append(line(".")+6, "#include<stdio.h>")
		    call append(line(".")+7, "")
		endif

		 "新建文件后，自动定位到文件末尾（这个功能实际没有被实现，即下面的语句无效，暂不知道原因）
		 autocmd BufNewFile * normal G
endfunc

"C,C++ 按F5编译运行
map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec "!g++ % -o %<"
        exec "!time ./%<"
    elseif &filetype == 'cpp'
        exec "!g++ % -o %<"
        exec "!time ./%<"
    endif    
endfunc

"C,C++的调试
map <F8> :call Rungdb()<CR>
func! Rungdb()
	exec "w"
	exec "!g++ % -g -o %<"
	exec "!gdb ./%<"
endfunc


