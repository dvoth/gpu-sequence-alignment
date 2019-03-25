#ifndef __ENCODEDDATA_CUH__
#define __ENCODEDDATA_CUH__

typedef struct  encodedData
{
	
	long long unsigned bs1 = 0;
	long long unsigned bs2 = 0;
	long long unsigned bs3 = 0;
	long long unsigned bs4 = 0;
	long long unsigned bs5 = 0;

	//get the next long long FOR ENCODING
	__host__ __device__ void getNextEmptyLong(long long unsigned **result) {
		if (bs1 == 0)
			(*result) = (&(this->bs1));
		else if (bs2 == 0)
			(*result) = (&(this->bs2));
		else if (bs3 == 0)
			(*result) = (&(this->bs3));
		else if (bs4 == 0)
			(*result) = (&(this->bs4));
		else
			(*result) = (&(this->bs5));
	}

	//based on the given long this will return the next one for decoding
	__host__ __device__ void getNextEncodedLong(long long unsigned **temp) {
		if ((*(*temp)) == bs1)
			(*temp) = (&bs2);
		else if ((*(*temp)) == bs2)
			(*temp) = (&bs3);
		else if ((*(*temp)) == bs3)
			(*temp) = (&bs4);
		else if ((*(*temp)) == bs4)
			(*temp) = (&bs5);
	}
		//simple check to see if list is empty 1 = yes and 0 = no
		__host__ __device__ void isEmpty(int *result) {
			if (bs1 == 0 && bs2 == 0 && bs3 == 0 && bs4 == 0 && bs5 == 0)
				(*result) = 1;
			else
				(*result) = 0;
		}
		//key creater from the encodedData object for the hash table
		__host__ __device__ void createKey(long long unsigned *result) {
			(*result) = bs1;
			(*result) += bs2;
			(*result) += bs3;
			(*result) += bs4;
			(*result) += bs5;
		}

} encodedData;

#endif
