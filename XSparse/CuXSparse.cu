#include <stdio.h>
#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <helper_functions.h> 
#include "IntList.h"
#include "Pick.h"

__global__ 
void sliceCopyKernel(int *slice_out, int *slice_in, int N)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < N)
    {
        slice_out[idx] = slice_in[idx];
    }
}

__global__ 
void shaffleKernel(float *dst, float *src, int *indexdst, int nd, int N,  int *indexsrc, int *shapedst,    int *shapesrc, int *sizedst, int *sizesrc, int *pick)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    using namespace IntList;
    using namespace Pick;
    if (idx < N)
    {
        int ip = idx*nd;
        PositionToKernelIndex(sizesrc,idx,&indexsrc[ip]);
        ToPickInKernel(pick, &indexsrc[ip], &indexdst[ip]);
        int ps = KernelIndexPosition(shapedst, &indexdst[ip]);
        dst[ps] = src[idx];
    }

}

__global__ 
void ScatterKernel(int * shape, 
    int* indextensor, int N, int * tr, 
    float *u, float *tensor)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    using namespace IntList;
    using namespace Pick;   
   
    int nd = shape[0];
    if (idx < N)
    {
        int ip = idx*nd;
        for(int i = 0;i<nd;i++)
        {
            indextensor[ip+i] = tr[ip+i];
        }

        int ps = KernelIndexPosition(shape, &indextensor[ip]);
        tensor[ps] = u[idx];
    }
    
}


__global__ 
void ScatterXKernel(int * shape, 
    int* indextensor, int N, int * tr, 
    float *u, float *tensor)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    using namespace IntList;
    using namespace Pick;   
   
    int nd = shape[0];
    if (idx < N)
    {
        int ip = idx*nd;
        for(int i = 0;i<nd;i++)
        {
            indextensor[ip+i] = tr[ip+i];
        }

        int ps = KernelIndexPosition(shape, &indextensor[ip]);
        tensor[ps] = u[idx];
    }
    
}



