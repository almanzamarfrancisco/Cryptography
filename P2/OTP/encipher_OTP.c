/*
* @ date: 30/10/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / OTP encipher 
* [I] compile: gcc encipher_OTP.c -o encipher_OTP
* [I] usage: ./OTP_encipher.c {plaintext}
* i.e. ./OTP_encipher.c "Hello  my name is Lucas"
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

unsigned int get_random_byte();
void put_binary(int);
u_char *encipher_base64(u_char*);
void write_to_binary_file(u_char *content, int len, char *name);

int main(int argc, char *argv[]){
	if(!(argc>1)){
		perror("[E] Too few arguments");
		exit(EXIT_FAILURE);
	}
	puts("**OTP encipher**");
	unsigned int len = strlen(argv[1]), b64text_len=0;
	u_char *b64text, *ciphertext, *key;
	ciphertext = malloc(sizeof(u_char)*((len*1.4)+10));
	key = malloc(sizeof(u_char)*((len*1.4)+10));
	b64text = malloc(sizeof(u_char)*((len*1.4)+10));
	printf("[I] The string: %s\n", argv[1]);
	b64text = encipher_base64(argv[1]);
	b64text_len = strlen(b64text);
	for (int i=0;i<b64text_len; i++){
		key[i] = (char)get_random_byte();
		ciphertext[i] = b64text[i] ^ key[i];
	}
	write_to_binary_file(key, b64text_len, "key.bin");
	write_to_binary_file(ciphertext, b64text_len, "ciphertext.bin");
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
	// printf("Content length: %d, size: %d\n", strlen(content), element_size);
	// for(int j=0;j<len;j++)
	// 	printf("%u ", content[j]);
	puts("");
	FILE *fp = fopen(name, "wb");
	size_t elements_written = fwrite(content, element_size, elements_to_write, fp);
	if (elements_written != elements_to_write){
		perror("[E] Couldn't write to file\n");
		exit(EXIT_FAILURE);
	}
	printf("[I] File %s written successfully!\n", name);
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
u_char *encipher_base64(u_char *str){
	FILE *fp;
	u_char *result = (char*)malloc(sizeof(char)*strlen(str));
	char *command = (char*)malloc(sizeof(char)*(strlen(str)+20));
	strcat(command, "echo '");
	strcat(command, str);
	strcat(command, "' | base64");
	fp = popen(command,"r"); 
	fscanf(fp, "%s", result);
	fclose(fp);
	return result;
}