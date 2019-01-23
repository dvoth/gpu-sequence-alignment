__global__ void
 bestFinalMutation(
	 unsigned int * mutationStep ,
	 unsigned int readLength ,
	 unsigned int l ,
	 /*out*/
	 unsigned int * bestMutationPos ,
	 unsigned int * bestMutationIdx)
 {
	 unsigned int newScoreValue = mutationStep[blockIdx.x * readLength];
	 unsigned int bestScore = (newScoreValue & 0x0000FFFF);
	 unsigned int bestIdx = newScoreValue >> 16;
	 unsigned int bestPos = 0;
	 unsigned int newScore;
	 for (int i = 1; i < readLength; i++)
	 {
		 newScoreValue = mutationStep[blockIdx.x * readLength + i];
		 newScore = (newScoreValue & 0x0000FFFF);
		 bestIdx = bestScore < newScore ? (newScoreValue >> 16) : bestIdx;
		 bestPos = bestScore < newScore ? i : bestPos;
		 bestScore = bestScore < newScore ? newScore : bestScore;
	 }
	 bestMutationPos[blockIdx.x] =
		 (bestScore > (
			 (readLength - l + 1)
			 + (readLength - l + 1) >> 1))
		 ? bestPos : readLength;
		 bestMutationIdx[blockIdx.x] = bestIdx;
 }
