/*
* @ date: 08/10/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / Binary string to Base64 
* [I] compile: gcc base64.c -o base64
* [I] usage: ./base64 [binary/plaintext] [string]
* i.e. ./base64 binary "000111 101000 100101 011010 001100 101110 100111 011101 101000"
* i.e. ./base64 plaintext "Hola Mundo"
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
char base64[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','\0'};

void put_binary(int);

int main(int argc, char const *argv[]){
	if(!(argc>2)){
		perror("[E] Too few arguments");
		exit(EXIT_FAILURE);
	}
	char input_string[100], string[150]=" ", ss[20];
	unsigned char value=0;
	strcpy(input_string, argv[2]);
	strcat(string, input_string);
	if(!strcmp("binary", argv[1])){
		for(int j=0;string[j];j++){
			if(string[j] == ' '){
				strncpy(ss, string+j, 7);
				value = (int)strtol(ss, NULL, 2);
				printf("%c", base64[value]);
			}
		}
		puts("");
	}
	else{
		if(!strcmp("plaintext", argv[1])){
			strcat(string, " ");
			int last_space = 0, transformed[50], counter=0;
			printf("-> String: %s\n", string);
			for(int j=0;string[j];j++){
				if(string[j] == ' '){
					strncpy(ss, string+last_space, abs(last_space-j));
					last_space = j+1;
					// printf("%s \t", ss);
					for(int i=0;ss[i];i++){
						if(ss[i]>64 && ss[i]<97){
							transformed[counter] = ss[i]-65;
							counter++;
						}
						if(ss[i]>96){
							transformed[counter] = ss[i]-71;
							counter++;
						}
						if(ss[i]>48 && ss[i]<58){
							transformed[counter] = ss[i]-71;
							counter++;
						}
						if(ss[i]=='+'){
							transformed[counter] = ss[i]-71;
							counter++;
						}
						if(ss[i]=='/'){
							transformed[counter] = ss[i]-71;
							counter++;
						}
					}
					strcpy(ss, "                   ");
				}
			}
			puts(transformed);
			for(int i=0;i<counter;i++)
				put_binary(transformed[i]);
			puts("");
		}
		else
			printf("Second argument not recognized\n");
	}
	return 0;
}
void put_binary(int n){
	for(int m=2;m<8;m++){
		if(!!((n << m) & 0x80))
			putchar('1');
		else
			putchar('0');
	}
	putchar(' ');
}