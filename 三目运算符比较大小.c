#include<stdio.h>
int main()
{
	int a,b,c;
	scanf("%d" "%d" "%d",&a,&b,&c);
	int max = a > (b > c ? b : c) ? a : (b > c ? b : c);
	int min = a < (b < c ? b : c) ? a : (b < c ? b : c);
	int med = a+b+c-max-min;
	printf("%d %d %d",max,med,min);
	return 0;
}
//edit
