#! /bin/bash

# 作者原文
# .git文件过大，github仓库瘦身
# https://blog.csdn.net/luchengtao11/article/details/82531044

# 1. 扫描大文件 
# git verify-pack -v .git/objects/pack/pack-b421a1e1cec3b8b2b27d1061f5853197d25a9c87.idx | sort -k 3 -n | tail -5
# 871b30bb407e6e94696404d07e75cd3bcb61cc9e blob   4353752 1618558 172748915
# 7c8af76fc6aea912a787be4850c794811ff78d7a blob   7659093 6221765 35149263
# 702890da7a3bfea7267948506559c8a5bbadb2a2 blob   33589933 32229261 2920002
# b6b18ff46815ee1d95ab31afbd8ac863a2469690 blob   51127867 49137643 123607251
# 9a15fb683db7b7f9fe56dd48f9381c1d26c46d31 blob   88015321 82235890 41371090



# 2. 寻找大文件
# git rev-list --objects --all | grep b6b18ff46815ee1d95ab31afbd8ac863a2469690 
# b6b18ff46815ee1d95ab31afbd8ac863a2469690 books/nginx/深入理解Nginx.pdf

# 3. 将该文件从历史记录的所有 tree 中移除
# git log --pretty=oneline --branches --  books/nginx/深入理解Nginx.pdf 
# e4e9aa26f0fa28f6148e212adb8846ade41f2b19 2019-07-10 02:26:02 将nginx相关书籍移动books仓库，nginx仓库建立索引即可
# b09845baa72ac261cad9f9868d705df395bd0a4f 2019-07-09 22:09:58 add books dir. add 《深入理解nginx》 《深入剖析nginx》 

# 4. 用 filter-branch 命令重写所有 commit 才能将文件从 Git 历史中完全移除
# git filter-branch --index-filter 'git rm --cached --ignore-unmatch  books/nginx/深入理解Nginx.pdf'
# Rewrite b09845baa72ac261cad9f9868d705df395bd0a4f (35/68)rm 'books/nginx/深入理解Nginx.pdf'
# Rewrite 4a84b3a679a75bbf239a59c588375a4c493d2713 (36/68)rm 'books/nginx/深入理解Nginx.pdf'
# Rewrite 2458e8e1b87903782c45c63041a8761411d2b8e1 (37/68)rm 'books/nginx/深入理解Nginx.pdf'
# Rewrite 16bbbd0bacd77e06fab5f1aeea933626b994ea4b (67/68)error: duplicate parent cf584e3b75d79a757681a3295c4b40ea24ed3aa6 ignored
# Rewrite 5dbebb8bd2f6891d9cf8dfbde4c01bf53fee4ff8 (68/68)
# Ref 'refs/heads/master' was rewritten 


cd  ../../
rm -fr  .git/refs/original/

git reflog expire --expire=now --all

git fsck --full --unreachable

git repack -A -d

git gc --aggressive --prune=now

git push --force

