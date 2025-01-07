#pragma once

#include <string>
#include <cstdlib>

#include "base/base.h"
#include "base/tensor.h"

enum class LayerType{
    Conv,
    Sigmoid
};

class BaseLayer{
    public:
    explicit BaseLayer(base::DeviceType device_type, LayerType layer_type,
                       base::DataType data_type, std::string layer_name = "");

    protected:
        base::DeviceType device_type_;
        LayerType layer_type_;
        base::DataType data_type_;
        std::string layer_name_;
};

class Layer : public BaseLayer{
    public:
    explicit Layer(base::DeviceType device_type, LayerType layer_type, 
                   base::DataType data_type, std::string layer_name = "");

    void set_input(int32_t index, tensor::Tensor& input) override;

    tensor::Tensor& get_input(int32_t index) const override;

    tensor::Tensor& get_output(int32_t index) const override;

    private:
    std::vector<torch::Tensor> inputs_;
    std::vector<torch::Tensor> outputs_;
}