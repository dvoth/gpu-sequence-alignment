#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

void read_fasta(int k, string file_name){
    ifstream in_file(file_name);
    int index_start = 0;
    int index_length = k;
    bool line_finished = false;
    
    // cout << "Default value of k is 27. If a different one is desired, please enter: ";
    // cin >> k;
    
    for(string line_in; getline(in_file, line_in); ){
        // Check to make sure we are not on a header line, as we ignore those.
        if(line_in.substr(0, 1) != ">"){
            while(!line_finished){
                // This checks to see that the end of the k-mer is still a char (one of the bases).
                // If it is not, we cannot continue to read k-mers, as we have reached the end of all possibilities.
                if(line_in[k + index_start - 1] != NULL && isalpha(line_in.at(k + index_start - 1))){
                    char k_mer_found[k];
                    string line_in_substr = line_in.substr(index_start, k);
                    strcpy(k_mer_found, line_in_substr.c_str());
                    // k_mer_found = line_in.substr(index_start, k);
                    index_start++;
                    
                    // Pass the k-mer to the encoder for work.
                    cout << k_mer_found << " - " << line_in_substr.length() << endl;
                }
                else{
                    line_finished = true;
                }
            }
        }
        cout << endl;
        index_start = 0;
        line_finished = false;
    }
}
