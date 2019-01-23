__global__ void
 assignSuccessor(
     EulerVertex * ev ,
     unsigned int * l ,
     unsigned int * e ,
     unsigned vcount ,
     EulerEdge * ee ,
     unsigned int ecount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y) + threadIdx.x;
     unsigned int eidx = 0;
     if (tid < vcount)
     {
         while (eidx < ev[tid].ecount && eidx < ev[tid].lcount)
         {
             ee[e[ev[tid].ep + eidx]].s = l[ev[tid].lp + eidx];
             eidx++;
         }
     }
 }
