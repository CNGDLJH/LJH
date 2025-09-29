#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int a,b;
    double m;
    scanf("%d %d",&a,&b);
    m=(a*0.001+b*0.01)/2;
    printf("%.1lf",m);
	return 0;
}

