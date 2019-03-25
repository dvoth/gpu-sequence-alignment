#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <bitset>

#include "encodedData.cuh"
#include "Decode.cu"
#include "mer_list.cuh"

const int maxKSize = 105;

__host__ __device__ void baseToLong(char *val, int KSize, struct encodedData * result){
   /*
		A = 000;
		C = 001;
		G = 010;
		T = 011;
		N = 100;
	*/
	long long unsigned oneflip = 1;
	//the struct holds 320 bits all together over 5 different longs
	//while only a single long long can hold 64 bits and the encoding comes out to 3 bits per base to encode all 5
	//thus it only holds 21 bases per long long when rounded down (21.3333_ when not rounded)
	//this means the max k can be 160 
	//this will guarntee that K <= 105 which
	if (KSize > 105)
		return;

	long long unsigned *encodingTemp = NULL;
	result->getNextEmptyLong(&encodingTemp);

	for (int i = 0; i < KSize; i++) {
		//if true, them change to the other version of the struct
		if (i % 21 == 0 && i > 0)
			result->getNextEmptyLong(&encodingTemp);

		int aciiVal = int(val[i]);
		//A val - 000
		if (aciiVal == 65 || aciiVal == 97) {
			//shift left 3 times
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
		}
		//C val - 100
		else if (aciiVal == 67 || aciiVal == 99) {
			//shift left 3 times
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
			//flip last bit
			(*encodingTemp) = (*encodingTemp) | oneflip;

		}
		//G val - 010
		else if (aciiVal == 71 || aciiVal == 103) {
			//shift left once
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
			//flip first 1
			(*encodingTemp) = (*encodingTemp) | oneflip;
			//shit left again twice
			//(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
		}
		//T val - 110
		else if (aciiVal == 84 || aciiVal == 116) {
			//shift left twice
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
			//flip first 1
			(*encodingTemp) = (*encodingTemp) | oneflip;
			//shift left once
			(*encodingTemp) = (*encodingTemp) << 1;
			//flip first 1
			(*encodingTemp) = (*encodingTemp) | oneflip;
		}
		//default N value - 001
		else {
			//shift once
			(*encodingTemp) = (*encodingTemp) << 1;
			//flip the bit 
			(*encodingTemp) = (*encodingTemp) | oneflip;
			//shift twice
			(*encodingTemp) = (*encodingTemp) << 1;
			(*encodingTemp) = (*encodingTemp) << 1;
		}
	}


}

__host__ __device__ void encodeData(char *val, int KSize, dataList *kmerHead, dataList *lmerHead){ 


	/*
		A = 000;
		C = 001;
		G = 010;
		T = 011;
		N = 100;
	
	*/
	//L = our K-mers which are of size K
	//K = our K - 1 mers which are of size K-1	
	struct encodedData *lMer = new encodedData();
	int LSize = KSize;              		//reduce the size sine L = K - 1
	baseToLong(val, LSize, lMer);       //transform the bases into the long long representation
	(*lmerHead).addNewVal(lMer);

	////kmer----------------------------------------------------------------------------
	struct encodedData *kMer = new encodedData();        //create the var that will be the K-Mer
	int KSize1 = LSize - 1;
	baseToLong(val, KSize1, kMer);       //transform the bases into the long long representation
	(*kmerHead).addNewVal(kMer);


	//next step is to put the encoded K-mer into the hash table
	


}




