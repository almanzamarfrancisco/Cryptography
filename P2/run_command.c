#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[]){
	FILE *fp;
	char *command = "echo HOLA | base64";
	char str[10];
	fp = popen(command,"r"); 
	fscanf(fp, "%s", str);
	printf("This is the result: %s\n", str);
	fclose(fp);
}