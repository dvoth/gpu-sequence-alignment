__global__ void
 bestMutation2(
     unsigned int * mutationScore ,
     unsigned int readLength ,
     unsigned int l ,
     /*out*/
     unsigned int * mutationStep)
 {
     unsigned int bestIdx = 0;
     unsigned int bestScore = mutationScore[
         blockIdx.x * readLength * NA_COUNT + threadIdx.x * NA_COUNT
     ];
     unsigned int newScore = 0;
     for (int i = 1; i < NA_COUNT; i++)
     {
         newScore =
             mutationScore[ blockIdx.x * readLength * NA_COUNT
                + threadIdx.x * NA_COUNT + i];
         bestIdx = bestScore < newScore ? i : bestIdx;
         bestScore = bestScore < newScore ? newScore : bestScore;
     }
     mutationStep[ blockIdx.x * readLength
         + threadIdx.x] = (bestIdx << 16 | bestScore);
 }
