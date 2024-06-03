//
//  VerticalModel.cpp
//
//  Created by William OCCELLI on 25/02/2022.
//
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <string>
#include "VerticalModel.hpp"

#include <android/log.h>
#define LOG_TAG "VerticalModel"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

VerticalModel::VerticalModel(const char* verticalModel) : _memoryInfo(nullptr), verticalModel_(verticalModel) {
    LOGD("Initializing VerticalModel with model: %s", verticalModel);

    this->_env = new Ort::Env();

    try {
        this->_session = new Ort::Session(*this->_env, verticalModel_, Ort::SessionOptions{});
        LOGD("Session created successfully.");

        this->_inputShape = (*this->_session).GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
        this->_inputShape[0] = 1;

        LOGD("Input shape: ");
        for (size_t i = 0; i < this->_inputShape.size(); ++i) {
            LOGD("Dim %zu: %lld", i, this->_inputShape[i]);
        }

        Ort::AllocatorWithDefaultOptions defaultAllocator;
        char* inputName = (*this->_session).GetInputName(0, defaultAllocator);
        char* outputName1 = (*this->_session).GetOutputName(0, defaultAllocator);

        this->_inputNames = { inputName };
        this->_outputNames = { outputName1 };

        LOGD("Input name: %s", inputName);
        LOGD("Output name: %s", outputName1);

        this->_memoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
        LOGD("MemoryInfo created successfully.");

        printLayerNames();

    } catch (const Ort::Exception& e) {
        LOGD("Failed to initialize VerticalModel: %s", e.what());
        throw;  // Re-throw the exception after logging it
    }
}

VerticalModel::~VerticalModel() {
}

void VerticalModel::printLayerNames() {
    size_t numNodes = _session->GetInputCount() + _session->GetOutputCount();
    LOGD("Model contains %zu layers:", numNodes);

    Ort::AllocatorWithDefaultOptions allocator;

    // Print input layer names
    for (size_t i = 0; i < _session->GetInputCount(); ++i) {
        char* inputName = _session->GetInputName(i, allocator);
        LOGD("Input Layer %zu: %s", i, inputName);
        allocator.Free(inputName);  // Free the allocated name
    }

    // Print output layer names
    for (size_t i = 0; i < _session->GetOutputCount(); ++i) {
        char* outputName = _session->GetOutputName(i, allocator);
        LOGD("Output Layer %zu: %s", i, outputName);
        allocator.Free(outputName);  // Free the allocated name
    }
}

std::vector<double> VerticalModel::runModel(std::vector<float> verticalFeatures) {
    LOGD("Running model with %zu features", verticalFeatures.size());

    for (size_t i = 0; i < verticalFeatures.size(); ++i) {
        LOGD("Feature %zu: %f", i, verticalFeatures[i]);
    }

    Ort::Value inputOnnxTensorAcc = Ort::Value::CreateTensor<float>(
            this->_memoryInfo,
            verticalFeatures.data(),
            verticalFeatures.size(),
            this->_inputShape.data(),
            this->_inputShape.size()
    );

    std::vector<Ort::Value> outputValuesAcc = (*this->_session).Run(
            Ort::RunOptions{nullptr},
            this->_inputNames.data(), &inputOnnxTensorAcc, 1,
            this->_outputNames.data(), 1
    );

    Ort::Value& outputAcc = outputValuesAcc[0];
    const float* valuesAcc = outputAcc.GetTensorMutableData<float>();

    // Convert the output to a vector<float>
    std::vector<float> result(valuesAcc, valuesAcc + outputAcc.GetTensorTypeAndShapeInfo().GetElementCount());

    LOGD("Model output:");
    for (size_t i = 0; i < result.size(); ++i) {
        LOGD("Value %zu: %f", i, result[i]);
    }

    auto maxPosition = std::max_element(result.begin(), result.end());
    size_t positionIndex = std::distance(result.begin(), maxPosition);
    double position = static_cast<double>(positionIndex);

    LOGD("Max position index: %zu, value: %f", positionIndex, result[positionIndex]);

    return {position, result[positionIndex]};
}