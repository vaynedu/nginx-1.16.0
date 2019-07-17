#! /bin/bash

note=$1
if [ -z "$note" ]; then
   echo "please add note"
   exit
fi

now_time=`date +"%F %T"`

git commit -m"${now_time} ${note}"

