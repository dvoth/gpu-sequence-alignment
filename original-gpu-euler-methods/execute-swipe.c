__global__ void
 executeSwipe(
     EulerVertex * ev ,
     unsigned int * e ,
     unsigned int vcount ,
     EulerEdge * ee ,
     unsigned int * mark ,
     unsigned int ecount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     unsigned int t;
     unsigned int index = 0;
     unsigned int maxIndex;
     unsigned int s;
     if (tid < vcount)
     {
         index = ev[tid].ep;
         maxIndex = index + ev[tid].ecount - 1;
         while (index < maxIndex){
             if (mark[ee[e[index]].eid] == 1)
             {
                 t = index;
                 s = ee[e[index]].s;
                 while (mark[ee[e[index]].eid] == 1 && index < maxIndex)
                 {
                     ee[e[index]].s = ee[e[index + 1]].s;
                     index = index + 1;
                 }
                 if (t != index){
                    ee[e[index]].s = s;
                 }
             }
             index++;
         }
     }
 }
