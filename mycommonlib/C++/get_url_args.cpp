/*******************************************************************
*    > F-Name :  get_url_args.cpp
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Sat 21 Sep 2019 03:10:50 PM CST
*******************************************************************/

#include<iostream>
#include<map>
#include<vector>
#include<string>


using namespace std;

/*
 * 取出url参数放在map中 a=1&b=2&c=3
 *
 *
 *
 * */
int get_url_args(map<string, string> &url_args, string &url_params)
{
	if(url_params.empty())
	{
		return -1;
	}

	string key;
	string val;

    size_t last_pos = 0;
	size_t amp_pos = 0;  /* & == amp;*/
	size_t equal_pos = 0;

	while( (equal_pos =  url_params.find('=', last_pos)) != string::npos )
	{
	    amp_pos = url_params.find('&',last_pos);
	    if(amp_pos == string::npos)
		{
			amp_pos = url_params.length();
		}

		key = url_params.substr(last_pos, equal_pos - last_pos);
		val = url_params.substr(equal_pos + 1,  amp_pos - (equal_pos + 1));

		url_args[key] = val;

		last_pos = amp_pos + 1;

		if(last_pos >= url_params.length())
		{
			break;
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{

	map<string, string> url_args;

	string url_params = "cdncode=18907E7BE0798990%2F&index=2&xxxxx=18840&yyyyy=30000&brs=760272&bre=1190603&ver=4&stdfrom=5000";

	get_url_args(url_args, url_params);

	map<string, string>::iterator it = url_args.begin();
    for(; it != url_args.end(); it++)
	{
	   cout << it->first << "=" << it->second << endl;	
	}

    return 0;
}









