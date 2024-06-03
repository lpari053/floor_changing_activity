//
//  StepProbabilities.cpp
//
//  Created by William OCCELLI on 11/03/2022.
//

#include "StepProbabilities.hpp"

using namespace std;

//Constructors
StepProbabilities::StepProbabilities() :
_gyroProb0(0), _gyroProb1(0), _accProb0(0),_accProb1(0), _isStepInstant(false) {}

void StepProbabilities::set_gyroProb0(float gyroProb0) {
    this->_gyroProb0 = gyroProb0;
}
void StepProbabilities::set_gyroProb1(float gyroProb1) {
    this->_gyroProb1 = gyroProb1;
}
void StepProbabilities::set_accProb0(float accProb0) {
    this->_accProb0 = accProb0;
}
void StepProbabilities::set_accProb1(float accProb1) {
    this->_accProb1 = accProb1;
}
void StepProbabilities::set_isStepInstant(bool isStepInstant) {
    this->_isStepInstant = isStepInstant;
}


float StepProbabilities::get_gyroProb0() {
    return this->_gyroProb0;
}
float StepProbabilities::get_gyroProb1() {
    return this->_gyroProb1;
}
float StepProbabilities::get_accProb0() {
    return this->_accProb0;
}
float StepProbabilities::get_accProb1() {
    return this->_accProb1;
}
bool StepProbabilities::get_isStepInstant() {
    return this->_isStepInstant;
}
