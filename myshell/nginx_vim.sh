#! /bin/bash

# nginx的配置高亮

mkdir -p ~/.vim/syntax

# 强制覆盖nginx.vim配置
\cp ../contrib/vim/syntax/nginx.vim  ~/.vim/syntax/

# 管他存不存在暴力追加，返回多了也不会有事情
cd ~/.vim/
echo "au BufRead,BufNewFile /usr/local/nginx/* set ft=nginx" >> filetype.vim


