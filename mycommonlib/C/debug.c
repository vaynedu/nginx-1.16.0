#include <stdio.h>


/*
 *
 * 来源于我的博客
 * https://blog.csdn.net/lotluck/article/details/52526925
 *
 */



/*定义了__DEBUG就使用 ifdef里面，否则就是else中的DEBUG，什么不输出*/ 
#define __DEBUG
 
#ifdef __DEBUG
#define  DEBUG(format,...)  printf("File: "__FILE__", Line: %05d, (%s): "format"\n", \
                                  __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define  DEBUG(format,...)
#endif




 
 
int main(int argc, char *argv[])
{
    // DEBUG();  // 出错, 不能传入空
    

    DEBUG("I love ying");
 
    DEBUG("I love ying  %d", 1314);
 
    DEBUG("I love ying, %s", "ying love me too");
    return 0;
}

