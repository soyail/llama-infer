
#include "kernel/add.h"

__global__ void add_kernel(
    const float* input1,
    const float* input2,
    const int size,
    float* output
){
    int idx = threadIdx.x + blockIdx.x * gridDim.x;
    if(idx<size){
        output[idx] = input1[idx] + input2[idx];
    }
}


void add_gpu(
    const float* input1,
    const float* input2,
    const int size,
    float* output
){
    dim3 blockDim(32*32);
    dim3 gridDim((size-blockDim.x+1)/(blockDim.x));
    add_kernel<<<gridDim, blockDim>>>(input1, input2, size, output);
}