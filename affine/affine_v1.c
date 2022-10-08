/*
* @ date: 05/09/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Implementation of affine cipher with english_alphabet
* [I] compile: gcc affine.c -o affine
* [I] usage: ./affine {-c|-d} {plaintext|ciphertext} {a of key}
*	where -c is for cipher and -d for decipher
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_key_valid(int a, int b);
int gcd(int, int); // Greatest Common Divisor
int xgd(int, int); // Greatest Common Divisor inverse multiplicative
int main(int argc, char const *argv[]){
	printf("Affine Cipher 1\n");
	if(argc<3){
		printf("Usage: affine_cipher {a} {b} {plain_text}\n");
		exit(0);
	}
	int a = atoi(argv[1]), b = atoi(argv[2]), m = 26, x = 0;
	if(gcd(a, m) != 1){
		perror("The Key a is not valid\n");
		exit(1);
	}
	char *plain_text = "TWENTY FIFTEEN", *cipher_text;
	cipher_text = (char*)malloc(sizeof(char)*strlen(plain_text));
	for(int i=0;i<strlen(plain_text);i++)
		printf("%2c ", plain_text[i]);
	puts("");
	for(int i=0;i<strlen(plain_text);i++){
		x = plain_text[i] - 65; // Base on ascii - A is 65
		printf("%2d ", x);
		cipher_text[i] = (((a * x) + b) % m) + 65;
	}
	puts("\n-----------------------------------------------");
	for (int x = 0; x < strlen(plain_text); x++){
		printf("%2c ", cipher_text[x]);
	}
	// cipher_text[strlen(plain_text)] = '\0';
	puts("");
	for (int x = 0; x < strlen(plain_text); x++){
		printf("%2d ", cipher_text[x] - 65);
	}
	puts("");
	printf("Plain text: %s\n", plain_text);
	printf("Cipher text: %s\n", cipher_text);
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
	printf("\t xgd\n");
	while(u!=1){
		q=v/u;
		r=v-(q*u);
		x=x2-(q*x1);
		v=u;
		u=r;
		x2=x1;
		x1=x;
		printf("\t u=%d, v=%d, x=%d, x2=%d, q=%d, r=%d \n",u, v, x, x2, q, r);
	}
	puts("");
	return x1%n;
}