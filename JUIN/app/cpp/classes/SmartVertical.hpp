//
//  Features.cpp
//  labcom
//
//  Created by Yohann Tschudi on 15/02/2022.
//

#ifndef SmartVertical_hpp
#define SmartVertical_hpp
#include <android/log.h>
#define LOG_TAG "SmartVertical"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

using namespace std;
#include "Sensors.hpp"
#include "VerticalModel.hpp"
#include "FeaturesCalculatorVertical.hpp"
#include "VerticalProbabilities.hpp"

class SmartVertical {

public:
    // Constructor and destructor
	SmartVertical();
    ~SmartVertical();
	void Init(const char* actiModel);
	vector<double> Inference(Sensors* vectorData, int threshold);

private:
    VerticalModel* verticalModel;
	FeaturesCalculatorVertical *featuresCalculatorvertical;
};

#endif /* SmartVertical_hpp */
