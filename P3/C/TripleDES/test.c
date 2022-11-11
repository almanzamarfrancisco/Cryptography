#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int p = 58, b=1, s=8 - (p - (p/8)*8);
	printf("Test: %d\n", s);
	printf("=> \n");
	b=b<<s;
		for(int m=0;m<8;m++){
			if(!!((b << m) & 0x80))
				putchar('1');
			else
				putchar('0');
	}
		printf("\n");
	return 0;
}