/*******************************************************************
*    > F-Name :  get_domain.cpp
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Sat 21 Sep 2019 09:28:02 PM CST
*******************************************************************/

#include<iostream>
#include<string>

using namespace std;


int get_domain(const string  &url, string &domain, bool is_http)
{
	if(url.empty()) 
	{
		return -1;
	}
 
	domain = "";

	const string http  = "http://";
	const string https = "https://";

	if(url.find(http) != string::npos || url.find(https) != string::npos)
	{
		string::size_type start_pos  = is_http ? http.length() : https.length();
		string::size_type end_pos = url.find("/", start_pos);
		if(end_pos != string::npos)
	    {
			domain = url.substr(start_pos, end_pos - start_pos);
		}
		else
		{
			domain = url.substr(start_pos);
		}
		
	}

	return 0; 

}


int main(int argc, char *argv[])
{
	string http_domain;
	get_domain("http://aaa.bbb.com/1.mp4", http_domain, true);
    cout << http_domain << endl;

	string https_domain;
	get_domain("https://111.222.333", https_domain, false);
    cout << https_domain << endl;


    
	return 0;
}
