__global__ void
 calculateMutationScores(
     char * in_read ,
     char * mutationMask ,
     unsigned int readLength ,
     unsigned int lmerLength ,
     unsigned int M ,
     KEY_PTR TK ,
     VALUE_PTR TV ,
     unsigned int * bucketSize ,
     unsigned int bucketCount ,

     unsigned int* mutation , /*out param*/
     unsigned int * buffer) /*out param*/
 {
     extern __shared__ char read[]; /* shared variable for read data*/
     char * mask = read + readLength + 31; /* shared variable for mask */

     VALUE_T statusF;
     VALUE_T statusR;
     volatile KEY_T lmer = 0;

     /*convert to base4*/
     read[threadIdx.x] = base4[
         in_read[blockIdx.x * readLength + threadIdx.x]
         & 0x07
     ];
     /*apply mutation mask*/
     mask[threadIdx.x] = mutationMask[
         (threadIdx.x + readLength - blockIdx.y)
         % readLength
     ];

     __syncthreads();

     for (unsigned int k = 0; k < 4; k++)
     {
         lmer = 0;
         #pragma unroll 4 //loop unroll
         for (unsigned int i = 0; i < 8; i++)
         {
             lmer = (lmer << 8) |
             ((KEY_T)(
                 shifter[mutator[mask[threadIdx.x + i * 4]
                 | read[threadIdx.x + i * 4]][k]][3]
                 | shifter[mutator[mask[threadIdx.x + i * 4 + 1]
                 | read[threadIdx.x + i * 4 + 1]][k]][2]
                 | shifter[mutator[mask[threadIdx.x + i * 4 + 2]
                 | read[threadIdx.x + i * 4 + 2]][k]][1]
                 | mutator[mask[threadIdx.x + i * 4 + 3]
                 | read[threadIdx.x + i * 4 + 3]][k]));
         }

         lmer = (lmer >> ((32 - lmerLength) << 1)) & lmerMask[lmerLength - 1];
         statusF =
             getHashValue(
                 lmer,
                 TK,
                 TV,
                 bucketSize,
             bucketCount);
         statusF = ((statusF == MAX_INT) ? 0 : ((statusF >= M)) ? 1 : 0);

         /*compute reverse*/
         lmer = 0;
         #pragma unroll 4 //loop unroll
         for (int i = 7; i >= 0; i--)
         {
             lmer = (lmer << 8) |
             ((KEY_T)
                 shifter[reverse[mutator[mask[threadIdx.x + i * 4 + 3]
                 | read[threadIdx.x + i * 4 + 3]][k]]][3]
                 | shifter[reverse[mutator[mask[threadIdx.x + i * 4 + 2]
                 | read[threadIdx.x + i * 4 + 2]][k]]][2]
                 | shifter[reverse[mutator[mask[threadIdx.x + i * 4 + 1]
                 | read[threadIdx.x + i * 4 + 1]][k]]][1]
                 | reverse[mutator[mask[threadIdx.x + i * 4]
                 | read[threadIdx.x + i * 4]][k]]);
         }

         lmer = (lmer) & lmerMask[lmerLength - 1];

         statusR =
             getHashValue(
                 lmer,
                 TK,
                 TV,
                 bucketSize,
                 bucketCount);
         statusR = ((statusR == MAX_INT) ? 0 : ((statusR >= M)) ? 1 : 0);

         //increment solidCount
         mutation[blockIdx.x * (readLength * NA_COUNT * readLength)
             + blockIdx.y * readLength * NA_COUNT
             + k * readLength
             + threadIdx.x]
             = (unsigned int) (statusF + statusR);
     }
 }
