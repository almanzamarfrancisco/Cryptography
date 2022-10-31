/*
* @ date: 30/10/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / OTP decipher 
* [I] compile: gcc decipher_OTP.c -o decipher_OTP
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

int main(){
	u_char *key, *cipher_text, *plain_text;
	puts("**OTP decipher**");
	plain_text = malloc(sizeof(u_char)*300);
	key = read_from_file("./key.bin");
	cipher_text = read_from_file("./ciphertext.bin");
	puts("Base 64: ");
	for(int i = 0;cipher_text[i]; i++){
		plain_text[i] = cipher_text[i] ^ key[i];
		printf("%c", plain_text[i]);
	}
	puts("");
	plain_text = decipher_base64(plain_text);
	printf("Plain text: %s\n", plain_text);
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
    // printf("Read data: %2d\n", file_contents);
	return file_contents;
}
u_char *decipher_base64(u_char *str){
	FILE *fp;
	u_char *result = (char*)malloc(sizeof(char)*strlen(str));
	char *command = (char*)malloc(sizeof(char)*(strlen(str)+20));
	strcat(command, "echo '");
	strcat(command, str);
	strcat(command, "' | base64 -d");
	fp = popen(command,"r"); 
	fscanf(fp, "%s", result);
	fclose(fp);
	return result;
}