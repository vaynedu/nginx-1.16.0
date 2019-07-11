#include <iostream>
#include <stdio.h>
#include <stdint.h> // for int64_t
#include <string>   // for string
#include <stdlib.h> // for strtol


/*
 *  目前只实现了C++的int2str转化，稍后会完善C语言的int2str
 *
 * */



/*int snprintf(char *str, size_t size, const char *format,...)*/
/*返回值：成功返回写入的字符串的长度，出错返回负值*/
/*当写入的字符串大于size的时候，会在size截断，最后一个字符\0，这里要判断返回值和buf size的大小。*/
/*snprintf的返回值是欲写入的字符串长度，而不是实际写入的字符串度*/

static  inline  std::string int2string(int64_t v)
{
    int ret = -1;
    char buf[32] = {'\0'};

    ret = snprintf(buf, sizeof(buf), "%lld" , v);
    if(ret < 0 || ret >= sizeof(buf))
    {
       return std::string("");
    }

    return std::string(buf);
}



/* 将nptr字符串根据base来转化成有符号或者无符号的整数
 * stroul会跳过前面的空格，遇到+-或者数字开始，遇到非数字停止
 * long int strtol(const char *nptr, char **endptr, int base)
 * long long strtoll(cost char *nptr, char **endptr, int base)
 * unsigned long int stroul(cost char *nptr, char **endptr, int base)
 * unsigned long long stroull(cost char *nptr, char **endptr, int base)
 */

 static inline int64_t string2int(std::string s)
 {
    return  strtoll(s.c_str(), 0, 10);
 }



int main()
{
   std::string str = int2string(100);

   std::cout << str << std::endl;

   int64_t v = string2int("  -324299099");
   std::cout <<v << std::endl;


   return 0;
}



