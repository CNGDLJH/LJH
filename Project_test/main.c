#include <stdio.h>
#include <stdlib.h>
#include "func.h" 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a=2,b=3;
    printf("%d",add(a,b));
    extern int c;
    printf("%d",c);
	return 0;
}
