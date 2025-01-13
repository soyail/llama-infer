#pragma once

#include <cuda_runtime.h>

void add_gpu(
    const float* input1,
    const float* input2,
    const int size,
    float* output
);