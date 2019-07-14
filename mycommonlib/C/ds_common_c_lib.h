#include <stdio.h>


/*定义了__DEBUG就使用 ifdef里面，否则就是else中的DEBUG，什么不输出*/
#define __DEBUG

#ifdef __DEBUG
#define  DEBUG(format,...)  printf("File: "__FILE__", Line: %05d, (%s): "format"\n", \
                                  __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define  DEBUG(format,...)
#endif
