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
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int gcd(int, int); // Greatest Common Divisor
int xgd(int, int); // Greatest Common Divisor inverse multiplicative
int* z_closure(int); // Z* - Returns all Z closure elements of a number
// int* affine_key(int); // Implements all functions above for getting an affine key
int valid_numbers(int, int, int*);
char* affine_cipher(char*, int, int, int);
char* affine_decipher(char*, int, int, int);
int get_index_of(char);
int* get_indexes_of(char*);
char get_letter_of(int n);
char* get_text_of(int*, int);

char english_alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

int main(int argc, char const *argv[]){
	printf("Affine Cipher 1\n");
	if(argc<3){
		printf("Usage: affine_cipher {a} {b} {plain_text}\n");
		return 0;
	}
	int a = atoi(argv[1]), b = atoi(argv[2]);
	int n = (sizeof english_alphabet) - 1;
	int *z = z_closure(n), a_inverse=0;
	char *p = malloc(sizeof(char)*strlen(argv[3]));
	strcpy(p, argv[3]);
	char *cipher_text = "", *decipher_text = "";
	if(!valid_numbers(a, b, z))
		return 1;
	printf("[I] Your input: a = %d, b = %d, n = %d\n", a, b, n);
	printf("    plain_text: %s\n", p);
	printf("\t-> gcd(%d, %d) = %d \n", a, n, gcd(a,n));
	a_inverse = xgd(a, n);
	printf("\t-> xgd(%d, %d) = %d \n", a, n, a_inverse);
	printf("\t-> z_closure(%d): \n", n);
	printf("\t\t");
	for(int i=0;i<sizeof(z);i++)
		printf("%d, ", z[i]);
	puts("");
	printf("[I] Affine key: a = %d, b = %d, a_inverse = %d\n", a, b, a_inverse);
	cipher_text = affine_cipher(p, a, b, n);
	printf("\t-> cipher_text: %s \n", cipher_text);
	// decipher_text = affine_decipher(cipher_text, 15, 3, n);
	// printf("\t-> decipher_text: %s \n", decipher_text);
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
int valid_numbers(int a, int b, int* z){
	int a_valid=0, b_valid=0;
	for(int i=0;i<9;i++){
		if(z[i]==a)
			a_valid=1;
		if(primes[i]==a)
			a_valid=1;
		if(z[i]==b)
			b_valid=1;
		if(primes[i]==b)
			b_valid=1;
	}
	if(!a_valid){
		puts("[I] a is invalid, choose a valid value");
		return 0;
	}
	if(!b_valid){
		puts("[I] b is invalid, choose a valid value");
		return 0;
	}
	return 1;
}
int* z_closure(int n){
	int i=n, *z, s=0;
	z = (int *)malloc(sizeof(int)*n);
	while(i){
		if(gcd(n,i) == 1){
			z[s] = i;
			s++;
		}
		i--;
	}
	return z;
}
char* trim(char *s){
	char *aux = malloc((sizeof(char))*strlen(s));
	int i=0, j=0;
	for (i=0; s[i]; i++){
		if(s[i]!=' '){
			aux[j] = tolower(s[i]);
			j++;
		}
	}
	aux[j+1] = '\0';
	return aux;
}
int get_index_of(char q){
	int i = 0;
	while(english_alphabet[i]){
		if(english_alphabet[i] == q)
			return i;
		i++;
	}
}
int* get_indexes_of(char *q){
	int *aux = malloc(sizeof(int) * strlen(q));
	for (int i=0; q[i]; i++)
		aux[i] = get_index_of(q[i]);
	return aux;
}
char get_letter_of(int n){
	int i = 0;
	while(english_alphabet[i]){
		if(english_alphabet[i] == english_alphabet[n])
			return english_alphabet[n];
		i++;
	}
}
char* get_text_of(int *n, int size){
	char *t = malloc(sizeof(char) * size);
	for (int i=0;i<size; i++)
		t[i] = get_letter_of(n[i]);
	return t;
}
char* affine_cipher(char* plain_text, int a, int b, int n){
	char *c = "";
	int *indexes, *result;
	plain_text = trim(plain_text);
	indexes = get_indexes_of(plain_text);
	result = malloc(strlen(plain_text)*sizeof(int));
	for(int i=0;plain_text[i];i++){
		result[i] = ((indexes[i]*a)+b)%n;
	}
	c = get_text_of(result, strlen(plain_text));
	return c;
}
char* affine_decipher(char* cipher_text, int a_inverse, int b, int n){
	char *plain_text = "";
	int *indexes, *result;
	indexes = get_indexes_of(cipher_text);
	result = malloc(strlen(cipher_text)*sizeof(int));
	for(int i=0;cipher_text[i];i++){
		// result[i] = modulo((a_inverse*(indexes[i]-b)), n);
		result[i] = (a_inverse*(indexes[i]-b))%n;
		if (result[i] < 0) 
			result[i] += n;
		printf("%d \n", result[i]);
	}
	plain_text = get_text_of(result, strlen(cipher_text));
	return plain_text;
}