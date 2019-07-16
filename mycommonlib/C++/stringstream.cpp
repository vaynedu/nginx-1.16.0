#include <iostream>
#include "./include/md5.h"
#include <sstream>
#include <iomanip>

using namespace std;

/*
 *
 * g++ -c -o 1.o 1.cpp
 *
 * g++ -o 1 1.o md5.o
 *
 *
 *  ./1
 */

    char x[] = "0123456789abcdef";
    unsigned i = 0;
	for(i = 0; i < sizeof(md5); i++)
	{
		code[i*2]   = x[md5[i] >> 4];
		code[i*2+1] = x[md5[i] & 0xF];
	}
	code[32] = 0x0;


int main()
{
   unsigned char md5[16];
   MD5::Digest((const char *)"1234", sizeof("1234")-1, md5);

   stringstream auth_string;
   for (unsigned i=0; i<sizeof(md5); i++) {
              int x = md5[i];
              auth_string << std::hex << std::setw(2) << std::setfill('0') << x;
   }   

   cout << auth_string.str() << endl;
   return 0;
}

