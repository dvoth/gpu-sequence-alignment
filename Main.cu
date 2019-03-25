#include "input.cpp"

// const int maxKSize = 105;
int main(int argc, char * argv[]){
	//will need to create some input file method that will take the input from the user (KSize & fileName)
	dataList *lmerHead = new dataList();
	dataList *kmerHead = new dataList();
	read_fasta(21, "test.fasta", kmerHead, lmerHead);

	return 0;
}