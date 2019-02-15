#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <bitset>

//takes a size K, and a char array
__host__ __device__ void decodeData(long long val, int KSize, char *result) {
	//k defines the number of bits revelant to the bit mask
	// k must be strictly less than 32 for now, since a long long is 64 bits 
	/*
		A = 00;
		C = 01;
		G = 10;
		T = 11;

	*/
	//assume the largest K which is 32 and creates an array for it
	//will have to chang when we can view larger K values
	//since this can't be dynamic, that is why it is 32
	for (int i = 0; i < KSize; i++) {
		long long unsigned one = 1;
		long long unsigned temp1 = one & val;
		val = val >> 1;
		long long unsigned temp2 = one & val;
		val = val >> 1;
		if (temp2 == 0 && temp1 == 0)
			result[KSize - i - 1] = 'A';
		else if (temp2 == 0 && temp1 == 1)
			result[KSize - i - 1] = 'C';
		else if (temp2 == 1 && temp1 == 0)
			result[KSize - i - 1] = 'G';
		else
			result[KSize - i - 1] = 'T';
	}
}