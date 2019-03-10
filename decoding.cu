#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <bitset>
#include "encodedData.cuh"

//takes a size K, and a char array
__host__ __device__ void decodeData(struct encodedData *val, int KSize, char *result) {
//k defines the number of bits revelant to the bit mask
	// k must be strictly less than 32 for now, since a long long is 64 bits 
	/*
		A = 000;
		C = 001;
		G = 010;
		T = 011;
		N = 100;

	*/
	//assume the largest K which is 32 and creates an array for it
	//will have to chang when we can view larger K values
	//since this can't be dynamic, that is why it is 32
	long long unsigned * pointerTemp = (&(val->bs1));
	long long unsigned temp = (*pointerTemp);
	long long unsigned oneflip = 1;
	int twnetyOneShift = 21;
	int placementIterator = 0;
	for (int i = 0; i < KSize; i++) {
		//ignore the last bit since it doesn't contain anything
		//will get the next encoded long based on the current one
		if (i > 0 && i % 21 == 0) {
			val->getNextEncodedLong(&pointerTemp);					//CUDA doesn't allow for returns, this will get pointer
			temp = (*pointerTemp);									//this will copy over the value
			twnetyOneShift = twnetyOneShift * 2;					//increment the 21
			if (KSize < twnetyOneShift)
				twnetyOneShift = KSize;
			placementIterator = 0;
		}

		//getting all three of the bits for a single base
		long long unsigned bit1 = oneflip & temp;					//anding the 1 to the oringal the orginal encoded long long
		temp = temp >> 1;											//shift the temp one bit over the value we just obtained
		long long unsigned bit2 = oneflip & temp;
		temp = temp >> 1;
		long long unsigned bit3 = oneflip & temp;
		temp = temp >> 1;

		/*Since the last base will be at the beginning of the long long,
			we have to put the base red into the array it is correct position which is an offset of 21.
					since there are 21 bases stored in each long*/
		if (bit1 == 0 && bit2 == 0 && bit3 == 0)
			result[twnetyOneShift - placementIterator - 1] = 'A';
		else if (bit1 == 1 && bit2 == 0 && bit3 == 0)
			result[twnetyOneShift - placementIterator - 1] = 'C';
		else if (bit1 == 0 && bit2 == 1 && bit3 == 0)
			result[twnetyOneShift - placementIterator - 1] = 'G';
		else if (bit1 == 1 && bit2 == 1 && bit3 == 0)
			result[twnetyOneShift - placementIterator - 1] = 'T';
		else
			result[twnetyOneShift - placementIterator - 1] = 'N';

		placementIterator++;
	}
}