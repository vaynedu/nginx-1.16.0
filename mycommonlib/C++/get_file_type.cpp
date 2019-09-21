/*******************************************************************
*    > F-Name :  get_file_type.cpp
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Sat 21 Sep 2019 07:36:05 PM CST
*******************************************************************/

#include<iostream>
#include<string>

using namespace std;

/*
 * get file type
 *
 * szg_81926605_40000_05633ae391f44171bdb9fdd956aa207b.f30.mp4
 *
 * i050360h0um.322012.1.ts
 *
 * */
int get_file_type(string &file_name, string &file_type)
{
	if(file_name.empty())
	{
		return -1;
	}
	size_t pos = 0;

	pos = file_name.rfind(".");
	if(pos != string::npos)
	{
    //	file_type = file_name.substr(pos + 1, file_name.length() - pos - 1);
		file_type = file_name.substr(pos + 1);
	}

	return 0;

}



int main(int argc, char *argv[])
{

	string file_name = "/szg_81926605_40000_05633ae391f44171bdb9fdd956aa207b.f30.mp4";

	string file_type;

	get_file_type(file_name, file_type);

	cout << file_type << endl;


    return 0;
}
