/*
* @ date: 05/09/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Implementation of affine cipher with english_alphabet
* [I] compile: gcc affine_v1.c -o affine_v1
* [I] usage: ./affine {-c|-d} {plaintext|ciphertext} {a of key}
*	where -c is for cipher and -d for decipher
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_key_valid(int a, int b);
int gcd(int, int); // Greatest Common Divisor
int xgd(int, int); // Greatest Common Divisor (Extended Eucledean algorithm) 
void cipher(char*, char*, int, int, int);
void decipher(char*, char*, int, int, int);
int inverse_module(int, int);
int main(int argc, char const *argv[]){
	printf("Affine Cipher 2 (English alphabet)\n");
	if(argc<4){
		printf("Usage: ./affine_v1 {-c|-d} {a of key} {b of key} {plaintext|ciphertext}\n");
		exit(0);
	}
	int a = atoi(argv[2]), b = atoi(argv[3]), m = 26;
	if(gcd(a, m) != 1){
		perror("The Key a is not valid\n");
		exit(1);
	}
	char *plain_text, *cipher_text;
	plain_text  = (char*)malloc(sizeof(char)*strlen(argv[4]));
	cipher_text = (char*)malloc(sizeof(char)*strlen(argv[4]));
	if (!strcmp(argv[1], "-c")){
		strcpy(plain_text, argv[4]);
		printf("Plain text: %s\n", plain_text);
		cipher(plain_text, cipher_text, a, b, m);
		printf("Cipher text: %s\n", cipher_text);
	}else if(!strcmp(argv[1], "-d")){
		strcpy(cipher_text, argv[4]);
		printf("Cipher text: %s\n", cipher_text);
		decipher(cipher_text, plain_text, a, b, m);
		printf("\nPlain text: %s\n", plain_text);
	}
	else{
		printf("Invalid argument. Usage: ./affine_v1 {-c|-d} {plaintext|ciphertext} {a of key} {b of key}\n");
		exit(1);
	}
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
void cipher(char *plain_text, char *cipher_text, int a, int b, int m){
	int x = 0;
	for(int i=0;i<strlen(plain_text);i++){
		x = plain_text[i] - 65; // Based on ascii - A is 65
		if(!(x < 0))
			cipher_text[i] = (((a * x) + b) % m) + 65;
		else
			cipher_text[i] = ' ';
	}
}
void decipher(char *cipher_text, char *plain_text, int a, int b, int m){
	int a_inverse = inverse_module(a, m), x = 0;
	for(int i=0;i<strlen(cipher_text);i++){
		x = cipher_text[i] + 65;
		if(x != ' '+65)
			plain_text[i] = (a_inverse * (x - b) % m) + 65;
		else
			plain_text[i] = ' ';
	}
}
int inverse_module(int a, int m){
	for (int x = 1; x < m; x++)
		if (((a % m) * (x % m)) % m == 1)
			return x;
}