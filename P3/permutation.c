/*
* @ date: 04/11/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Permuting function
* [I] compile: gcc -o permutation permutation.c
* [I] usage: ./permutation
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void make_permutation(u_char *n, int p[], int size);
void put_binary(int b);

int main(int argc, char const *argv[]){
	u_char byte = 122;
	int permutation[] = {2,6,3,1,4,8,5,7};
	int permutation_size = sizeof(permutation)/sizeof(int);
	printf("**Permutation function**\n");
	printf("[I] Permutation lenght: %d\n[I] Permutation: ",  permutation_size);
	for (int i = 0; i < permutation_size; i++)
		printf("%2d", permutation[i]);
	puts("");
	printf("[I] Value in char: %2c \n[I] Value in int: %2d\n", byte, byte); 	
	make_permutation(&byte, permutation, permutation_size);
	printf("=> Permutation gotten: ");
	put_binary(byte);
	puts("");
	return 0;
}

void make_permutation(u_char *b, int p[], int size){
	int i=0, mask=0, bitshifted[8], reqbit=0, l=0, result=0;
	printf("[I] Permuting... \n");
	printf("[I] Original value: %d\n[I] Binary: ", *b);
	put_binary((int)*b);
	for (i=0;i<size;i++){
		mask = 1;
		mask = mask<<p[i];// To get 1 in the required position
		reqbit = (int)*b & mask;// To get the required bit
		// put_binary(reqbit);// Required bit gotten
		l = p[i] - i;// To get how many places is required to shift
		if(l < 0)// If negative shift to the 
			bitshifted[i] = reqbit<<abs(l);
		else
			bitshifted[i] = reqbit>>l;
		result = result | bitshifted[i];
		printf(" ");
	}
	puts("");
	printf("[I] Permuted finished \n");
	// put_binary(result);
	// puts("");
	*b = result;
}
void put_binary(int b){
	// printf("Value: %2d\n", v);
	for(int m=0;m<8;m++){
		if(!!((b << m) & 0x80))
			putchar('1');
		else
			putchar('0');
	}
}