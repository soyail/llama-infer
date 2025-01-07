#include <gtest/gtest.h>
#include <glog/logging.h>

#include "base/tensor.h"

TEST(test_tensor, init){
    using namespace base;
    //auto alloc = CPUDeviceAllocator::get_instance();
    std::shared_ptr<CPUDeviceAllocator> alloc_cpu = std::make_shared<CPUDeviceAllocator>();
    int32_t size = 32 * 151;
    tensor::Tensor t1(DataType::FLOAT32, size, true, alloc_cpu);
    ASSERT_EQ(t1.is_empty(), false);
}

TEST(test_tensor, init1){
    using namespace base;
    std::shared_ptr<CPUDeviceAllocator> alloc_cpu = std::make_shared<CPUDeviceAllocator>();
    std::vector<int32_t> dims = {32, 151};
    tensor::Tensor t1(DataType::FLOAT32, dims, true, alloc_cpu);
    ASSERT_EQ(t1.is_empty(), false);
}

TEST(test_init, init2){
    using namespace base;
    std::shared_ptr<CPUDeviceAllocator> alloc_cpu = std::make_shared<CPUDeviceAllocator>();
    int32_t size = 32;
    float* ptr = new float[size];
    ptr[0] = 31;
    tensor::Tensor t1(DataType::FLOAT32, size, false, alloc_cpu, ptr);
    ASSERT_EQ(t1.is_empty(), false);
    ASSERT_EQ(t1.ptr<float>(), ptr);
    ASSERT_EQ(*t1.ptr<float>(), 31);
}

TEST(test_tensor, index){
    using namespace base;
    std::shared_ptr<CPUDeviceAllocator> alloc_cpu = std::make_shared<CPUDeviceAllocator>();
    int32_t size = 32;
    float* ptr = new float[size];
    ptr[0] = 31;
    tensor::Tensor t1(DataType::FLOAT32, size, false, nullptr, ptr);
    void* p1 = t1.ptr<void>();
    p1 += 1;
    float* f1 = t1.ptr<float>();
    f1 += 1;
    ASSERT_NE(f1, p1);
    delete[] ptr;
}