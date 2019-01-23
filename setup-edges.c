__global__ void
 setupEdges(
     KEY_PTR lmerKeys ,
     VALUE_PTR lmerValues ,
     unsigned int * lmerOffsets ,
     const unsigned int lmerCount ,
     KEY_PTR TK ,
     VALUE_PTR TV ,
     unsigned int * bucketSize ,
     const unsigned int bucketCount ,
     unsigned int * l ,
     unsigned int * e ,
     EulerEdge * ee ,
     unsigned int * loffsets ,
     unsigned int * eoffsets ,
     const KEY_T validBitMask)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     if (tid < lmerCount)
     {
         KEY_T lmer = lmerKeys[tid];
         VALUE_T lmerValue = lmerValues[tid];
         KEY_T prefix = (lmer & (validBitMask << 2)) >> 2;
         KEY_T suffix = (lmer & validBitMask);
         KEY_T lomask = 3;

         VALUE_T prefixIndex =
             getHashValue(
                 prefix,
                 TK,
                 TV,
                 bucketSize,
                 bucketCount);

         VALUE_T suffixIndex =
             getHashValue(
                 suffix,
                 TK,
                 TV,
                 bucketSize,
                 bucketCount);

         KEY_T transitionTo = (lmer & lomask);
         KEY_T transitionFrom = ((lmer >> __popcll(validBitMask)) & lomask);

         unsigned int loffset = loffsets[(prefixIndex << 2) + transitionTo];
         unsigned int eoffset = eoffsets[(suffixIndex << 2) + transitionFrom];

         unsigned int lmerOffset = lmerOffsets[tid];

         for (unsigned int i = 0; i < lmerValue; i++)
         {
             ee[lmerOffset].eid = lmerOffset;
             ee[lmerOffset].v1 = prefixIndex;
             ee[lmerOffset].v2 = suffixIndex;
             ee[lmerOffset].s = lmerValues[lmerCount - 1]
             + lmerOffsets[lmerCount - 1];

             l[loffset] = lmerOffset;
             e[eoffset] = lmerOffset;
             loffset++;
             eoffset++;
             lmerOffset++;
         }
     }
 }
