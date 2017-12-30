/*
SHA_256.c

Author:  		Adarsh Melethil
Created:		30, December 2017
Last-Modified:	30, December 2017

*/

#include "SHA_256.h"
#include <stdio.h>

#define WORD int
#define WORD_SIZE sizeof(WORD)

int rotateLeft(WORD word, int rotate_amount){
  return ((word << rotate_amount) | (word >> (WORD_SIZE - rotate_amount));
}
int rotateRight(WORD word, int rotate_amount){
  return ((word >> rotate_amount) | (word << (WORD_SIZE - rotate_amount));
}

int main(void) {
  printf("%lu\n", sizeof(long long));
  return 0;
}