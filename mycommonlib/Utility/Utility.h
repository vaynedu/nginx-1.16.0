//
// Created by vaynedu on 2019/12/25.
//

#ifndef UTILITY_H
#define UTILITY_H

// c++
#include <iostream>
#include <string>
#include <map>
#include <vector>

// c
#include <cstring> //string.h
#include <stdint.h> //uint32_t uint64_t


// linux c
#include <unistd.h> // close
#include <sys/types.h>  //socket
#include <sys/socket.h> //socket
#include <sys/ioctl.h>
#include <net/if.h> //ifname
#include <netinet/in.h>
#include <arpa/inet.h> //inet_pton inet_ntoa

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


    /*
     * ip相关操作
     * 1. 获取网卡ip
     * 2. ip和整数相互转化 并且支持ipv6
     * 3. 网络序和主机序转化
     * */
public:
    static uint32_t get_networkcard_ip(const char *ifname);
    static uint32_t inet_p2n_ipv4(const char *ip_addr);
    static string   inet_n2p_ipv4(uint32_t ipv4);
    static uint32_t ipv4_to_uint32(const char *ip_addr);
    static string   uint32_to_ipv4(uint32_t ipv4);

    // 预留ipv6
    // static uint64_t inet_p2n_ipv6(const char *ip_addr);
    // static string inet_n2p_ipv6(uint64_t ipv4);



    /*
     * 字符串相关操作
     * 1. 分割字符串
     * 2. 去除字符串两端'\t\r \n'
     * 3. 删除字符串的某些字符
     *
     *
     *
     * */
public:
    static void split_v1(const string &str, vector<string> &v, const char delims = '/');
    static void split_v2(const string &str, vector<string> &v, const string& delims = " \t\n\r");
    static string trim_string(const string &str, const char *delims); //delims = " \t\n\r"
    static void delete_all_space(string &s, const string &mark);



    /*
     * http相关操作
     * 1. 获取url中的参数
     * 2. 获取域名
     * 3. 获取文件类型
     * 4. 获取url中的按照/划分的每一段 /a/b/c/d?
     *
     * */

public:
    static int get_url_args(map<string, string> &url_args, const string &url_params);
    static int get_domain(const string  &url, string &domain, bool is_http);
    static int get_file_type(const string &file_name, string &file_type);
    static int get_urlpath_slashsplit(map<int, string> &url_path, const string &url);




};




#endif //UTILITY_H
