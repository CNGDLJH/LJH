#include<stdio.h>
#include<math.h>
 
int main() 
{
    int n,sum=0,ct=0,m[10]={0};
    scanf("%d",&n);
    int a=n;
	while(a!=0)	
	{
		sum=sum*10+a%10;
		a/=10;
	}
	printf("n �ľ����� = %d\n",sum);
	printf("�� = %d\n",sum+n);
	int s=sum+n;
	while(s!=0)
	{
		m[ct]=s%10;
		ct++;
		s/=10;
	} 
	int flag=0;
	s=sum+n;
	for(int i=ct-1;i>=0;i--)
	{
		int tp=s%10;
		if(tp!=m[i])
		{
			flag=1;
			break;
		}
		s/=10;
	}
	if(flag==1)
	{
		printf("�ǻ��ĺ�");
	}
	else
	{
		printf("���ĺ�");
	}
} 
