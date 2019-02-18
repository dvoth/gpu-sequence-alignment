#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

void read_fasta(int k, std::string file_name){
    std::ifstream in_file(file_name);
    int index_start = 0;
    int index_length = k;
    bool line_finished = false;
    
    // cout << "Default value of k is 27. If a different one is desired, please enter: ";
    // cin >> k;
    
    for(std::string line_in; std::getline(in_file, line_in); ){
        // Check to make sure we are not on a header line, as we ignore those.
        if(line_in.substr(0, 1) != ">"){
            while(!line_finished){
                // This checks to see that the end of the k-mer is still a char (one of the bases).
                // If it is not, we cannot continue to read k-mers, as we have reached the end of all possibilities.
                if(line_in[k + index_start - 1] != '\0' && isalpha(line_in.at(k + index_start - 1))){
                    char k_mer_found[k];
                    std::string line_in_substr = line_in.substr(index_start, k);
                    strcpy(k_mer_found, line_in_substr.c_str());
                    // k_mer_found = line_in.substr(index_start, k);
                    index_start++;
                    
                    // Pass the k-mer to the encoder for work.
                    std::cout << k_mer_found << " - " << line_in_substr.length() << std::endl;
                }
                else{
                    line_finished = true;
                }
            }
        }
        std::cout << std::endl;
        index_start = 0;
        line_finished = false;
    }
}
