//
//  AccelerometerModel.hpp
//
//  Created by William OCCELLI on 25/02/2022.
//

#ifndef AccelerometerModel_hpp
#define AccelerometerModel_hpp

#include <stdio.h>
#include <vector>
#include "onnxruntime/core/session/onnxruntime_cxx_api.h"
#include "onnxruntime_c_api.h"
#include "onnxruntime/core/providers/nnapi/nnapi_provider_factory.h"

using namespace std;

class AccelerometerModel
{
public:
    
    AccelerometerModel(const char*  accModel);
    ~AccelerometerModel();
    
    vector<float> runModel(vector<float> accelerometerFeatures);
    
private:
    const char* accModel_;
    Ort::Env* _env;
    Ort::Session* _session;
    vector<int64_t> _inputShape;
    Ort::MemoryInfo _memoryInfo;
    array<char*, 128> _inputNames;
    array<char*, 128> _outputNames;
}
;

#endif /* AccelerometerModel_hpp */
