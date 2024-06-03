//
//  GyroscopeModel.hpp
//
//  Created by William OCCELLI on 25/02/2022.
//

#ifndef GyroscopeModel_hpp
#define GyroscopeModel_hpp

#include <stdio.h>
#include <vector>
#include "onnxruntime/core/session/onnxruntime_cxx_api.h"
#include "onnxruntime_c_api.h"
#include "onnxruntime/core/providers/nnapi/nnapi_provider_factory.h"


using namespace std;

class GyroscopeModel
{
public:
    
    GyroscopeModel(const char*  gyroModel);
    ~GyroscopeModel();
    
    vector<float> runModel(vector<float> gyroscopeFeatures);
    
private:
    const char* gyroModel_;
    Ort::Env* _env;
    Ort::Session* _session;
    vector<int64_t> _inputShape;
    Ort::MemoryInfo _memoryInfo;
    array<char*, 128> _inputNames;
    array<char*, 128> _outputNames;
}
;

#endif /* GyroscopeModel_hpp */
