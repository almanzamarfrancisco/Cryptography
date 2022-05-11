/*
* @ date: 08/03/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Implementing simple DES for cipher and decipher
* [I] compile: gcc sdes_key_schedule.c -o sdes_key_schedule
* [I] usage: ./sdes_key_schedule
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
void g(char k1[2][8], char *key);
void permutation(char *final, char *n, int p[], int size);
void round1(char *final_message, char *message, char *k1);

char english_alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};

int main(int argc, char const *argv[]){
	char key[11] = "1010000010\0", k[2][8]={"00000000", "00000000"};
	char *message = malloc(sizeof(char)*8);
	char *round1_message = malloc(sizeof(char)*8);
	message="10111101";
	char pm[11]="00000000000";
	int ip[] = {2,6,3,1,4,8,5,7};
	int initial_permutation[] = {2,6,3,1,4,8,5,7};
	printf("**SDES**\n");
	printf("original_key: \n\t%s\n", key);
	g(k, key);
	printf("Message: %s\n", message);
	permutation(pm, message, initial_permutation, 8);
	printf("pm: %s\n", pm);
	round1(round1_message, pm, k[0]);
	return 0;
}
void permutation(char *final, char *n, int p[], int size){
	int i=0;
	char t[11];
	t[size-1]='\0';
	printf("Permutation %d: %s\n\t", size, n);
	printf("n | ");
	for (i=1;i<=size;i++)
		printf("%2d ", i);
	printf("\n\t");
	for (i=0;i<size+2;i++)
		printf("-- ", i);
	printf("\n\tp | ");
	for (i=0;i<size;i++){
		printf("%2d ", p[i]);
		t[i] = n[p[i]-1];
	}
	printf("\n\tk | ");
	for (i=0; i<size+1;i++)
		printf("%2c ", n[i]);
	
	printf("\n\tr | ");
	for (i=0;i<size;i++)
		printf("%2c ", t[i]);
	t[size]='\0';
	strcpy(final, t);
	puts("");
}
void shift(char *prefinal_key, int times, char *direction, char *k1, char *k2){
	unsigned char kcs1=0,kcs2=0, mask1=0, mask2=0;
	char pk[11]="0000000000\0";
	kcs1 = (int) strtol(k1, NULL, 2);
	kcs2 = (int) strtol(k2, NULL, 2);
	mask1 = mask1 | kcs1;
	mask2 = mask2 | kcs2;
	if(!strcmp(direction, "<<")){ // TODO implement rigth side
		mask1 = mask1 >> 5 - times;
		mask2 = mask2 >> 5 - times;
		kcs1 = kcs1 << times;
		kcs2 = kcs2 << times;
	}
	else{
		perror("[E] Direction not valid in shift function");
		exit(0);
	}	
	kcs1 = kcs1 | mask1;
	kcs2 = kcs2 | mask2;
	kcs1 = kcs1 << 3;kcs1 = kcs1 >> 3;
	kcs2 = kcs2 << 3;kcs2 = kcs2 >> 3;
	printf("Circle shifted key (5 bits taken only): \n\tkcs1: ");
	for (int i = 0; i < 8; i++)
		printf("%d", !!((kcs1 << i) & 0x80));
	printf("\n\tkcs2: ");
	for (int i = 0; i < 8; i++)
		printf("%d", !!((kcs2 << i) & 0x80));
	for(int i=3;i<8;i++){ // To obtain only the less 5 significative bits of each part
		if(!!((kcs1 << i) & 0x80))
			pk[i-3] = '1';
		if(!!((kcs2 << i) & 0x80))
			pk[i+2] = '1';
	}
	strcpy(prefinal_key, pk);
}
void g(char subkeys[2][8], char *key){
	int p10[] = {3,5,2,7,4,10,1,9,8,6};
	int p8[] = {6,3,7,4,8,5,10,9};
	char kp[10], kp1[6], kp2[6], prefinal_key1[11], prefinal_key2[10];
	permutation(kp, key, p10, 10);
	char final_subkey1[8],final_subkey2[8];
	printf("\n\n -> Permuted key: %s \n\n", kp);
	strncpy(kp1, kp, 5);kp1[5]='\0';
	strncpy(kp2, kp+5, 5);kp2[5]='\0';
	printf("Splitted key: \n");
	printf("\tkp1: %s \n\tkp2: %s\n", kp1, kp2);
	shift(prefinal_key1, 1, "<<", kp1, kp2);
	printf("\nPrefinal key 1:  %s\n", prefinal_key1);
	permutation(final_subkey1, prefinal_key1, p8, 8);
	printf("\n=> Final subkey 1:  %s\n", final_subkey1);
	strncpy(kp1, prefinal_key1, 5);kp1[5]='\0';
	strncpy(kp2, prefinal_key1+5, 5);kp2[5]='\0';
	printf("Splitted key: \n");
	printf("\tkp1: %s \n\tkp2: %s\n", kp1, kp2);
	shift(prefinal_key2, 2,"<<", kp1, kp2);
	printf("\nPrefinal key 2:  %s\n", prefinal_key2);
	permutation(final_subkey2, prefinal_key2, p8, 8);
	printf("\n=> Final subkey 2:  %s\n", final_subkey2);
	strcpy(subkeys[0], final_subkey1);
	strcpy(subkeys[1], final_subkey2);
}
void round1(char *final_message, char *message, char *k1){
	char *l=(char*)malloc(sizeof(char)*4), *r=(char*)malloc(sizeof(char)*4);
	char *pl=(char*)malloc(sizeof(char)*4), *pr=(char*)malloc(sizeof(char)*4);
	unsigned char xor_message;
	int ep[]={4,1,2,3,2,3,4,1};
	printf("Round1: %s\n\t", message);
	strncpy(l,message,4);
	strncpy(r,message+4,4);
	printf("L: %s, R:%s\n", l, r);
	permutation(pr, r, ep, 8);
	unsigned char prc = (int) strtol(pr, NULL, 2);
	unsigned char k1c = (int) strtol(k1, NULL, 2);
	xor_message = prc ^ k1c;
	for (int i = 0; i < 8; i++){
		printf("%d", !!((xor_message << i) & 0x80));
	}
	printf("\n");
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