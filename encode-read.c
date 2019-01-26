/*
    Base encoding of the reads from the FASTA file input
*/

#include <stdio.h>

/*
    * k-value is the length k either from the input of the user or a default value k<=32
    * read is a read from the FASTA file to be encoded, can be any size, must be a single dimension array
*/
__global__ void encodeRead(int k-value, char **read){

    /*
        Base Encoding according to Mahmood's Thesis
        A = 00
        C = 01
        G = 10
        T = 11
        If there are less than 32 bases in a read, the missing bases will be encoded to 00
        ----------------------------------------------
        New Encoding addidtion
        N = 00
    */
    
    //iterate through the read till a length of k is found or till the end of the read
    int i;
    for(i=1; i <= (int)(sizeof(read)); i++){
        
        //if the current iterator is the length of k
        if(i % k == 0){

        }
        else{

        }

    }
    
    //if the k-mer isn't a total length of K and the read is incompletes
    if (i < 0 && i == (int)(sizeof(read)) && i % k != 0){

    }




}