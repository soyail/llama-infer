#include "base/allocator.h"


using namespace base;
void DeviceAllocator::memcpy(void* src_ptr, void* dst_ptr, size_t byte_size,
                            MemcpyKind memcpy_kind, void* stream, bool need_sync) const{
    CHECK_NE(src_ptr, nullptr);
    CHECK_NE(dst_ptr, nullptr);
    if(!byte_size) return;

    cudaStream_t stream_ = nullptr;
    if(stream) {
        stream_ = static_cast<CUstream_st*>(stream);
    }
    if(memcpy_kind==MemcpyKind::MemcpyHostToDevice){
        if(!stream_){
            cudaMemcpy(dst_ptr, src_ptr, byte_size, cudaMemcpyHostToDevice);
        }else{
            cudaMemcpyAsync(dst_ptr, src_ptr, byte_size, cudaMemcpyHostToDevice, stream_);
        }
    } else if(memcpy_kind==MemcpyKind::MemcpyDeviceToHost){
        cudaMemcpy(dst_ptr, src_ptr, byte_size, cudaMemcpyDeviceToHost);
    } else if(memcpy_kind==MemcpyKind::MemcpyHostToHost){
        std::memcpy(dst_ptr, src_ptr, byte_size);
    } else{
        throw std::runtime_error("Invalid Memcpy Kind");
    }

}


CPUDeviceAllocator::CPUDeviceAllocator() : DeviceAllocator(base::DeviceType::DeviceCPU){

}

void* CPUDeviceAllocator::allocate(size_t byte_size) const{
    if(!byte_size) return nullptr;
    void* data = malloc(byte_size);
    return data;
}

void CPUDeviceAllocator::release(void* ptr) const{
    free(ptr);
}



void* CUDADeviceAllocator::allocate(size_t byte_size) const {
    if(!byte_size) return nullptr;
    void* data;
    cudaError_t err = cudaMalloc(&data, byte_size);
    CHECK_EQ(err, cudaSuccess);
    return data;
}

void CUDADeviceAllocator::release(void* ptr) const {
    if(ptr){
        cudaFree(ptr);
    }
}

//std::shared_ptr<CPUDeviceAllocator> CPUDeviceAllocatorFactory::instance = nullptr;

