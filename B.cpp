#include<cstring>
#include<iostream>
using namespace std;
void px(int s[])
{
	int tp;
	for (int i=0;i<200;i++)
	{
		for(int j=i+1;j<200;j++)
		{
			if(s[i]>s[j])
			{
				tp=s[i];
				s[i]=s[j];
				s[j]=tp;
			}
		}
	}
}
int main()
{
	int a[200],b[200],tp;
	int n,q,x,cot;
	cot=0;
	for(int i=0;i<200;i++)
		a[i]=200000;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>q;
		if(q==1)
		{
			cin>>x;
			a[i]=x;
			px(a);
		}
		else
		{
			px(a);
			b[cot]=a[0];
			a[0]=200000;
			cot++;
		}
	}
	for(int i=0;i<cot;i++)
	{
		if(i==cot-1)
		{
			cout<<b[i];
		}
		else
		{
			cout<<b[i]<<endl;
		}
	}
}
