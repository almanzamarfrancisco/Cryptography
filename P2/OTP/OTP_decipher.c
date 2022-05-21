/*
* @ date: 17/05/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / OTP decipher 
* [I] compile: gcc OTP_decipher.c -o OTP_decipher
* [I] usage: ./OTP_decipher.c
* i.e. ./OTP_decipher.c 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <fcntl.h>

u_char *read_from_file(char *name);
u_char *decipher_base64(u_char *input);

char base64_table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','\0'};

int main(){
	u_char *key, *cipher_text, *plain_text;
	plain_text = malloc(sizeof(u_char)*300);
	key = read_from_file("./key.bin");
	cipher_text = read_from_file("./ciphertext.bin");
	for(int i = 0; i<20; i++){
		plain_text[i] = cipher_text[i] ^ key[i];
		// printf("%c", plain_text[i]);
	}
	decipher_base64(plain_text);
	puts("");
	return 0;
}
u_char *read_from_file(char *name){
	FILE *fp;
	struct stat sb;
	fp = fopen(name,"rb");
    if (stat(name, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    char* file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, fp);
    // printf("read data: %s\n", file_contents);
	return file_contents;
}
u_char *decipher_base64(u_char *input){
	u_char string[150]=" ", ss[20], value=0;
	static u_char transformed[100];
	strcat(string, input);
	for(int j=0;string[j];j++){
		if(string[j] == ' ')
			printf(" ");
		printf("%c", base64_table[string[j]]);
	}
	puts("");
}