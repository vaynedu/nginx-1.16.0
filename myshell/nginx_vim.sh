#! /bin/bash

# author : vaynedu
# e-mail : 

# 1. nginx的配置高亮
#  nginx-1.16.0/contrib/vim/syntax/nginx.vim 

mkdir -p ~/.vim/syntax

# 强制覆盖nginx.vim配置
\cp ../contrib/vim/syntax/nginx.vim  ~/.vim/syntax/

# 管他存不存在暴力追加，返回多了也不会有事情
echo "au BufRead,BufNewFile /usr/local/nginx/* set ft=nginx" >> ~/.vim/filetype.vim


# 2. contrib 目录下的这三个一般用不到, 也可以全部赋值过去
# ftdetect  ftplugin  indent
# 判断是否是nginx配置文件的文件是 ftdetect/nginx.vim

mkdir -p ~/.vim/ftdetect
mkdir -p ~/.vim/ftplugin
mkdir -p ~/.vim/indent


\cp ../contrib/vim/ftdetect/nginx.vim  ~/.vim/ftdetect/
\cp ../contrib/vim/ftplugin/nginx.vim  ~/.vim/ftplugin/
\cp ../contrib/vim/indent/nginx.vim    ~/.vim/indent/

