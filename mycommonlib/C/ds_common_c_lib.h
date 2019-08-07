#include <stdio.h>


/*定义了__DEBUG就使用 ifdef里面，否则就是else中的DEBUG，什么不输出*/
#define __DEBUG

#ifdef __DEBUG
#define  DEBUG(format,...)  printf("File: "__FILE__", Line: %05d, (%s): "format"\n", \
                                  __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define  DEBUG(format,...)
#endif


/*  "#" 运算符用在预编译时期，用于将宏参数转换为字符串，即是加上双引号 */
#define CSTR(s) #s


/* ##运算符用于在预编译期粘连两个符号, 连接操作， 相当于strcat*/
#define CSTRCAT(a,b) CSTR(a##b)


