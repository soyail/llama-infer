#include "base/tensor.h"


namespace tensor{

Tensor::Tensor(base::DataType data_type, int32_t size,
               bool need_alloc, std::shared_ptr<DeviceAllocator> alloc)
: data_type_(data_type), size_(size){
    // TODO: use_external_ = true or false;
    std::shared_ptr<base::Buffer> buffer = 
        std::make_shared<base::Buffer>(Getdatatypesize(data_type)*size_, alloc, nullptr, true);
    buffer_ = buffer;
    if(need_alloc && alloc){
        allocate();
    }
}

Tensor::Tensor(base::DataType data_type, std::vector<int32_t>& dims,
            bool need_alloc, std::shared_ptr<DeviceAllocator> alloc)
: data_type_(data_type), dims_(dims) {
    size_ = 1;
    for(int32_t dim:dims){
        size_ *= dim;
    }
    std::shared_ptr<base::Buffer> buffer = 
        std::make_shared<base::Buffer>(Getdatatypesize(data_type)*size_, alloc, nullptr, true);
    buffer_ = buffer;
    if(need_alloc && alloc){
        allocate();
    }
}

Tensor::Tensor(base::DataType data_type, int32_t size,
               bool need_alloc, std::shared_ptr<DeviceAllocator> alloc, void* ptr)
: data_type_(data_type), size_(size){
    if(ptr!=nullptr){
        CHECK(need_alloc == false)
            << "The need_alloc is true when ptr parameter is not a null pointer.";
        if(alloc){
            std::shared_ptr<base::Buffer> buffer = 
                std::make_shared<base::Buffer>(Getdatatypesize(data_type)*size_, alloc, ptr, false);
            buffer_ = buffer;
        }else{
            std::shared_ptr<base::Buffer> buffer = 
                std::make_shared<base::Buffer>(Getdatatypesize(data_type)*size_, nullptr, ptr, true);
            buffer_ = buffer;
        }
    }
}

void Tensor::allocate(){
    buffer_->allocate();
}


}
                                                                 