//
//  Filter.hpp
//  labcom
//
//  Created by Yohann Tschudi on 01/04/2022.
//

#ifndef FILTER_HPP_INCLUDED
#define FILTER_HPP_INCLUDED

#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <complex>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

using namespace std;

class Filter {
    
public:
    vector<double> filtfilt(vector<double> vectorData, int axis = 0);
    
private:
    int lfilter(vector<double> b, vector<double> a, vector<double> x, vector<double> zi, vector<double> &y);
    int lfilter_zi(Eigen::VectorXd b, Eigen::VectorXd a, Eigen::VectorXd & zi);
    int odd_ext(vector<double> x, int n, int axis, vector<double> & ext);
    void axis_slice(vector<double> a, vector<double> & out, int start = 0, int stop = INFINITY, int step = 1, int axis = 0);
    int validate_pad(vector<double> x, int axis, int ntaps, int & edge, vector<double> & ext);
    void reverse_vector(vector<double> in, vector<double> & out);
    void multiplyVectorByScalar(vector<double> &v, double k);
    //void reverse_matrix(Eigen::MatrixXd in, Eigen::MatrixXd & out);
    
    // Parameters
    vector<double>  b0 = {5.51456216845228e-12, 5.51456216845228e-11, 2.48155297580353e-10, 6.61747460214274e-10, 1.15805805537498e-09, 1.38966966644997e-09, 1.15805805537498e-09, 6.61747460214274e-10, 2.48155297580353e-10, 5.51456216845228e-11, 5.51456216845228e-12};
    Eigen::VectorXd b = Eigen::VectorXd::Map(b0.data(),b0.size());
    
    vector<double> a0 = {1.0, -8.99594505535417, 36.4633075498862, -87.6908102873418, 138.559912556039, -150.302116273606, 113.348650426591, -58.6790854259776, 19.9562604962225, -4.02604302102184, 0.365869040210561};
    Eigen::VectorXd a = Eigen::VectorXd::Map(a0.data(),a0.size());

};

#endif // FILTER_HPP_INCLUDED
