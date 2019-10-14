/*******************************************************************
*    > F-Name :  get_cpu_num.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Mon 14 Oct 2019 11:29:08 AM CST
*******************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int get_cpu_num()
{
        char buf[16] = {0};
        int num;
        FILE* fp = popen("cat /proc/cpuinfo |grep processor|wc -l", "r");
        if(fp) {
           fread(buf, 1, sizeof(buf) - 1, fp);
           pclose(fp);
        }
        num = atoi(buf);
        if(num <= 0){
            num = 1;
        }
        return num;
}

int main(int argc, char *argv[])
{
    printf("cpu num = %d\n", get_cpu_num());
    int pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize = %d\n", pagesize);
    return 0;
}
