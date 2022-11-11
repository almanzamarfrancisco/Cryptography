/*
* @ date: 04/11/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Implementing simple Triple DES schedule
* [I] compile: gcc key_schedule.c -o key_schedule
* [I] usage: ./key_schedule
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

void make_permutation(u_char *b, int size, int p[], int permutation_size);
void put_binary(int b);
void put_binary_bytes(u_char *n, int size);

int main(int argc, char const *argv[]){
	printf("**3DES Key Schelue**\n");
	printf("[I] Generating key...\n");
	int c_permutation[] = { 57, 49, 41, 33, 25, 17, 9,
						 1, 58, 50, 42, 34, 26, 18,
						 10, 2, 59, 51, 43, 35, 27,
						 19, 11, 3, 60, 52, 44, 36
						};
	int d_permutation[] = {63, 55, 47, 39, 31, 23, 15,
						 7, 62, 54, 46, 38, 30, 22,
						 14, 6, 61, 53, 45, 37, 29, 
						 21, 13, 13, 28, 20, 12, 4
						};
	int c_permutation_size = sizeof(c_permutation)/sizeof(int);
	int d_permutation_size = sizeof(d_permutation)/sizeof(int);
	u_char *key = (u_char*)malloc(sizeof(u_char)*17);
	strcpy(key, "kj329nf982bc9wn1");
	printf("This is the result: %s \n", key);
	make_permutation(key, 16, c_permutation, c_permutation_size);
	return 0;
}
void make_permutation(u_char *b, int size, int p[], int permutation_size){
	int i=0, j=0, mask=0, bitshifted[permutation_size], reqbit[size], l=0, result[size];
	int bits_to_shift;
	printf("[I] Permuting...\n");
	printf("[I] Original value: \n");
	for (int i=0;i<size;i++){
		result[i] = 0; // Initialize result array
		reqbit[i] = 0; // Initialize reqbit array
		printf("%8d ", i);
	}
	puts("");
	for (int i=0;i<size;i++){
		printf("%8d ", p[i]);
	}
	puts("");
	for (int i=0;i<size;i++){
		printf("%8d ", p[i]/8);
	}
	puts("");
	for (int i=0;i<size;i++){
		bits_to_shift = 8 - (p[i] - (p[i]/8)*8);
		printf("%8d ", bits_to_shift);
	}
	printf("\n");
	put_binary_bytes(b, size);
	printf("\n");
	for(i=0;i<size;i++){
		bits_to_shift = 8 - (p[i] - (p[i]/8)*8);
		mask = 1;
		mask = mask<<bits_to_shift;//
		reqbit[i] = (int)b[p[i]/8] & mask;//
		put_binary(reqbit[i]);//
		printf(" ");
	}
	printf("\n");
	// for(i=0;i<8;i++){
	// 	j=1;
	// 	j<<7-i;
	// 	reqbit[i] = reqbit[i]<<(7-i);
	// 	result[0] = b[0] | reqbit[i];
	// 	printf(" ");
	// }
	// puts("\nResult: ");	
	// put_binary_bytes((char*)result, size);
	// puts("");	
	// // printf("=> \n");
	// for(int i=0;i<size;i++){
	// 	for(int m=0;m<8;m++){
	// 		if(!!((result[i] << m) & 0x80))
	// 			putchar('1');
	// 		else
	// 			putchar('0');
	// 	}
	// 	printf(" ");
	// }
	// puts("");	
	// printf("\n[I] Permuted finished \n");
	// put_binary(result);
	// puts("");
	// *b = result;
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
void put_binary_bytes(u_char *n, int size){
	for (int i=0;i<size;i++){
		put_binary(n[i]);
		printf(" ");
	}
}