
#include "op/rmsnorm_kernel.h"

void rmsnorm_kernel_cpu(
    int32_t dim,
    const tensor::Tensor& input,
    const tensor::Tensor& weights,
    const tensor::Tensor& output
){
    const float* in_ptr = input.ptr<float>();
    const float* weight_ptr = weights.ptr<float>();
    float* out_ptr = output.ptr<float>();

    
}

op::RMSNormKernel op::get_rmsnorm_kernel(base::DeviceType device_type){
    if(device_type == base::DeviceType::DeviceCPU){
        return rmsnorm_kernel_cpu;
    } 
    else if(device_type == base::DeviceType::DeviceGPU){
        return rmsnorm_kernel_gpu;
    }
    else{
        LOG(FATAL) << "unknown device type for get an rmsnorm kernel.";
        return nullptr;
    }
}

