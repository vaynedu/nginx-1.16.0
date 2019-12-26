//
// Created by vaynedu on 2019/12/25.
//

#include <iostream>
#include <cstring> // string.h

#include <sstream> //stringstream
#include <iomanip> //std::setfill, std::setw

#include <algorithm> //transform

#include "Utility.h"



int  Utility::get_md5(const char* data, unsigned len,  unsigned char md5[16]) {
    if(data == nullptr || md5 == nullptr || len <= 0) return -1;

    MD5::GETMD5(data, len, md5);

    return 0;
}

bool Utility::is_same_md5(const unsigned char *s1, const unsigned char *s2) {
    if(s1 == nullptr || s2 == nullptr) return false;
    if(strlen((const char *)s1) != 16 || strlen((const char *)s2) != 16) return false;

    for(unsigned i = 0; i < 16; i++){
        if(s1[i] != s2[i]) return false;
    }

    return true;
}

string Utility::md5_to_hex(const unsigned char *data, unsigned len) {
    if(data == nullptr || len != 16) return "";

    stringstream ss;
    for(unsigned i = 0; i < len ; i++){
        int  x = data[i];
        ss << std::hex << std::setw(2) << std::setfill('0')	<< x;
    }
    return ss.str();
}

string Utility::hex_to_md5(const  char *data, unsigned len ) {
    if(data == nullptr || len != 32) return "";

    string str;
    char ch[3];
    for(unsigned i = 0; i < len/2; i++) {
        memcpy(ch, data + 2 * i, 2);
        ch[2] = '\0';
        str.push_back((char)strtol(ch, NULL, 16));
    }

    return str;
}

const static char hex_tower[] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f'
};
const static char hex_upper[] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
};

static int get_hex_value(const char c){
    switch (c){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': return 10;
        case 'A': return 10;
        case 'b': return 11;
        case 'B': return 11;
        case 'c': return 12;
        case 'C': return 12;
        case 'd': return 13;
        case 'D': return 13;
        case 'e': return 14;
        case 'E': return 14;
        case 'f': return 15;
        case 'F': return 15;
        defalut: return -1;
    }
}

int  Utility::hex_to_md5(const  char *data, unsigned len, unsigned char *md5, unsigned md5_len) {
    if(data == nullptr || len != 32 || md5 == nullptr || md5_len != 16) return -1;

    for(unsigned i = 0, j = 0; i < len ; i=i+2){
        int x = get_hex_value(data[i]);
        int y = get_hex_value(data[i + 1]);
        if(x < 0 || x > 16 || y < 0 || y > 16) return -2;

        int  m = x * 16  + y;
        md5[j++] = m;
    }

    return 0;
}

void Utility::md5_to_lower(string &s) {
    if(s.empty()) return;
    transform(s.begin(), s.end(), s.begin(), (int (*)(int))tolower);
}

void Utility::md5_to_upper(string &s) {
    if(s.empty()) return;
    transform(s.begin(), s.end(), s.begin(), (int (*)(int))toupper);
}

uint32_t Utility::get_networkcard_ip(const char *ifname) {
    if(!ifname)  return 0;

    register int fd, intrface;
    struct ifreq buf[10];
    struct ifconf ifc;
    unsigned ip = 0;

    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if(!ioctl(fd, SIOCGIFCONF, (char*)&ifc))
        {
            intrface = ifc.ifc_len / sizeof(struct ifreq);
            while(intrface-- > 0)
            {
                if(strcmp(buf[intrface].ifr_name, ifname) == 0)
                {
                    if(!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
                        ip = (unsigned)((struct sockaddr_in *)(&buf[intrface].ifr_addr))->sin_addr.s_addr;
                    break;
                }
            }
        }
        close(fd);
    }


    return ip;
}

uint32_t Utility::inet_p2n_ipv4(const char *ip_addr) {
    if(ip_addr == nullptr) return 0;

    // 这里直接处理返回的网络序，即是大端，
    struct in_addr in = {0};
    if(inet_pton(AF_INET, ip_addr, &in) > 0){
        return in.s_addr;
    } else {
        return 0;
    }

}

string Utility::inet_n2p_ipv4(uint32_t ipv4) {
    if(ipv4 == 0) return "0.0.0.0";

    static char buf[INET_ADDRSTRLEN] = {0};
    struct in_addr in;
    in.s_addr = ipv4;

    if(inet_ntop(AF_INET, &in, buf, sizeof(buf))){
        return string(buf);
    } else {
        return "";
    }
}

uint32_t Utility::ipv4_to_uint32(const char *ip_addr) {
    if(ip_addr == nullptr) return 0;

    // 另外一种思路可以使用sscanf和snprintf实现, 这里不使用，直接复用上面逻辑
    // sscanf(ip_str, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
    // sprintf(str, "%u.%u.%u.%u", c[3], c[2], c[1], c[0]);

    return ntohl(inet_p2n_ipv4(ip_addr));
}

string Utility::uint32_to_ipv4(uint32_t ipv4) {
    if(ipv4 == 0) return "0.0.0.0";

    return inet_n2p_ipv4(htonl(ipv4));
}

void Utility::split_v1(const string &str, vector<string> &v,  const char delims) {
    v.clear();

    int curr = 0;
    int last = 0;
    int str_size = str.length();

    while(curr < str_size){
        if(str[curr] == delims){
            if(curr - last > 0){
                v.push_back(str.substr(last, curr - last));
            }
            /*记录curr的下一个位置， 跳过delims*/
            last = curr + 1;
        }
        ++curr;
    }

    if(curr - last > 0){
        v.push_back(str.substr(last, curr -last));
    }
}

void Utility::split_v2(const string &str, vector<string> &v, const string& delims) {
    v.clear();

    int curr = 0;
    int last = 0;
    int str_size = str.length();

    while(curr < str_size){
        if(delims.find(str[curr]) != string::npos){
            if(curr - last > 0){
                v.push_back(str.substr(last, curr - last));
            }
            last = curr + 1;
        }
        ++curr;
    }

    if(curr - last > 0){
        v.push_back(str.substr(last, curr-last));
    }

}

string Utility::trim_string(const string &str, const char *delims) {
    if(str.empty()) return "";
    if(delims == nullptr) return str;

    string::size_type start_pos = str.find_first_not_of(delims);
    string::size_type end_pos   = str.find_last_not_of(delims);

    string::const_iterator s = (start_pos == string::npos) ? str.begin() : (str.begin() + start_pos);
    string::const_iterator e = (end_pos == string::npos) ? str.end() : (str.end() + 1);

    return string(s, e);
}

void Utility::delete_all_space(string &s, const string &mark) {
    string::size_type nSize = mark.size();
    while(true){
        string::size_type pos = s.find(mark);
        if(pos == string::npos){
            return;
        }
        s = s.erase(pos, nSize);
    }
}

int Utility::get_url_args(map<string, string> &url_args, const string &url_params) {
    if(url_params.empty())  return -1;

    url_args.clear();

    string key;
    string val;

    size_t last_pos = 0;
    size_t amp_pos = 0;  /* & == amp;*/
    size_t equal_pos = 0;

    while( (equal_pos =  url_params.find('=', last_pos)) != string::npos ){
        amp_pos = url_params.find('&',last_pos);
        if(amp_pos == string::npos){
            amp_pos = url_params.length();
        }

        key = url_params.substr(last_pos, equal_pos - last_pos);
        val = url_params.substr(equal_pos + 1,  amp_pos - (equal_pos + 1));

        url_args[key] = val;

        last_pos = amp_pos + 1;

        if(last_pos >= url_params.length()){
            break;
        }
    }
    return 0;
}

int Utility::get_domain(const string &url, string &domain, bool is_http) {
    if(url.empty())  return -1;


    domain = "";
    const string http  = "http://";
    const string https = "https://";

    if(url.find(http) != string::npos || url.find(https) != string::npos){
        string::size_type start_pos  = is_http ? http.length() : https.length();
        string::size_type end_pos = url.find("/", start_pos);
        if(end_pos != string::npos){
            domain = url.substr(start_pos, end_pos - start_pos);
        } else {
            domain = url.substr(start_pos);
        }
    }

    return 0;
}

int Utility::get_file_type(const string &file_name, string &file_type) {
    if(file_name.empty())  return -1;

    size_t pos = file_name.rfind(".");
    if(pos != string::npos){
        //	file_type = file_name.substr(pos + 1, file_name.length() - pos - 1);
        file_type = file_name.substr(pos + 1);
    }

    return 0;
}

int Utility::get_urlpath_slashsplit(map<int, string> &url_path, const string &url) {
    if(url.empty()) return -1;
    url_path.clear();

    /*
     *  url 的格式 /a/b/c/d, 以/进行划分
     */

    int i = 1;
    vector<string> v;
    split_v1(url, v, '/');
    if(v.empty()) return -2;

    for(const auto& item:v){
        url_path[i++] = item;
    }

    return 0;
}









































