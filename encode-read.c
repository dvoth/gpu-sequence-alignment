/*
    Base encoding of the reads from the FASTA file input
*/

#include <stdio.h>

/*
    * k-value is the length k either from the input of the user or a default value k<=32
    * read is a read from the FASTA file to be encoded, can be any size, must be a single dimension array
*/
__global__ void encodeRead(char **read){

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
    //use get method to get the 'K' value from the input method
    int k = 0;
    //int k = getSizeOfKFromUserInputReader();

    //make sure that K is smaller than the size of the read
    if(k <= sizeof(read))
    {
        int begin = 0;      //iterator
        int end = k;        //iterator
        //Iterating through the read until the end of the file
        while(end <= sizeof(read)){
            long 64bitkmer = 0;
            //will loop through the substring of the read, converting each base to the 2-bit representation
            for(int i=begin; i < end; i++){
                char value = read[i];
                //switch statement to increase the long, the default where there is a N, wil be 00
                switch(value){
                    case 'A':
                        64bitkmer = 64bitkmer * 100;
                        break;
                    case 'C':
                        64bitkmer = 64bitkmer * 100;
                        64bitkmer += 1;
                        break;
                    case 'G':
                        64bitkmer = 64bitkmer * 100;
                        64bitkmer += 10;
                        break;
                    case 'T':
                        64bitkmer = 64bitkmer * 100;
                        64bitkmer += 11;
                        break;
                    default:
                        64bitkmer = 64bitkmer * 100;
                        break;
                }
            }

            begin += k;
            end += k;
        }
    }
    else{
        //thow an error that says that the k value is/was smaller than the read length
    }







}