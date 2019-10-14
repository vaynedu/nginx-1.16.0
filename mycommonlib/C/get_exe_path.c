/*******************************************************************
*    > F-Name :  get_exe_path.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Mon 14 Oct 2019 10:55:55 AM CST
*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <libaio.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <inttypes.h>

//gcc -o get_exe_path get_exe_path.c

/*
 * print
 *
 * /data/lotluck/nginx-1.16.0/mycommonlib/C/get_exe_path
 * /data/lotluck/nginx-1.16.0/mycommonlib/C/
 *
 * */

char *get_exe_path(char *buf, int count)
{
    int i;
    int rslt = readlink("/proc/self/exe", buf, count);
    if(rslt < 0 || rslt >= count - 1){
       return NULL;
    }

    buf[rslt] = '\0';

    printf("%s\n", buf);
    for(i = rslt; i >= 0; i--){
        if(buf[i] == '/'){
           buf[i+1] = '\0';
           break;
        }
    }
    return buf;
}


int main()
{
    char path[1024];
    printf("%s\n", get_exe_path(path, 1024));

    return 0;
}
