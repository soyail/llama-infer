#include "glog/logging.h"
#include <gtest/gtest.h>
#include "base/buffer.h"

TEST(test_buffer, allocate){
    using namespace base;
    // auto alloc = CPUDeviceAllocatorFactory::get_instance();
    std::shared_ptr<CPUDeviceAllocator> alloc = std::make_shared<CPUDeviceAllocator>();
    Buffer buffer(32, alloc);
    ASSERT_NE(buffer.ptr(), nullptr);
}

TEST(test_buffer, use_external) {
    using namespace base;
    // auto alloc = CPUDeviceAllocatorFactory::get_instance();
    std::shared_ptr<CPUDeviceAllocator> alloc = std::make_shared<CPUDeviceAllocator>();
    float* ptr = new float[32];
    Buffer buffer(32, nullptr, ptr, true);
    ASSERT_EQ(buffer.is_external(), true);
    delete[] ptr;
}