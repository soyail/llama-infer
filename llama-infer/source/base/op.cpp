#include "base/op.h"
#include <glog/logging.h>


void Layer::set_input(int32_t index, tensor::Tensor& input){
    CHECK_GE(index, 0);
    inputs_[index] = input;
}

tensor::Tensor& Layer::get_input(int32_t index){
    CHECK_GE(index, 0);
    CHECK_LT(index, inputs_.size());
    return inputs_[index];
}

tensor::Tensor& Layer::get_output(int32_t index){
    CHECK_GE(index, 0);
    CHECK_LT(index, outputs_.size());
    return outputs_[index];
}