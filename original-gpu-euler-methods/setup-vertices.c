__global__ void
setupVertices(
    KEY_PTR kmerKeys ,
    unsigned int kmerCount ,
    KEY_PTR TK ,
    VALUE_PTR TV ,
    unsigned int * bucketSeed ,
    unsigned int bucketCount ,
    EulerVertex * ev ,
    unsigned int * lcount ,
    unsigned int * loffset ,
    unsigned int * ecount ,
    unsigned int * eoffset)
{

    unsigned int tid =
        (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
        + (blockDim.x * blockDim.y * blockIdx.x)
        + (blockDim.x * threadIdx.y)
        + threadIdx.x;

    if (tid < kmerCount)
    {

        KEY_T key = kmerKeys[tid];

        VALUE_T index =
        getHashValue(
            key,
            TK,
            TV,
            bucketSeed,
            bucketCount);

         ev[index].vid = key;

         //set up leaving edge information
         ev[index].lp = loffset[(index << 2)];
         ev[index].lcount =
             lcount[(index << 2)]
             + lcount[(index << 2) + 1]
             + lcount[(index << 2) + 2]
             + lcount[(index << 2) + 3];

         //set up entering edge information
         ev[index].ep = eoffset[(index << 2)];
         ev[index].ecount =
             ecount[(index << 2)]
             + ecount[(index << 2) + 1]
             + ecount[(index << 2) + 2]
             + ecount[(index << 2) + 3];
     }
}
