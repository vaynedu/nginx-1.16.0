#include <iostream>

#include "Utility.h"

using namespace std;

//g++ -std=c++11 main.cpp  md5.cpp Utility.cpp

int main()
{
    unsigned char  md5[16];
    Utility::get_md5("1234", strlen("1234"), md5);

    string hex1 = Utility::md5_to_hex(md5,sizeof(md5));
    cout << hex1 << endl; //81dc9bdb52d04dc20036dbd8313ed055

    Utility::md5_to_upper(hex1);
    cout << hex1 << endl; //81DC9BDB52D04DC20036DBD8313ED055


    string str("81DC9BDB52D04DC20036DBD8313ED055");
    string md5_char = Utility::hex_to_md5(str.c_str(), str.size());
    cout << md5_char.size() << endl; //16

    string hex2 = Utility::md5_to_hex((const unsigned char *)md5_char.c_str(),md5_char.size());
    cout << hex2 << endl;//81dc9bdb52d04dc20036dbd8313ed055


    unsigned char md5_1[16];
    Utility::hex_to_md5(str.c_str(), str.size(),md5_1, sizeof(md5_1));
    string hex3 = Utility::md5_to_hex(md5_1,sizeof(md5_1));
    cout << hex3 << endl; //81dc9bdb52d04dc20036dbd8313ed055


    return 0;
}