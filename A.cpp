#include<cstring>
#include<iostream>
using namespace std;
int main()
{
	string s;
	cin>>s;
	string a,b,c;
	a='red';
	b='blue';
	c='green';
	if (s == a)
	{
		cout<<"SSS";
	}
	else if(s == b)
	{
		cout<<"FFF";
	}
	else if(s == c)
	{
		cout<<"MMM";
	}
	else
	{
		cout<<"Unknown";
	}
	return 0;
}
