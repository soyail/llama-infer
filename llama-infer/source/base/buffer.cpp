#include "base/buffer.h"

namespace base{
    Buffer::Buffer(size_t byte_size, std::shared_ptr<DeviceAllocator> allocator, void* ptr, bool use_external)
        : byte_size_(byte_size),
          allocator_(allocator),
          ptr_(ptr),
          use_external_(use_external){
        if(!ptr_ && allocator_){
            device_type_ = allocator_->device_type();
            use_external_ = false;
            ptr_ = allocator_->allocate(byte_size); 
        }
    }
    Buffer::~Buffer(){
        if(!use_external_){
            if(ptr_&&allocator_){
                allocator_->release(ptr_);
                ptr_ = nullptr;
            }
        }
    }
    void Buffer::allocate(){
        if(allocator_ && byte_size_!=0){
            // why?
            use_external_ = false;
            ptr_ = allocator_->allocate(byte_size_);
        }
        
    }
}

