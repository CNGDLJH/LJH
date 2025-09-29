#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    double t,p;
    int s;
    scanf("%lf %d %lf",&t,&s,&p);
    if(t>=0)
	{
		printf("+%.1lf\n",t);
	}
	else
	{
		printf("%.1lf\n",t);
	}
    printf("%08d%%\n",s);
    printf("%-12.2lf",p);
	return 0;
}

