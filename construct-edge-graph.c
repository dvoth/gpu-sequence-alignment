__global__ void
 constructSuccessorGraph_Step1(
     EulerEdge* e ,
     Vertex * v ,
     unsigned int ecount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     if (tid < ecount)
     {
         v[tid].n1 = ecount;
         v[tid].n2 = ecount;
         v[tid].vid = e[tid].eid;
         v[tid].n1 = e[tid].s;
     }
}

 __global__ void
 constructSuccessorGraph_Step2(
     EulerEdge* e ,
     Vertex * v ,
     unsigned int ecount)
 {
     unsigned int tid =
         (blockDim.x * blockDim.y * gridDim.x * blockIdx.y)
         + (blockDim.x * blockDim.y * blockIdx.x)
         + (blockDim.x * threadIdx.y)
         + threadIdx.x;
     if (tid < ecount)
     {
         if (v[tid].n1 < ecount)
         {
            v[v[tid].n1].n2 = v[tid].vid;
         }
     }
 }
