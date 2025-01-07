

#include "op/add.h"

namespace op{

AddLayer::AddLayer(base::DeviceType device_type) : device_type_(device_type) {};

tensor::Tensor AddLayer::forward(){
    auto input1 = get_input(0);
    auto input2 = get_input(1);
    auto output = get_output(0);
    if(device_type_ == base::DeviceType::DeviceGPU){
        add_gpu(input1, input2, ,output)
    }
}

}