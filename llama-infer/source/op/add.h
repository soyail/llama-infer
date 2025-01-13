#pragma once

#include "base/op.h"
#include "base/base.h"
#include "kernel/add.h"

namespace op{
class AddLayer : public Layer{
public:
    explicit AddLayer(base::DeviceType device_type);

    tensor::Tensor forward() override;
}
}