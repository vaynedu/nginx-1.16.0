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






































