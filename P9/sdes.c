/*
* @ date: 08/03/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Implementing simple DES for cipher and decipher
* [I] compile: gcc sdes.c -o sdes
* [I] usage: ./sdes {-c|-d} {plaintext|ciphertext} {a of key}
*	where -c is for cipher and -d for decipher
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

int get_index_of(char);
int* get_indexes_of(char*);
char get_letter_of(int n);
char* get_text_of(int*, int);
char* trim(char *s);
int16_t g(int16_t key);

void print_16(int16_t);


char english_alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};

int main(int argc, char const *argv[]){
	int16_t original_key=642, k1=0, k2=0;// 1010000010
	printf("**SDES**\n");
	printf("original_key: \n\t");
	print_16(original_key);
	k1 = g(original_key);
	puts("");
	// printf("k1: \n\t");
	// print_16(k1);

	return 0;
}
char* permutation_10(int16_t n){
	int p[] = {3,5,2,7,4,10,1,9,8,6,0,0,0,0,0,0}, a=0;
	char s[17];
	static char t[17];
	s[16]='\0';t[16]='\0';

	printf("permutation_10: \n\t");
	printf("n | ");
	for (int i=1;i<=16;i++)
		printf("%2d ", i);
	printf("\n\t");
	for (int i=0;i<17;i++)
		printf("-- ", i);
	printf("\n\tk | ");

	n=n<<6;
	for (int i=0; i<16;i++){
		a = !!((n << i) & 0x8000);
		printf("%2d ", a);
		s[i] = a+'0';
	}
	printf("\n\tp | ");

	for (int i=0;i<16;i++){
		printf("%2d ", p[i]);
		if(p[i]==0 && i>9)
			t[i]='0';
		t[i] = s[p[i]-1];
	}
	printf("\n\tr | ");
	for (int i=0;i<16;i++)
		printf("%2c ", t[i]);
	return t;
}
int16_t g(int16_t key){
	char aux[10];
	printf("\n => %s", permutation_10(key));
	return 0;
}
void print_16(int16_t n){
	for (int i = 0; i < 16; i++)
		printf("%d", !!((n << i) & 0x8000));
	puts("");
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