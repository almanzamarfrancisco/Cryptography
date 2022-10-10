/*
* @ date: 09/10/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / Binary string to Base64 
* [I] compile: gcc base64.c -o base64
* [I] usage: ./base64 [-c|-d] [string]
* i.e. ./base64 -e "Hola Mundo"
* i.e. ./base64 -d "000111 101000 100101 011010 001100 101110 100111 011101 101000"
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

void put_binary(int, int);
void cipher_base64(char*, char*);

int main(int argc, char const *argv[]){
	if(!(argc>2)){
		perror("[E] Too few arguments. Usage: ./base64 [-c|-d] [string]\n");
		exit(EXIT_FAILURE);
	}
	char *plain_text, *cipher_text;
	if(!strcmp(argv[1],"-c")){
		int padding = strlen(argv[2]);
		while(padding%4)
			padding++;
		printf("Length of plain text: %d, padding: %d\n", strlen(argv[2]), padding);
		plain_text  = (char*)malloc(padding*sizeof(char*));
		cipher_text = (char*)malloc(padding*sizeof(char*));
		strcpy(plain_text, argv[2]);
		padding = padding - strlen(argv[2]);
		printf("padding: %d\n", padding);
		while(padding){
			strcat(plain_text, "=");
			padding--;
		}
		printf("Plain text: %s\n", plain_text);
		cipher_base64(plain_text, cipher_text);
		// printf("Cipher text: %s", cipher_text);
	}
	else if(!strcmp(argv[1],"-d")){
		printf("Here we're decrypting brooo!\n");
	}else
		perror("[E] Invalid argument. Usage: ./base64 [-c|-d] [string]\n");

}
void cipher_base64(char *plain_text, char* cipher_text){
	u_char x = 0, y = 0;
	printf("Plain text length: %d\n", strlen(plain_text));
	for (int i = 0; i < strlen(plain_text); i++){
		printf("%8c ", plain_text[i]);
	}
	puts("");
	for (int i = 0; i < strlen(plain_text); i++){
		printf("%8d ", plain_text[i]);
	}
	puts("");
	for (int i = 0; i < strlen(plain_text); i++){
		put_binary(plain_text[i], 0);
	}
	puts("");
	printf("Cipher text: %s\n", cipher_text);
	for(int i = 0;i<strlen(plain_text);i++){
		x = 0; y = 0;
		switch(i%4){
			case 0:
				x = 0xFC & plain_text[i];
				x = x >> 2;
			break;
			case 1:
				y = plain_text[i-1] << 6;
				y = y >> 2;
				x = 0xFC & plain_text[i];
				x = x >> 4;
				x = x | y;
			break;
			case 2:
				y = 0xF & plain_text[i-1];
				y = y << 2;
				x = 0xC0 & plain_text[i];
				x = x >> 6;
				x = x | y;
			break;
			case 3:
				x = 0x3F & plain_text[i-1];
			break;
		}
		printf("Obtained value: %2d -> ", x);
		put_binary(x, 2);
		puts("");
		cipher_text[i] = x;
	}
	for (int i = 0; i < strlen(cipher_text); i++){
		if(cipher_text[i] <= 25)
			cipher_text[i]+=65;
		else if(cipher_text[i]>25 && cipher_text[i]<=51)
			cipher_text[i]+=71;
		else if(cipher_text[i]>51 && cipher_text[i]<64)
			cipher_text[i]-=4;
		else
			perror("[E] Value out of base64 range");
		printf("%2c ", cipher_text[i]);
	}
	puts("");
	for (int i = 0; i < strlen(cipher_text); i++){
		printf("%2d ", cipher_text[i]);
	}
	puts("");
}
void put_binary(int n, int from){
	for(int m=from;m<8;m++){
		if(!!((n << m) & 0x80))
			putchar('1');
		else
			putchar('0');
	}
	putchar(' ');
}