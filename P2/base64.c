/*
* @ date: 11/05/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / Binary string to Base64 
* [I] compile: gcc base64.c -o base64.c
* [I] usage: ./base64.c [cipher/decipher] [string]
* i.e. ./base64 cipher "000111 101000 100101 011010"
* i.e. ./base64 decipher "Hola"
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
char base64[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','\0'};

int main(int argc, char const *argv[]){
	if(!(argc>2)){
		perror("Few arguments");
		exit(EXIT_FAILURE);
	}
	char input_string[30], binary_string[30]=" ", bs[9];
	unsigned char value=0;
	strcpy(input_string, argv[2]);
	if(!strcmp("cipher", argv[1])){
		strcat(binary_string, input_string);
		for(int j=0;binary_string[j];j++){
			if(binary_string[j] == ' '){
				strncpy(bs, binary_string+j, 7);
				// printf("=> %s\n", bs);
				value = (int)strtol(bs, NULL, 2);
				// for(int i=0;i<8;i++)
				// 	printf("%d", !!((value << i) & 0x80));
				puts("");
				// printf("In decimal: %d\n", value);
				printf("-> %c\n", base64[value]);
			}
		}
	}
	return 0;
}