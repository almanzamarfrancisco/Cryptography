/*
* @ date: 17/05/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / OTP encipher 
* [I] compile: gcc OTP_encipher.c -o OTP_encipher
* [I] usage: ./OTP_encipher.c [plaintext]
* i.e. ./OTP_encipher.c "Hello  my name is Lucas"
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

char base64_tablel[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','\0'};

unsigned int get_random_byte();
void put_binary(int);
void base64();
void write_to_binary_file(u_char *content, int len, char *name);

int main(int argc, char const *argv[]){
	if(!(argc>1)){
		perror("[E] Too few arguments");
		exit(EXIT_FAILURE);
	}
	unsigned int len=strlen(argv[1]);
	u_char ciphertext[100], key[100];
	for (int i=0;i<len; i++){
		key[i] = (char)get_random_byte();
		ciphertext[i] = argv[1][i] ^ key[i];
	}
	write_to_binary_file(key, len, "key.bin");
	write_to_binary_file(ciphertext, len, "ciphertext.bin");
	return 0;
}
unsigned int get_random_byte(){	
	unsigned int randval;
	FILE *f;
	f = fopen("/dev/random", "r");
	fread(&randval, sizeof(randval), 1, f);
	fclose(f);
	return randval;
}
void write_to_binary_file(u_char *content, int len, char *name){
	size_t element_size = sizeof(char)*len;
	size_t elements_to_write = sizeof content;
	printf("Content: %d\n", strlen(content));
	for(int j=0;j<len;j++)
		printf("%u ", content[j]);
	puts("");
	FILE *fp = fopen(name, "wb");
	size_t elements_written = fwrite(content, element_size, elements_to_write, fp);
	if (elements_written != elements_to_write){
		perror("[E] Couldn't write to file");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
}
void put_binary(int n){
	for(int m=0;m<8;m++){
		if(!!((n << m) & 0x80))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}
void base64(){
	char string[150]=" ", ss[20];
	int last_space = 0, transformed[50], counter=0;
	strcat(string, " ");
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
	printf("Tranformed: %s", transformed);
}