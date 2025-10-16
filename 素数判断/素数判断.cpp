#include<stdio.h>
#include<math.h>

int prime(int x);

int main()
{
	int n;
	int i1,j1;
	int fl1,fl2;
	do
	{
		printf("输入6-200之间的一个偶数：");
		scanf("%d",&n);
		if( n<6 || n>200 )	continue;
		for(int i=2;i<n;i++)
		{
			for(int j=2;j<n;j++)
			{
				if(i+j==n)
				{
					fl1=0,fl2=0;
					fl1=prime(i);
					fl2=prime(j);
					if(fl1==1 && fl2==1 && i<=j)
					{
						i1=i,j1=j;
						printf("%d = %d + %d\n",n,i1,j1);
					}					
				}
			}
			
		}
		
	}while( n<6 || n>200 );
}

int prime(int x)
{
	int n=ceil(sqrt(x));
	int flag = 1 ;
	for(int i=2;i<=n;i++)
	{
		if( x % i == 0 )
			flag=0;
	}
	return flag;
}
