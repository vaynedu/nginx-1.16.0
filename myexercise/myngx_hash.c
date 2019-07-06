#include <stdio.h>
#include <stdint.h>

//gcc -m32 test_ngx_hash_elt_t.c
//pragma 控制内存是否对齐


//#pragma  pack(1)
typedef struct {  
    void             *value;            //即为key-value中对应的value  
    unsigned short    len;              //为key-value中key的长度  
    /*
     * name[1]为key的首地址
     * 这里是非常重要的一个技巧，C语言的柔性数组(可变长数组)
     * 可以申请一段连续的空间
     */
    unsigned char    name[1];            
} ngx_hash_elt_t;  

//#pragma  pack()

int main()
{
    printf("sizeof(ngx_hash_elt_t) = %d\n", sizeof(ngx_hash_elt_t));
    return 0;
}
