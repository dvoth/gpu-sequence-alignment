#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <bitset>
__host__ __device__ void baseToLong(char *val, int KSize, long long unsigned *result){
    /*
        A = 00;
        C = 01;
        G = 10;
        T = 11;
    */
    long long unsigned oneflip = 1;
    // long long unsigned result = 0;

    for (int i = 0; i < KSize; i++) {
        int aciiVal = int(val[i]);
        //A val
        if (aciiVal == 65 || aciiVal == 97) {
            //shift left twice
            (*result) = (*result) << 1;
            (*result) = (*result) << 1;
        }
        //C val
        else if (aciiVal == 67 || aciiVal == 99) {
            //shift left twice
            (*result) = (*result) << 1;
            (*result) = (*result) << 1;
            //flip last bit
            (*result) = (*result) | oneflip;

        }
        //G val
        else if (aciiVal == 71 || aciiVal == 103) {
            //shift left once
            (*result) = (*result) << 1;
            //flip first 1
            (*result) = (*result) | 1;
            //shit left again
            (*result) = (*result) << 1;
        }
        //T val
        else if (aciiVal == 84 || aciiVal == 116) {
            //shift left once
            (*result) = (*result) << 1;
            //flip first 1
            (*result) = (*result) | 1;
            //shift left once
            (*result) = (*result) << 1;
            //flip first 1
            (*result) = (*result) | 1;
        }
        //default bad val
        else{
            printf("Bad Input Flag Triggered \n");
            break;
        }
    }


}

__host__ __device__ void encodData(char *val, int KSize){ 
    long long unsigned kMer = 0;        //create the var that will be the K-Mer
	baseToLong(val, KSize, (&kMer));       //transform the bases into the long long representation

    long long unsigned lMer = 0;         //create the var that will be the L-Mer
    int LSize = KSize - 1;              //reduce the size sine L = K - 1
    baseToLong(val, LSize, (&lMer));       //transform the bases into the long long representation
    
    //next step is to put the encoded K-mer into the hash table
}