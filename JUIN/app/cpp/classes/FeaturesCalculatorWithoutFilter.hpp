//
//  Features.cpp
//  labcom
//
//  Created by Yohann Tschudi on 15/02/2022.
//

#ifndef FEATURESW_H_INCLUDED
#define FEATURESW_H_INCLUDED

#include <vector>
#include <complex>
#include <iostream>
#include <numeric>
#include <valarray>
#include <Eigen/Geometry>

#include "FFT.hpp"
#include "Filter.hpp"
#include "PeakFinder.hpp"
#include "Sensors.hpp"
#include "Features.hpp"

using namespace std;

class FeaturesCalculatorWithoutFilter {
    
public:
    // Constructor and destructor
    FeaturesCalculatorWithoutFilter();
    ~FeaturesCalculatorWithoutFilter();
    
    // Main functions
    Features* computeFeatures(Sensors*, int);

private:
    // Parameters
    // Buffer accelero and gyro
    vector<double> _acc_norm;
    vector<double> _gyro_norm;
    vector<double> _acc_norm_nf; //nf indicated no filtered
    vector<double> _gyro_norm_nf;
    vector<double> _acc_x;
    vector<double> _acc_y;
    vector<double> _acc_z;
    vector<double> _gyro_x;
    vector<double> _gyro_y;
    vector<double> _gyro_z;
    vector<double> _mag_x;
    vector<double> _mag_y;
    vector<double> _mag_z;
    vector<double> _mag_norm;
    vector<double> _mag_norm_nf;
    
    // Vector functions
    vector<double> scalarProduct(const vector<double>&, double);
    vector<double> extractVector(const vector<double>&, int, int);
    void rotateAndInsert(vector<double>&, double);
    int findMiddle(const vector<double>&);
    int findMiddle(const vector<int>&);
    double getMinElement(const vector<double>&);
    double getMaxElement(const vector<double>&);
    double getMaxValue(const vector<double>&);
    int getMaxArrayIndex(const valarray<complex<double>>&);
    valarray<complex<double>> getAbsoluteArray(const valarray<complex<double>>&);
    
    // Features functions
    double computeSMA(const vector<double>&);
    double computeNorm(const double&, const double&, const double&);
    double computeNorm(const vector<double>&);
    double computeVariance(const vector<double>&, const double&, int);
    double computeMean(const vector<double>&);
    double computeLerp(double, double, double);
    double computeQuantile(const vector<double>&);
    double computeKurtosis(const vector<double>&);
    double computeSkewness(const vector<double>&);
    double computeProminence(const vector<double>&, double, int, int);
    vector<double> computeDominantFrequency(const vector<double>&);
};

#endif // FEATURESW_H_INCLUDED
