//
//  Features.cpp
//  labcom
//
//  Created by Yohann Tschudi on 15/02/2022.
//

#ifndef Smartstep_hpp
#define Smartstep_hpp



using namespace std;
#include "Sensors.hpp"
#include "AccelerometerModel.hpp"
#include "GyroscopeModel.hpp"
#include "FeaturesCalculator.hpp"
#include "StepProbabilities.hpp"

class Smartstep {
    
public:
    // Constructor and destructor
	Smartstep();
    ~Smartstep();
	void Init(const char* accModel, const char* gyroModel);
	double Inference(Sensors* vectorData, int threshold);
        
private:
    // Parameters
	AccelerometerModel* accelerometerModel;
	GyroscopeModel* gyroscopeModel;
	FeaturesCalculator *featuresCalculator;
	StepProbabilities* stepProbabilities;
};

#endif /* Smartstep_hpp */
