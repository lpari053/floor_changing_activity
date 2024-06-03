//
//  VerticalModel.hpp
//
//  Created by William OCCELLI on 25/02/2022.
//

#ifndef VerticalModel_hpp
#define VerticalModel_hpp

#include <stdio.h>
#include <vector>
#include "onnxruntime/core/session/onnxruntime_cxx_api.h"
#include "onnxruntime_c_api.h"
#include "onnxruntime/core/providers/nnapi/nnapi_provider_factory.h"
#include <android/log.h>
#define LOG_TAG "VerticalModel"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
using namespace std;

class VerticalModel
{
public:
    
    VerticalModel(const char*  verticalModel);
    ~VerticalModel();
    void printLayerNames();
    vector<double> runModel(vector<float> verticalFeatures);
    
private:
    const char* verticalModel_;
    Ort::Env* _env;
    Ort::Session* _session;
    vector<int64_t> _inputShape;
    Ort::MemoryInfo _memoryInfo;
    array<char*, 128> _inputNames;
    array<char*, 128> _outputNames;
}
;

#endif /* VerticalModel_hpp */
