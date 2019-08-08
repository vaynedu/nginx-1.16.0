#include <stdio.h>
#include <stdint.h>



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


/* 转化大小写 */
#define ds_tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define ds_toupper(c)      (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

/*
 *  数值对齐
 *
 *  地址对齐
 * */

#define ds_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define ds_align_ptr(p, a)                                     \
	(u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

