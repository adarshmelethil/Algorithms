/*
SHA_256.c

Author:  		Adarsh Melethil
Created:		30, December 2017
Last-Modified:	30, December 2017

*/

#include "SHA_256.h"
#include <stdio.h>
#include <stdlib.h>

#define WORD int
#define WORD_SIZE sizeof(WORD)
// Rotate left
#define ROTL(word, rotate_amount) ((word << rotate_amount) | (word >> (WORD_SIZE - rotate_amount)))
// Rotate right
#define ROTR(word, rotate_amount) ((word >> rotate_amount) | (word << (WORD_SIZE - rotate_amount)))

#define Ch(x,y,z) ((x&y)^((~x)&z))
#define Maj(x,y,z) ((x&y)^(x&z)^(y&z))

#define UPPER_SIGMA_0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x,22))
#define UPPER_SIGMA_1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x,25))
#define LOWER_SIGMA_0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))
#define LOWER_SIGMA_1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

const int K[] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

int padAndBlockMessage(unsigned char*** msg_blocks, unsigned char* message, unsigned long msg_size){
  // msg_size + 1bit termination, 1 byte to makes sure there is room + 64bit length of msg
  int N = ((msg_size+1+8) + 63) / 64;

  (*msg_blocks) = (unsigned char**)malloc(N * sizeof(unsigned char*));
  for(int i = 0; i < N; i++){
    (*msg_blocks)[i]  = (unsigned char*)malloc(64);
    
    for(unsigned long j = 0; j < 64; j++){
      // printf("%d\n", padded_message[i]);
      if(((i*64)+j) < msg_size){
        (*msg_blocks)[i][j] = message[(i*64)+j];
        // printf("%c\n", message[(i*64)+j]);
      }else{
        (*msg_blocks)[i][j] = 0;
      }
    }
  }
  
  (*msg_blocks)[N-1][(msg_size%64)] = 0x80;

  for(int i = 56; i < 64; i++){
    (*msg_blocks)[N-1][i] = (msg_size << (8*(63-i)));
  }

  return N;
}

void printDigest(unsigned char* digest){
  for(int i = 0; i < 64; i++){
    printf("%#02x \t", digest[i]);
    if((i+1)%8 ==0){
      printf("\n");
    }
  }
}
void printSchedule(unsigned int* digest){
  for(int i = 0; i < 64; i++){
    printf("%#08x \t", digest[i]);
    if((i+1)%8 ==0){
      printf("\n");
    }
  }
}

void printMessageBlocks(unsigned char** msg_blocks, int num_of_blocks){
  for(int i = 0; i < num_of_blocks; i++){
    printf("Block:%d\n", i);
    printDigest(msg_blocks[i]);
  }
}

unsigned int* messageSchedule(unsigned char* msg_blocks){
  unsigned int* msg_schedule = (int *)malloc(64*sizeof(unsigned int));
  for(int i = 0; i <= 15; i++){
    int j = i * 4;
    msg_schedule[i] = msg_blocks[j] + (msg_blocks[j+1]<<8) + (msg_blocks[j+2]<<16) + (msg_blocks[j+3]<<24);
  }
  for(int i = 16; i <= 64; i++){
    msg_schedule[i] = LOWER_SIGMA_1(msg_schedule[i-2]) + 
                      msg_schedule[i-7] +
                      LOWER_SIGMA_0(msg_schedule[i-15]) +
                      msg_schedule[i-16]; 
  }
  return msg_schedule;
}

void hash(char msg[], unsigned long msg_size){
  unsigned char** msg_blocks;
  int n = padAndBlockMessage(&msg_blocks, msg, msg_size);

  int H[] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

  // printDigest(msg_blocks[0]);
  unsigned int* W = messageSchedule(msg_blocks[0]);
  printSchedule(W);
}

int main(void) {
  char test[] = "abc";
  // printf("'%d' \n", (test[1]=='\0') );

  // printf("%lu\n", sizeof(sizeof(unsigned char)));
  unsigned char** a;
  
  hash(test, sizeof(test));

  // printMessageBlocks(a, n);
  
  return 0;
}