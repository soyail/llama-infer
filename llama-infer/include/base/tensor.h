#pragma once

#include <cstdlib>
#include "base/buffer.h"
#include "base/base.h"
#include "base/allocator.h"

namespace tensor{
class Tensor{
public:
    explicit Tensor(base::DataType data_type, int32_t size, 
                bool need_alloc, std::shared_ptr<DeviceAllocator> alloc);
    explicit Tensor(base::DataType data_type, std::vector<int32_t>& dims,
                bool need_alloc, std::shared_ptr<DeviceAllocator> alloc);
    explicit Tensor(base::DataType data_type, int32_t size,
                bool need_alloc, std::shared_ptr<DeviceAllocator> alloc, void* ptr);

    void allocate();
    
    bool is_empty(){
        return size_ == 0 || buffer_ == nullptr || buffer_->ptr() == nullptr;
    }

    template <typename T>
    T* ptr();

    template <typename T>
    T* ptr(int64_t index);

    template <typename T>
    T& index(int64_t offset);


private:
    int32_t size_ = 0;
    std::vector<int32_t> dims_;
    std::shared_ptr<base::Buffer> buffer_;
    base::DataType data_type_;
};


template <typename T>
T* Tensor::ptr(){
    if(!buffer_){
        return nullptr;
    }
    return reinterpret_cast<T*>(buffer_->ptr());
}

template <typename T>
T* Tensor::ptr(int64_t index){
    CHECK(buffer_ != nullptr && buffer_->ptr() != nullptr)
        << "The data area buffer of this tensor is empty or it points to a null pointer.";
    return const_cast<T*>(reinterpret_cast<const T*>(buffer_->ptr())) + index;
}

template <typename T>
T& Tensor::index(int64_t offset){
    CHECK_GE(offset, 0);
    CHECK_LT(offset, size_);
    T& val = *(reinterpret_cast<T*>(buffer_->ptr()) + offset);
}
}
