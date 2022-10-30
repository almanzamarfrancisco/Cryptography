/*
* @ date: 30/10/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / pseudorandom bits 
* [I] compile: gcc pseudorandom_bits.c -o pseudorandom_bits
* [I] usage: ./pseudorandom_bits
*/
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void put_binary(int);
int randint(int);
void put_binary(int n);

int main(int argc, char const *argv[]){
	srand(time(NULL));   // Initialization, should only be called once.
	int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX
	int o = randint(r);
	printf("*Random number*\n");
	printf("Number: %d\n", o);
	printf("Binary: ");
	put_binary(o);
	return 0;
}

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n) {
	if ((n - 1) == RAND_MAX){
		return rand();
	} else {
		// Supporting larger values for n would requires an even more
		// elaborate implementation that combines multiple calls to rand()
		assert (n <= RAND_MAX);

		// Chop off all of the values that would cause skew...
		int end = RAND_MAX / n; // truncate skew
		assert (end > 0);
		end *= n;

		// ... and ignore results from rand() that fall above that limit.
		// (Worst case the loop condition should succeed 50% of the time,
		// so we can expect to bail out of this loop pretty quickly.)
		int r;
		while ((r = rand()) >= end);

		return r % n;
	}
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