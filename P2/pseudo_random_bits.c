/*
* @ date: 08/10/2022
* @ author: Almanza Martínez Francisco Alejadro
* @ subject: Criptography
* @ teacher: Sandra Diaz Santiago
* @ Description: Practice 2 / pseudorandom bits 
* @ Source: James Aspnes from 2003 to 2012. [Online] https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html
* @ Important: This program is just for Linux, it uses /dev/random that derive their random bits from physically random properties of the computer
* [I] compile: gcc pseudo_random_bits.c -o pseudo_random_bits
* [I] usage: ./pseudo_random_bits
*/
#include <stdio.h>
int main(int argc, char **argv){
    unsigned int randval;
    FILE *f;
    f = fopen("/dev/random", "r");
    fread(&randval, sizeof(randval), 1, f);
    fclose(f);
    printf("=> This program use /dev/random device files from linux which derive their random bits from physically random properties of the computer\n");
    printf("=> Random unsigned int value: %u\n", randval);
    return 0;
}