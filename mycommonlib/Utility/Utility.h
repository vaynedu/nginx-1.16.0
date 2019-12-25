//
// Created by vaynedu on 2019/12/25.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <cstring> //string.h
#include "md5.h"

using namespace std;

class Utility
{
    /*
     *  md5相关操作
     * */
public:
    static int  get_md5(const  char* data, unsigned  len,  unsigned char md5[16]);
    static bool is_same_md5(const unsigned char s1[16], const unsigned char s2[16]);
    static string md5_to_hex(const unsigned char *data, unsigned len);
    static string hex_to_md5(const  char *data, unsigned len);
    static int hex_to_md5(const  char *data, unsigned len,unsigned char md5[16], unsigned md5_len);
    static void md5_to_lower(string &s);
    static void md5_to_upper(string &s);

};




#endif //UTILITY_H
