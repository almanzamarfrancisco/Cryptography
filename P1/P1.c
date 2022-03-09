/*
* @ date: 17/02/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 1. Function that implements...
*	
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>

int gcd(int, int); // Greatest Common Divisor
int xgd(int, int); // Greatest Common Divisor inverse multiplicative
int* z_closure(int); // Z* - Returns all Z closure elements of a number
int* affine_key(int); // Implements all functions above for getting an affine key

int main(int argc, char const *argv[]){
	printf("Practice 1\n");
	if (argc<3){
		printf("Usage: P1 {a} {n}\n");
		return 0;
	}
	int a = atoi(argv[1]);
	int n = atoi(argv[2]);
	int *z = z_closure(n);
	int *k;
	printf("[I] Your input: a = %d, n=%d\n", a, n);
	printf("-> gcd(%d, %d) = %d \n", a, n, gcd(a,n));
	printf("-> xgd(%d, %d) = %d \n", a, n, xgd(a, n));
	printf("-> z_closure(%d): \n\t", n);
	for (int i=0;z[i];i++)
		printf(", %d", z[i]);
	puts("");
	k = affine_key(n);
	printf("a=%d, b=%d, a_inverse=%d\n", k[0], k[1], k[2]);
	return 0;
}

int gcd(int a, int n){ // TODO: Change this function for an optimized function
	if(n==0) return a;
	return gcd(n,a%n);
}
int xgd(int a, int n){
	int u=a, v=n, x=0, x1=1, x2=0, q=0, r=0;
	if(!n>0){
		puts("[E] n must be greater than 0 (n>0)");
		return 0;
	}
	if(!(a<n)){
		puts("[E] n must be greater than a (a<n)");
		return 0;
	}
	if(!gcd(a,n)){
		puts("Greatest common divisor isn't 0, please retry");
		return 0;
	}
	while(u!=1){
		q=v/u;
		r=v-q*u;
		x=x2-q*x1;
		v=u;
		u=r;
		x2=x1;
		x1=x;
	}
	return x1%n;
}
int* z_closure(int n){
	int i=n, *z, s=0;
	z = (int *) malloc( sizeof(int)*n );// Size of the array must be like euler function
	while(i){
		if(gcd(n,i) == 1){
			z[s] = i;
			s++;
		}
		i--;
	}
	return z;
}
int* affine_key(int n){
	static int k[3];
	if(!(n>1)){
		puts("[E] n must be greater than 1 (n>1)");
		return 0;
	}
	int *z = z_closure(n);
	int a = (rand() % (n + 1));
	int b = (rand() % (n + 1));
	while(gcd(a,n)!=1)
		a = (rand() % (n + 1));
	int a_inverse = xgd(a, n);
	k[0]=a;
	k[1]=b;
	k[2]=a_inverse;
	return k;
}