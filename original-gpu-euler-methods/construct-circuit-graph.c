__global__ void
 calculateCircuitGraphVertexData(
     unsigned int * D ,
     unsigned int * C ,
     unsigned int ecount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y) + threadIdx.x;
     if (tid < ecount)
     {
         unsigned int c = D[tid];
         atomicExch( C + c, 1);
     }
 }

 __global__ void
 constructCircuitGraphVertex(
     unsigned int * C ,
     unsigned int * offset ,
     unsigned int ecount ,
     unsigned int * cv ,
     unsigned int cvCount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     if (tid < ecount)
     {
         if (C[tid] != 0)
         {
            cv[offset[tid]] = tid;
         }
     }
 }

 __global__ void
 calculateCircuitGraphEdgeData(
     EulerVertex* v ,

     unsigned int * e ,
     unsigned vCount ,
     unsigned int * D ,
     unsigned int * map ,
     unsigned int ecount ,
     unsigned int * cedgeCount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     unsigned int index = 0;
     unsigned int maxIndex = 0;
     index = 0;
     maxIndex = 0;
     if (tid < vCount && v[tid].ecount > 0)
     {
         index = v[tid].ep;
         maxIndex = index + v[tid].ecount - 1;
         while (index < maxIndex)
         {
             unsigned int c1 = map[D[e[index]]];
             unsigned int c2 = map[D[e[index + 1]]];
             if (c1 != c2)
             {
                 unsigned int c = min( c1, c2);
                 atomicInc( cedgeCount + c, ecount);
             }

             index++;
         }
     }
 }
 __global__ void
 assignCircuitGraphEdgeData(
     EulerVertex* v ,
     unsigned int * e ,
     unsigned vCount ,
     unsigned int * D ,
     unsigned int * map ,
     unsigned int ecount ,
     unsigned int * cedgeOffset ,
     unsigned int * cedgeCount ,
     unsigned int cvCount ,
     CircuitEdge * cedge ,
     unsigned int cecount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     unsigned int index = 0;
     unsigned int maxIndex = 0;
     if (tid < vCount && v[tid].ecount > 0)
     {
         index = v[tid].ep;
         maxIndex = index + v[tid].ecount - 1;
         while (index < maxIndex)
         {
             unsigned int c1 = map[D[e[index]]];
             unsigned int c2 = map[D[e[index + 1]]];
             if (c1 != c2)
             {
                 unsigned int c = min( c1, c2);
                 unsigned int t = max( c1, c2);
                 unsigned int i = atomicDec( cedgeCount + c, ecount);
                 i = i - 1;
                 cedge[cedgeOffset[c] + i].c1 = c;
                 cedge[cedgeOffset[c] + i].c2 = t;
                 cedge[cedgeOffset[c] + i].e1 = e[index];
                 cedge[cedgeOffset[c] + i].e2 = e[index + 1];
             }
             index++;
         }
     }
 }
