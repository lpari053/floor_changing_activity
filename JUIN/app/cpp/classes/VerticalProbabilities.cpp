//
//  StepProbabilities.cpp
//
//  Created by William OCCELLI on 11/03/2022.
//

#include "VerticalProbabilities.hpp"
#include <android/log.h>
#include <vector>
using namespace std;

//Constructors
VerticalProbabilities::VerticalProbabilities() :
        _vertical(0) {}

void VerticalProbabilities::set_vertical(vector<double> vertical) {
    this->_vertical = vertical;
}

vector<double>  VerticalProbabilities::get_vertical() {
    return this->_vertical;
}

