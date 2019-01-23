__global__ void
debruijnCount(
    KEY_PTR lmerKeys , /* lmer keys */
    VALUE_PTR lmerValues , /* lmer frequency */
    5unsigned int lmerCount , /* total lmers */
    KEY_PTR TK , /* Keys’ pointer for Hash table*/
    VALUE_PTR TV , /* Value pointer for Hash table*/
    unsigned int * bucketSize , /* bucketSize: size of each bucket */
    unsigned int bucketCount , /* total buckets */
    unsigned int * lcount , /* leaving edge count array : OUT */
    unsigned int * ecount , /* entering edge count array: OUT */
    KEY_T validBitMask /* bit mask for K length encoded bits*/
)
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
        KEY_T lomask = 3; // 2 bit Mask

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

        lcount[(prefixIndex << 2) + transitionTo] = lmerValue;
        ecount[(suffixIndex << 2) + transitionFrom] = lmerValue;
    }
}
