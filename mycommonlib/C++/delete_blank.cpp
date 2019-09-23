/*******************************************************************
*    > F-Name :  delete_blank.cpp
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Sun 21 Jul 2019 08:54:03 PM CST
*******************************************************************/

#include<iostream>
#include <map>
#include <string>

using namespace std;

/*
 * 去除字符串两端的空格、换行符
 * delims = " \t\n\r"
 *
 * */

string trim_string(const string &str, const char *delims)
{
	if(str.empty()) return "";

	string::size_type start_pos = str.find_first_not_of(delims);
	string::size_type end_pos   = str.find_last_not_of(delims);

	string::const_iterator s = (start_pos == string::npos) ? str.begin() : (str.begin() + start_pos);
	string::const_iterator e = (end_pos == string::npos) ? str.end() : (str.end() + 1);

	return string(s, e);
}


void delete_all_space(string &s, const string &mark)
{
	string::size_type nSize = mark.size();

 	while(1)
	{
		string::size_type pos = s.find(mark);
		if(pos == string::npos)
		{
   			return;
		}

		s = s.erase(pos, nSize);
   	}
}



int main(int argc, char *argv[])
{
    string s = " abc  def\"   ";
	string b = "abcdef";
	delete_all_space(s, " ");
	cout << ((s==b)? "yes": "no")<< endl;
   
	cout << s << endl;
	cout << b << endl;


	string str = trim_string("  111111     22222  ", " \t\n\r");
	cout << str << endl;

	
    return 0;
}

