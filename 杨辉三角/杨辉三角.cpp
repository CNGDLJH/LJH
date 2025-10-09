#include<cstdio>
using namespace std;
int main()
{
    int n;
	scanf("%d",&n);
	int a[n+1][2*n+1];
	
	for(int i=0;i<n;i++) 
	{
		for(int j=0;j<2*n;j++)
		{
			a[i][j]=0;
		}
	}
//	for(int i=0;i<n;i++)
//	{
//		a[i][1]=1;
//	}
	
	a[0][n]=1;
	
	for(int i=1;i<n;i++) 
	{
		for(int j=1;j<2*n;j++)
		{
			a[i][j]=a[i-1][j+1]+a[i-1][j-1];
		}
	}
	
	for(int i=0;i<n;i++) 
	{
		for(int j=0;j<2*n;j++)
		{
			if(a[i][j]==0)
			{
				printf(" ");
			}
			else
			{
				printf("%d",a[i][j]);
			}
		}
		printf("\n");
	}
    return 0;
}
