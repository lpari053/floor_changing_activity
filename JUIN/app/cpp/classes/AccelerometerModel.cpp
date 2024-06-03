//
//  AccelerometerModel.cpp
//
//  Created by William OCCELLI on 25/02/2022.
//
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <string>
#include "AccelerometerModel.hpp"

AccelerometerModel::AccelerometerModel(const char* accModel): _memoryInfo(nullptr),accModel_(accModel){
    this->_env = new Ort::Env();
    
    this->_session = new Ort::Session(*this->_env, accModel_, Ort::SessionOptions{});
    
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
AccelerometerModel::~AccelerometerModel() {}
vector<float> AccelerometerModel::runModel(vector<float> accelerometerFeatures) {
    if (accelerometerFeatures.size() != 8) {
        return {-1, -1};
    }
    
    // create the input tensor (this is not a deep copy!)
    Ort::Value inputOnnxTensorAcc = Ort::Value::CreateTensor<float>(this->_memoryInfo,
                                                              accelerometerFeatures.data(),
                                                              accelerometerFeatures.size(),
                                                              this->_inputShape.data(),
                                                              this->_inputShape.size());
    
    // finally run the inference!
    vector<Ort::Value> outputValuesAcc = (*this->_session).Run(Ort::RunOptions{ nullptr },
                                                 this->_inputNames.data(), &inputOnnxTensorAcc, 1,
                                                 this->_outputNames.data(), 2);
    
    // outputValuesGyro[0] is the label, outputValuesGyro[1] are the probabilities
    Ort::Value& outputAcc2 = outputValuesAcc[1];
    const float* valuesAcc2 = outputAcc2.GetTensorMutableData<float>();
    
    return {valuesAcc2[0], valuesAcc2[1]};
}
