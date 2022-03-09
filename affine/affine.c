/*
* @ date: 08/03/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Implementing affine cipher with english_alphabet
* [I] compile: gcc affine.c -o affine
* [I] usage: ./affine {-c|-d} {plaintext|ciphertext} {a of key}
*	where -c is for cipher and -d for decipher
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>

int gcd(int, int); // Greatest Common Divisor
int xgd(int, int); // Greatest Common Divisor inverse multiplicative
int* z_closure(int); // Z* - Returns all Z closure elements of a number
int* affine_key(int); // Implements all functions above for getting an affine key
char* affine_cipher(char*, int, int, int);
int get_index_of(char);
int* get_indexes_of(char*);
char get_letter_of(int n);

char english_alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};

int main(int argc, char const *argv[]){
	printf("Affine Cipher 1\n");
	if (argc<1){
		printf("Usage: affine_cipher {plain_text} {a}\n");
		return 0;
	}
	int a = atoi(argv[1]);
	int n = (sizeof english_alphabet) - 1;
	int *z = z_closure(n);
	int *k;
	char *p = "Hola a todos";
	char *cipher_text = "";
	printf("[I] Your input: a = %d, n = %d\n", a, n);
	printf("[I] plain_text: %s\n", p);
	printf("\t-> gcd(%d, %d) = %d \n", a, n, gcd(a,n));
	printf("\t-> xgd(%d, %d) = %d \n", a, n, xgd(a, n));
	printf("\t-> z_closure(%d): \n", n);
	k = affine_key(n);
	printf("[I] Affine key: a = %d, b = %d, a_inverse = %d\n", k[0], k[1], k[2]);
	cipher_text = affine_cipher(p, k[0], k[1], n);
	printf("\t%s \n", cipher_text);
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
	z = (int *) malloc( sizeof(int)*n );
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
char* trim(char *s){
	char *aux = malloc((sizeof(char))*sizeof s);
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
	int *aux = malloc(sizeof(int) * sizeof q);
	for (int i = 0; q[i]; i++)
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
char* get_text_of(int *n){
	char *t = malloc(sizeof(char) * sizeof(n));
	for (int i=0;i<=sizeof(n)+1; i++)
		t[i] = get_letter_of(n[i]);
	return t;
}
char* affine_cipher(char* plain_text, int a, int b, int n){
	char *c = "";
	int *indexes, *result;
	plain_text = trim(plain_text);
	indexes = get_indexes_of(plain_text);
	result = malloc(sizeof(int)*sizeof(indexes));
	for(int i=0;plain_text[i];i++)
		result[i] = ((indexes[i]*a)+b)%n;
	c = get_text_of(result);
	return c;
}
char* affine_decipher(char* cipher_text, int a, int b, int n){
	char plain_text = "";
	int *indexes, *result;

	return plain_text;
}