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
    
    //iterate through the read and encode it into the 64-bit representation
    for(int i=0; i < sizeof(read); i++){
        //encode the value

        //put value in new array

        //pass to the hash table function for storage 
    }




}