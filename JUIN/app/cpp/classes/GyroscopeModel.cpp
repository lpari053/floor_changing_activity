//
//  GyroscopeModel.cpp
//
//  Created by William OCCELLI on 25/02/2022.
//
#include <iostream>
//#include "onnxruntime_cxx_api.h"
#include <ostream>
#include <vector>
#include <algorithm>
#include <string>

#include "GyroscopeModel.hpp"

GyroscopeModel::GyroscopeModel(const char* gyroModel): _memoryInfo(nullptr),gyroModel_(gyroModel) {
    this->_env = new Ort::Env();
    
    this->_session = new Ort::Session(*this->_env, gyroModel_, Ort::SessionOptions{});
    
    this->_inputShape = (*this->_session).GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
    this->_inputShape[0] = 1;
    
    Ort::AllocatorWithDefaultOptions defaultAllocator;
    char* inputName = (*this->_session).GetInputName(0, defaultAllocator);
    char* outputName1 = (*this->_session).GetOutputName(0, defaultAllocator);
    char* outputName2 = (*this->_session).GetOutputName(1, defaultAllocator);
    this->_inputNames = { inputName };
    this->_outputNames = { outputName1, outputName2 };
    
    this->_memoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
}

vector<float> GyroscopeModel::runModel(vector<float> gyroscopeFeatures) {
    if (gyroscopeFeatures.size() != 8) {
        return {-1, -1};
    }
    
    // create the input tensor (this is not a deep copy!)
    Ort::Value inputOnnxTensorGyro = Ort::Value::CreateTensor<float>(this->_memoryInfo,
                                                                     gyroscopeFeatures.data(),
                                                                     gyroscopeFeatures.size(),
                                                                     this->_inputShape.data(),
                                                                     this->_inputShape.size());
    
    // finally run the inference!
    vector<Ort::Value> outputValuesGyro = (*this->_session).Run(Ort::RunOptions{ nullptr },
                                            this->_inputNames.data(), &inputOnnxTensorGyro, 1,
                                            this->_outputNames.data(), 2);

    // outputValuesGyro[0] is the label, outputValuesGyro[1] are the probabilities
    Ort::Value& outputGyro2 = outputValuesGyro[1];
    const float* valuesGyro2 = outputGyro2.GetTensorMutableData<float>();
    
    return {valuesGyro2[0], valuesGyro2[1]};
}
