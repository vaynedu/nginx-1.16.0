//
// Created by vaynedu on 2019/12/25.
//

#include <iostream>
#include <cstring> // string.h

#include <sstream> //stringstream
#include <iomanip> //std::setfill, std::setw

#include <algorithm> //transform

#include "Utility.h"


static const uint32_t gCrc32Table[] = {
        0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL,
        0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
        0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L,
        0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
        0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
        0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
        0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
        0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
        0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L,
        0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
        0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L,
        0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
        0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L,
        0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
        0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
        0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
        0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL,
        0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
        0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L,
        0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
        0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
        0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
        0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL,
        0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
        0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
        0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
        0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L,
        0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
        0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L,
        0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
        0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L,
        0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
        0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL,
        0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
        0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
        0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
        0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL,
        0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
        0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL,
        0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
        0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L,
        0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
        0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L,
        0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
        0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
        0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
        0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L,
        0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
        0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
        0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
        0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L,
        0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
        0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL,
        0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
        0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
        0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
        0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L,
        0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
        0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L,
        0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
        0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L,
        0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
        0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
        0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};


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

void Utility::crc32_init(uint32_t &crc32) {
    crc32 = 0xFFFFFFFF;
}

void Utility::crc32_update(uint32_t &crc32, const unsigned char *buf, int len) {
    for(int i = 0; i < len; i++){
        crc32 = gCrc32Table[(crc32 ^ buf[i]) & 0xFF] ^ (crc32 >> 8);
    }
}

void Utility::crc32_final(uint32_t &crc32) {
    crc32 ^= 0xFFFFFFFF;
}

uint32_t Utility::get_crc32(const unsigned char *buf, int len) {
    if(buf == nullptr || len <= 0) return 0;

    uint32_t  crc32;

    crc32_init(crc32);
    crc32_update(crc32, buf, len);
    crc32_final(crc32);

    return crc32;
}

bool Utility::is_same_crc32(const uint32_t &crc1, const uint32_t &crc2) {
    return crc1 == crc2;
}



/*int snprintf(char *str, size_t size, const char *format,...)*/
/*返回值：成功返回写入的字符串的长度，出错返回负值*/
/*当写入的字符串大于size的时候，会在size截断，最后一个字符\0，这里要判断返回值和buf size的大小。*/
/*snprintf的返回值是欲写入的字符串长度，而不是实际写入的字符串度*/
string Utility::int2str(int64_t v) {
    int ret = -1;
    char buf[32] = {0};

    ret = snprintf(buf, sizeof(buf), "%" PRId64"\n", v);
    if(ret < 0 || ret >= sizeof(buf)) {
        return  string("");
    } else {
        return  string(buf);
    }
}

/* 将nptr字符串根据base来转化成有符号或者无符号的整数
 * stroul会跳过前面的空格，遇到+-或者数字开始，遇到非数字停止
 * long int strtol(const char *nptr, char **endptr, int base)
 * long long strtoll(cost char *nptr, char **endptr, int base)
 * unsigned long int stroul(cost char *nptr, char **endptr, int base)
 * unsigned long long stroull(cost char *nptr, char **endptr, int base)
 */

int64_t Utility::str2int(const string &s) {
    return strtoll(s.c_str(), 0, 10);
}

//c++11标准增加了全局函数std::to_string
string Utility::int2str_v2(int64_t v) {
    return std::to_string(v);
}

//C++11 std::stoi/stol/stoll等等函数
int64_t Utility::str2int_v2(const string &s) {
    return std::stoll(s, nullptr, 10);
}







































