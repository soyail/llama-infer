#pragma once


namespace base{
    enum class DeviceType{
        DeviceUnknown = 0,
        DeviceCPU = 1,
        DeviceGPU = 2
    };

    enum class MemcpyKind{
        MemcpyHostToDevice,
        MemcpyDeviceToHost,
        MemcpyHostToHost
    };

    enum class DataType{
        FLOAT32,
        FLOAT16,
        INT32,
        INT8
    };

    inline size_t Getdatatypesize(DataType data_type){
        if(data_type == DataType::FLOAT32){
            return sizeof(float);
        }else if(data_type == DataType::FLOAT16){
            return 2;
        }else if(data_type == DataType::INT32){
            return sizeof(int32_t);
        }else if(data_type == DataType::INT8){
            return sizeof(int8_t);
        }else{
            return 0;
        }
    }
}
