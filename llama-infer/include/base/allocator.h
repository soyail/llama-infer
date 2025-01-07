#pragma once

#include <cstdlib>
#include <cuda_runtime.h>
#include <memory>
#include "base.h"
#include "glog/logging.h"

class DeviceAllocator {
public:
    explicit DeviceAllocator(base::DeviceType device_type) : device_type_(device_type){}
    virtual ~DeviceAllocator() = default;
    virtual void* allocate(size_t byte_size) const = 0;
    virtual void release(void* ptr) const = 0;
    virtual base::DeviceType device_type(){
        return device_type_;
    }
    virtual void memcpy(void* src_ptr, void* dst_ptr, size_t byte_size, 
                        base::MemcpyKind memcpy_kind = base::MemcpyKind::MemcpyHostToHost, 
                        void* stream = nullptr, bool need_sync=false) const;
private:
    base::DeviceType device_type_ = base::DeviceType::DeviceUnknown;
};



class CPUDeviceAllocator : public DeviceAllocator{
public:
    explicit CPUDeviceAllocator();
    void* allocate(size_t byte_size) const override;
    void release(void* ptr) const override;
};

class CUDADeviceAllocator : public DeviceAllocator{
    public:
    explicit CUDADeviceAllocator();
    void* allocate(size_t byte_size) const override;
    void release(void* ptr) const override;
};

// 通过static方法直接调用,为什么不直接通过构造函数生成？
// class CPUDeviceAllocatorFactory{
// public:
//     static std::shared_ptr<CPUDeviceAllocator> get_instance() {
//         if(instance == nullptr){
//             instance = std::make_shared<CPUDeviceAllocator>();
//         }
//         return instance;
//     }
// private:
//     static std::shared_ptr<CPUDeviceAllocator> instance;
// };