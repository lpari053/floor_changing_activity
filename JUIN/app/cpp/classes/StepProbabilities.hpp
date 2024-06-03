//
//  StepProbabilities.hpp
//
//  Created by William OCCELLI on 11/03/2022.
//

#ifndef StepProbabilities_hpp
#define StepProbabilities_hpp

#include <stdio.h>

class StepProbabilities
{
public:
    StepProbabilities();
    StepProbabilities(float gyroProb0, float gyroProb1, float accProb0, float accProb1, bool isStepInstant);
    ~StepProbabilities();
    
    void set_gyroProb0(float);
    float get_gyroProb0();
    void set_gyroProb1(float);
    float get_gyroProb1();
    
    void set_accProb0(float);
    float get_accProb0();
    void set_accProb1(float);
    float get_accProb1();
    
    void set_isStepInstant(bool);
    bool get_isStepInstant();
    
private:
    float _gyroProb0;
    float _gyroProb1;
    float _accProb0;
    float _accProb1;
    bool _isStepInstant;
};

#endif /* StepProbabilities_hpp */
