/*******************************************************************
*    > F-Name :  split.cpp
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Mon 02 Sep 2019 08:09:37 PM CST
*******************************************************************/

#include<iostream>
#include<vector>

using namespace std;

/* Summary:  use charactor to split string
 *
 * Parameters:
 *           str :  src string
 *            v  :  remain vector  after split str
 *        delims :  split  charactor 
 *
 * Return : 
 *
 * */


static void split_v1(const string &str, vector<string> &v, const char delims = '/')
{
	v.clear();

	int curr = 0;
	int last = 0;
	int str_size = str.length();

	while(curr < str_size)
	{
		if(str[curr] == delims)
		{
			if(curr - last > 0)
			{
               v.push_back(str.substr(last, curr - last));
			}
			/*记录curr的下一个位置， 跳过delims*/
			last = curr + 1; 
		}

		++curr;
	}

	if(curr - last > 0)
	{
		v.push_back(str.substr(last, curr -last));
	}

	return;

}


static void split_v2(const string &str, vector<string> &v, string delims = " \t\n\r")
{
	v.clear();

	int curr = 0;
	int last = 0;
	int str_size = str.length();

	while(curr < str_size)
	{
		if(delims.find(str[curr]) != string::npos)
		{
			if(curr - last > 0)
			{
                v.push_back(str.substr(last, curr - last));
            }
	
			last = curr + 1;
		}
       
	   
		++curr;

	}

	if(curr - last > 0)
	{
		v.push_back(str.substr(last, curr-last));
	}

    return;
}




int main(int argc, char *argv[])
{
    string str = "1049_M0115200004 PB0mG3yaffG  1001669735.f9934.18.ts";

	vector<string> v1;

	split_v1(str,v1, '.');

    vector<string>::iterator it = v1.begin();
	for(; it != v1.end(); it++)
	{
		cout << *it << endl;
	}

	cout << v1[0] + '.' +  v1[1] << endl;

    /*-----------------------------------------------------------------*/

    vector<string> v2;
    split_v2(str, v2);

    vector<string>::iterator it2 = v2.begin();
    for(; it2 != v2.end(); it2++)
	{
		cout << *it2 << endl;
	}
   
	cout << v2[0] + '.' + v2[1] << endl;


	return 0;
}



