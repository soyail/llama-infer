#pragma once

#include <cstdlib>

#include "base/allocator.h"
#include "base/base.h"

namespace base{
class Buffer{
public:
    explicit Buffer() = default;
    explicit Buffer(size_t byte_size, std::shared_ptr<DeviceAllocator> allocator = nullptr,
                    void* ptr = nullptr, bool use_external = false);
    virtual ~Buffer();
    void allocate();
    bool is_external(){
        return use_external_;
    };
    void* ptr(){
        return ptr_;
    };
private:
    size_t byte_size_ = 0;
    DeviceType device_type_ = DeviceType::DeviceUnknown;
    std::shared_ptr<DeviceAllocator> allocator_;
    void* ptr_;
    bool use_external_ = false;
};
}