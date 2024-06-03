//
//  Features.cpp
//  labcom
//
//  Created by William OCCELLI on 08/04/2022.
//

#include "Features.hpp"

Features::Features():
_acc_median_win80(0.0), _acc_kurtosis_win30(0.0), _acc_skewness_win5(0.0), _acc_minElement_win30(0.0), _acc_peak_prominences_win50(0.0), _acc_peak_prominences_win80(0.0), _acc_valley_prominences_win80(0.0),
_gyro_skewness_win70(0.0), _gyro_skewness_win30(0.0), _gyro_maxElement_win60(0.0),
_gyro_sma_win80(0.0), _gyro_variance_win20(0.0), _gyro_maxValue_win70(0.0),
_gyro_valley_prominences_win80(0.0), _acc_dominant_frequency(0.0),_gyro_max_frequency(0.0),
_mag_skewness_win70(0.0), _mag_skewness_win30(0.0), _mag_maxElement_win60(0.0),
_mag_sma_win80(0.0), _mag_variance_win20(0.0), _mag_maxValue_win70(0.0),
_mag_valley_prominences_win80(0.0),_mag_max_frequency(0.0),






_acc_norm_aad(0.0),_acc_norm_kurt(0.0),
_acc_norm_mean(0.0),
_acc_norm_skew(0.0),_acc_norm_mad(0.0),_acc_norm_std(0.0),

_gyro_norm_aad(0.0),_gyro_norm_kurt(0.0),
_gyro_norm_mean(0.0),
_gyro_norm_skew(0.0),_gyro_norm_mad(0.0),_gyro_norm_std(0.0),

_mag_norm_aad(0.0),_mag_norm_kurt(0.0),
_mag_norm_mean(0.0),
_mag_norm_skew(0.0),_mag_norm_mad(0.0),_mag_norm_std(0.0),

_acc_x_aad(0.0),_acc_x_arc(0.0),_acc_x_kurt(0.0),
_acc_x_mean(0.0),_acc_x_pc(0.0),
_acc_x_skew(0.0),_acc_x_mad(0.0),_acc_x_std(0.0),

_acc_y_aad(0.0),_acc_y_arc(0.0),_acc_y_kurt(0.0),
_acc_y_mean(0.0),_acc_y_pc(0.0),
_acc_y_skew(0.0),_acc_y_mad(0.0),_acc_y_std(0.0),


_acc_z_aad(0.0),_acc_z_arc(0.0),_acc_z_kurt(0.0),
_acc_z_mean(0.0),_acc_z_pc(0.0),
_acc_z_skew(0.0),_acc_z_mad(0.0),_acc_z_std(0.0),

_gyr_x_aad(0.0),_gyr_x_arc(0.0),_gyr_x_kurt(0.0),
_gyr_x_mean(0.0),_gyr_x_pc(0.0),
_gyr_x_skew(0.0),_gyr_x_mad(0.0),_gyr_x_std(0.0),

_gyr_y_aad(0.0),_gyr_y_arc(0.0),_gyr_y_kurt(0.0),
_gyr_y_mean(0.0),_gyr_y_pc(0.0),
_gyr_y_skew(0.0),_gyr_y_mad(0.0),_gyr_y_std(0.0),


_gyr_z_aad(0.0),_gyr_z_arc(0.0),_gyr_z_kurt(0.0),
_gyr_z_mean(0.0),_gyr_z_pc(0.0),
_gyr_z_skew(0.0),_gyr_z_mad(0.0),_gyr_z_std(0.0),

_mag_x_aad(0.0),_mag_x_arc(0.0),_mag_x_kurt(0.0),
_mag_x_mean(0.0),_mag_x_pc(0.0),
_mag_x_skew(0.0),_mag_x_mad(0.0),_mag_x_std(0.0),

_mag_y_aad(0.0),_mag_y_arc(0.0),_mag_y_kurt(0.0),
_mag_y_mean(0.0),_mag_y_pc(0.0),
_mag_y_skew(0.0),_mag_y_mad(0.0),_mag_y_std(0.0),


_mag_z_aad(0.0),_mag_z_arc(0.0),_mag_z_kurt(0.0),
_mag_z_mean(0.0),_mag_z_pc(0.0),
_mag_z_skew(0.0),_mag_z_mad(0.0),_mag_z_std(0.0),

_baro_aad(0.0),_baro_arc(0.0),_baro_kurt(0.0),
_baro_mean(0.0),_baro_pc(0.0),
_baro_skew(0.0),_baro_mad(0.0),_baro_std(0.0) ,

nb_step(0)












{}

//Accelerometer features
void Features::set_acc_median_win80(double acc_median_win80) {
    this->_acc_median_win80 = acc_median_win80;
}
void Features::set_acc_kurtosis_win30(double acc_kurtosis_win30) {
    this->_acc_kurtosis_win30 = acc_kurtosis_win30;
}
void Features::set_acc_skewness_win5(double acc_skewness_win5) {
    this->_acc_skewness_win5 = acc_skewness_win5;
}
void Features::set_acc_minElement_win30(double acc_minElement_win30) {
    this->_acc_minElement_win30 = acc_minElement_win30;
}
void Features::set_acc_valley_prominences_win80(double acc_valley_prominences80) {
    this->_acc_valley_prominences_win80 = acc_valley_prominences80;
}
void Features::set_acc_peak_prominences_win50(double acc_peak_prominences50) {
    this->_acc_peak_prominences_win50 = acc_peak_prominences50;
}
void Features::set_acc_peak_prominences_win80(double acc_peak_prominences80) {
    this->_acc_peak_prominences_win80 = acc_peak_prominences80;
}
void Features::set_acc_dominant_frequency(double acc_domfreq1){
    this->_acc_dominant_frequency=acc_domfreq1;
}
double Features::get_acc_median_win80() const {
    return this->_acc_median_win80;
}
double Features::get_acc_kurtosis_win30() const {
    return this->_acc_kurtosis_win30;
}
double Features::get_acc_skewness_win5() const {
    return this->_acc_skewness_win5;
}
double Features::get_acc_minElement_win30() const {
    return this->_acc_minElement_win30;
}
double Features::get_acc_peak_prominences_win50() const {
    return this->_acc_peak_prominences_win50;
}
double Features::get_acc_peak_prominences_win80() const {
    return this->_acc_peak_prominences_win80;
}
double Features::get_acc_valley_prominences_win80() const {
    return this->_acc_valley_prominences_win80;
}
double Features::get_acc_dominant_frequency() const{
    return this->_acc_dominant_frequency;
}

// Gyroscope
void Features::set_gyro_skewness_win70(double gyro_skewness_win70) {
    this->_gyro_skewness_win70 = gyro_skewness_win70;
}
void Features::set_gyro_skewness_win30(double gyro_skewness_win30) {
    this->_gyro_skewness_win30 = gyro_skewness_win30;
}
void Features::set_gyro_maxElement_win60(double gyro_maxElement_win60) {
    this->_gyro_maxElement_win60 = gyro_maxElement_win60;
}
void Features::set_gyro_sma_win80(double gyro_sma_win80) {
    this->_gyro_sma_win80 = gyro_sma_win80;
}
void Features::set_gyro_maxValue_win70(double gyro_maxValue_win70) {
    this->_gyro_maxValue_win70 = gyro_maxValue_win70;
}
void Features::set_gyro_variance_win20(double gyro_variance_win20) {
    this->_gyro_variance_win20 = gyro_variance_win20;
}
void Features::set_gyro_valley_prominences_win80(double gyro_valley_prominences80) {
    this->_gyro_valley_prominences_win80 = gyro_valley_prominences80;
}
void Features::set_gyro_max_frequency(double gyro_max_freq_val){
    this ->_gyro_max_frequency= gyro_max_freq_val;
}
double Features::get_gyro_skewness_win70() const {
    return this->_gyro_skewness_win70;
}
double Features::get_gyro_skewness_win30() const {
    return this->_gyro_skewness_win30;
}
double Features::get_gyro_maxElement_win60() const {
    return this->_gyro_maxElement_win60;
}
double Features::get_gyro_sma_win80() const {
    return this->_gyro_sma_win80;
}
double Features::get_gyro_variance_win20() const {
    return this->_gyro_variance_win20;
}
double Features::get_gyro_maxValue_win70() const {
    return this->_gyro_maxValue_win70;
}
double Features::get_gyro_valley_prominences_win80() const {
    return this->_gyro_valley_prominences_win80;
}
double Features::get_gyro_max_frequency() const{
    return this->_gyro_max_frequency;
}


//Magnetometer

void Features::set_mag_skewness_win70(double mag_skewness_win70) {
    this->_mag_skewness_win70 = mag_skewness_win70;
}
void Features::set_mag_skewness_win30(double mag_skewness_win30) {
    this->_mag_skewness_win30 = mag_skewness_win30;
}
void Features::set_mag_maxElement_win60(double mag_maxElement_win60) {
    this->_mag_maxElement_win60 = mag_maxElement_win60;
}
void Features::set_mag_sma_win80(double mag_sma_win80) {
    this->_mag_sma_win80 = mag_sma_win80;
}
void Features::set_mag_maxValue_win70(double mag_maxValue_win70) {
    this->_mag_maxValue_win70 = mag_maxValue_win70;
}
void Features::set_mag_variance_win20(double mag_variance_win20) {
    this->_mag_variance_win20 = mag_variance_win20;
}
void Features::set_mag_valley_prominences_win80(double mag_valley_prominences80) {
    this->_mag_valley_prominences_win80 = mag_valley_prominences80;
}
void Features::set_mag_max_frequency(double mag_max_freq_val){
    this ->_mag_max_frequency= mag_max_freq_val;
}
double Features::get_mag_skewness_win70() const {
    return this->_mag_skewness_win70;
}
double Features::get_mag_skewness_win30() const {
    return this->_mag_skewness_win30;
}
double Features::get_mag_maxElement_win60() const {
    return this->_mag_maxElement_win60;
}
double Features::get_mag_sma_win80() const {
    return this->_mag_sma_win80;
}
double Features::get_mag_variance_win20() const {
    return this->_mag_variance_win20;
}
double Features::get_mag_maxValue_win70() const {
    return this->_mag_maxValue_win70;
}
double Features::get_mag_valley_prominences_win80() const {
    return this->_mag_valley_prominences_win80;
}
double Features::get_mag_max_frequency() const{
    return this->_mag_max_frequency;
}




void Features::set_acc_norm_mean(double acc_norm_mean) {
    this->_acc_norm_mean = acc_norm_mean;
}
double Features::get_acc_norm_mean() const {
    return this->_acc_norm_mean;
}

void Features::set_acc_norm_std(double acc_norm_std) {
    this->_acc_norm_std = acc_norm_std;
}
double Features::get_acc_norm_std() const {
    return this->_acc_norm_std;
}

void Features::set_acc_norm_mad(double acc_norm_mad) {
    this->_acc_norm_mad = acc_norm_mad;
}
double Features::get_acc_norm_mad() const {
    return this->_acc_norm_mad;
}

void Features::set_acc_norm_kurt(double acc_norm_kurt) {
    this->_acc_norm_kurt = acc_norm_kurt;
}
double Features::get_acc_norm_kurt() const {
    return this->_acc_norm_kurt;
}

void Features::set_acc_norm_skew(double acc_norm_skew) {
    this->_acc_norm_skew = acc_norm_skew;
}
double Features::get_acc_norm_skew() const {
    return this->_acc_norm_skew;
}

void Features::set_acc_norm_aad(double acc_norm_aad) {
    this->_acc_norm_aad = acc_norm_aad;
}
double Features::get_acc_norm_aad() const {
    return this->_acc_norm_aad;
}


void Features::set_gyro_norm_mean(double gyro_norm_mean) {
    this->_gyro_norm_mean = gyro_norm_mean;
}
double Features::get_gyro_norm_mean() const {
    return this->_gyro_norm_mean;
}

void Features::set_gyro_norm_std(double gyro_norm_std) {
    this->_gyro_norm_std = gyro_norm_std;
}
double Features::get_gyro_norm_std() const {
    return this->_gyro_norm_std;
}


void Features::set_gyro_norm_kurt(double gyro_norm_kurt) {
    this->_gyro_norm_kurt = gyro_norm_kurt;
}
double Features::get_gyro_norm_kurt() const {
    return this->_gyro_norm_kurt;
}

void Features::set_gyro_norm_skew(double gyro_norm_skew) {
    this->_gyro_norm_skew = gyro_norm_skew;
}
double Features::get_gyro_norm_skew() const {
    return this->_gyro_norm_skew;
}

void Features::set_gyro_norm_aad(double gyro_norm_aad) {
    this->_gyro_norm_aad = gyro_norm_aad;
}
double Features::get_gyro_norm_aad() const {
    return this->_gyro_norm_aad;
}


void Features::set_mag_norm_mean(double mag_norm_mean) {
    this->_mag_norm_mean = mag_norm_mean;
}
double Features::get_mag_norm_mean() const {
    return this->_mag_norm_mean;
}

void Features::set_mag_norm_std(double mag_norm_std) {
    this->_mag_norm_std = mag_norm_std;
}
double Features::get_mag_norm_std() const {
    return this->_mag_norm_std;
}

void Features::set_mag_norm_kurt(double mag_norm_kurt) {
    this->_mag_norm_kurt = mag_norm_kurt;
}
double Features::get_mag_norm_kurt() const {
    return this->_mag_norm_kurt;
}

void Features::set_mag_norm_skew(double mag_norm_skew) {
    this->_mag_norm_skew = mag_norm_skew;
}
double Features::get_mag_norm_skew() const {
    return this->_mag_norm_skew;
}

void Features::set_mag_norm_aad(double mag_norm_aad) {
    this->_mag_norm_aad = mag_norm_aad;
}
double Features::get_mag_norm_aad() const {
    return this->_mag_norm_aad;
}


void Features::set_nb_step(int _nb_step) {
    this->nb_step = _nb_step;
}
int Features::get_nb_step() const {
    return this->nb_step;
}

void Features::set_acc_x_mean(double acc_x_mean) {
    this->_acc_x_mean = acc_x_mean;
}
double Features::get_acc_x_mean() const {
    return this->_acc_x_mean;
}

void Features::set_acc_y_mean(double acc_y_mean) {
    this->_acc_y_mean = acc_y_mean;
}
double Features::get_acc_y_mean() const {
    return this->_acc_y_mean;
}

void Features::set_acc_z_mean(double acc_z_mean) {
    this->_acc_z_mean = acc_z_mean;
}
double Features::get_acc_z_mean() const {
    return this->_acc_z_mean;
}

void Features::set_gyr_x_mean(double gyr_x_mean) {
    this->_gyr_x_mean = gyr_x_mean;
}
double Features::get_gyr_x_mean() const {
    return this->_gyr_x_mean;
}

void Features::set_gyr_y_mean(double gyr_y_mean) {
    this->_gyr_y_mean = gyr_y_mean;
}
double Features::get_gyr_y_mean() const {
    return this->_gyr_y_mean;
}

void Features::set_gyr_z_mean(double gyr_z_mean) {
    this->_gyr_z_mean = gyr_z_mean;
}
double Features::get_gyr_z_mean() const {
    return this->_gyr_z_mean;
}

void Features::set_mag_x_mean(double mag_x_mean) {
    this->_mag_x_mean = mag_x_mean;
}
double Features::get_mag_x_mean() const {
    return this->_mag_x_mean;
}

void Features::set_mag_y_mean(double mag_y_mean) {
    this->_mag_y_mean = mag_y_mean;
}
double Features::get_mag_y_mean() const {
    return this->_mag_y_mean;
}

void Features::set_mag_z_mean(double mag_z_mean) {
    this->_mag_z_mean = mag_z_mean;
}
double Features::get_mag_z_mean() const {
    return this->_mag_z_mean;
}

void Features::set_baro_mean(double baro_mean) {
    this->_baro_mean = baro_mean;
}
double Features::get_baro_mean() const {
    return this->_baro_mean;
}

void Features::set_acc_x_std(double acc_x_std) {
    this->_acc_x_std = acc_x_std;
}
double Features::get_acc_x_std() const {
    return this->_acc_x_std;
}

void Features::set_acc_y_std(double acc_y_std) {
    this->_acc_y_std = acc_y_std;
}
double Features::get_acc_y_std() const {
    return this->_acc_y_std;
}

void Features::set_acc_z_std(double acc_z_std) {
    this->_acc_z_std = acc_z_std;
}
double Features::get_acc_z_std() const {
    return this->_acc_z_std;
}

void Features::set_gyr_x_std(double gyr_x_std) {
    this->_gyr_x_std = gyr_x_std;
}
double Features::get_gyr_x_std() const {
    return this->_gyr_x_std;
}

void Features::set_gyr_y_std(double gyr_y_std) {
    this->_gyr_y_std = gyr_y_std;
}
double Features::get_gyr_y_std() const {
    return this->_gyr_y_std;
}

void Features::set_gyr_z_std(double gyr_z_std) {
    this->_gyr_z_std = gyr_z_std;
}
double Features::get_gyr_z_std() const {
    return this->_gyr_z_std;
}

void Features::set_mag_x_std(double mag_x_std) {
    this->_mag_x_std = mag_x_std;
}
double Features::get_mag_x_std() const {
    return this->_mag_x_std;
}

void Features::set_mag_y_std(double mag_y_std) {
    this->_mag_y_std = mag_y_std;
}
double Features::get_mag_y_std() const {
    return this->_mag_y_std;
}

void Features::set_mag_z_std(double mag_z_std) {
    this->_mag_z_std = mag_z_std;
}
double Features::get_mag_z_std() const {
    return this->_mag_z_std;
}

void Features::set_baro_std(double baro_std) {
    this->_baro_std = baro_std;
}
double Features::get_baro_std() const {
    return this->_baro_std;
}

void Features::set_acc_x_skew(double acc_x_skew) {
    this->_acc_x_skew = acc_x_skew;
}
double Features::get_acc_x_skew() const {
    return this->_acc_x_skew;
}

void Features::set_acc_y_skew(double acc_y_skew) {
    this->_acc_y_skew = acc_y_skew;
}
double Features::get_acc_y_skew() const {
    return this->_acc_y_skew;
}

void Features::set_acc_z_skew(double acc_z_skew) {
    this->_acc_z_skew = acc_z_skew;
}
double Features::get_acc_z_skew() const {
    return this->_acc_z_skew;
}

void Features::set_gyr_x_skew(double gyr_x_skew) {
    this->_gyr_x_skew = gyr_x_skew;
}
double Features::get_gyr_x_skew() const {
    return this->_gyr_x_skew;
}

void Features::set_gyr_y_skew(double gyr_y_skew) {
    this->_gyr_y_skew = gyr_y_skew;
}
double Features::get_gyr_y_skew() const {
    return this->_gyr_y_skew;
}

void Features::set_gyr_z_skew(double gyr_z_skew) {
    this->_gyr_z_skew = gyr_z_skew;
}
double Features::get_gyr_z_skew() const {
    return this->_gyr_z_skew;
}

void Features::set_mag_x_skew(double mag_x_skew) {
    this->_mag_x_skew = mag_x_skew;
}
double Features::get_mag_x_skew() const {
    return this->_mag_x_skew;
}

void Features::set_mag_y_skew(double mag_y_skew) {
    this->_mag_y_skew = mag_y_skew;
}
double Features::get_mag_y_skew() const {
    return this->_mag_y_skew;
}

void Features::set_mag_z_skew(double mag_z_skew) {
    this->_mag_z_skew = mag_z_skew;
}
double Features::get_mag_z_skew() const {
    return this->_mag_z_skew;
}

void Features::set_baro_skew(double baro_skew) {
    this->_baro_skew = baro_skew;
}
double Features::get_baro_skew() const {
    return this->_baro_skew;
}

void Features::set_acc_x_kurt(double acc_x_kurt) {
    this->_acc_x_kurt = acc_x_kurt;
}
double Features::get_acc_x_kurt() const {
    return this->_acc_x_kurt;
}


void Features::set_acc_y_kurt(double acc_y_kurt) {
    this->_acc_y_kurt = acc_y_kurt;
}
double Features::get_acc_y_kurt() const {
    return this->_acc_y_kurt;
}

void Features::set_acc_z_kurt(double acc_z_kurt) {
    this->_acc_z_kurt = acc_z_kurt;
}
double Features::get_acc_z_kurt() const {
    return this->_acc_z_kurt;
}

void Features::set_gyr_x_kurt(double gyr_x_kurt) {
    this->_gyr_x_kurt = gyr_x_kurt;
}
double Features::get_gyr_x_kurt() const {
    return this->_gyr_x_kurt;
}

void Features::set_gyr_y_kurt(double gyr_y_kurt) {
    this->_gyr_y_kurt = gyr_y_kurt;
}
double Features::get_gyr_y_kurt() const {
    return this->_gyr_y_kurt;
}

void Features::set_gyr_z_kurt(double gyr_z_kurt) {
    this->_gyr_z_kurt = gyr_z_kurt;
}
double Features::get_gyr_z_kurt() const {
    return this->_gyr_z_kurt;
}

void Features::set_mag_x_kurt(double mag_x_kurt) {
    this->_mag_x_kurt = mag_x_kurt;
}
double Features::get_mag_x_kurt() const {
    return this->_mag_x_kurt;
}

void Features::set_mag_y_kurt(double mag_y_kurt) {
    this->_mag_y_kurt = mag_y_kurt;
}
double Features::get_mag_y_kurt() const {
    return this->_mag_y_kurt;
}

void Features::set_mag_z_kurt(double mag_z_kurt) {
    this->_mag_z_kurt = mag_z_kurt;
}
double Features::get_mag_z_kurt() const {
    return this->_mag_z_kurt;
}

void Features::set_baro_kurt(double baro_kurt) {
    this->_baro_kurt = baro_kurt;
}
double Features::get_baro_kurt() const {
    return this->_baro_kurt;
}

void Features::set_acc_x_aad(double acc_x_aad) {
    this->_acc_x_aad = acc_x_aad;
}
double Features::get_acc_x_aad() const {
    return this->_acc_x_aad;
}


void Features::set_acc_y_aad(double acc_y_aad) {
    this->_acc_y_aad = acc_y_aad;
}
double Features::get_acc_y_aad() const {
    return this->_acc_y_aad;
}

void Features::set_acc_z_aad(double acc_z_aad) {
    this->_acc_z_aad = acc_z_aad;
}
double Features::get_acc_z_aad() const {
    return this->_acc_z_aad;
}

void Features::set_gyr_x_aad(double gyr_x_aad) {
    this->_gyr_x_aad = gyr_x_aad;
}
double Features::get_gyr_x_aad() const {
    return this->_gyr_x_aad;
}

void Features::set_gyr_y_aad(double gyr_y_aad) {
    this->_gyr_y_aad = gyr_y_aad;
}
double Features::get_gyr_y_aad() const {
    return this->_gyr_y_aad;
}

void Features::set_gyr_z_aad(double gyr_z_aad) {
    this->_gyr_z_aad = gyr_z_aad;
}
double Features::get_gyr_z_aad() const {
    return this->_gyr_z_aad;
}

void Features::set_mag_x_aad(double mag_x_aad) {
    this->_mag_x_aad = mag_x_aad;
}
double Features::get_mag_x_aad() const {
    return this->_mag_x_aad;
}

void Features::set_mag_y_aad(double mag_y_aad) {
    this->_mag_y_aad = mag_y_aad;
}
double Features::get_mag_y_aad() const {
    return this->_mag_y_aad;
}

void Features::set_mag_z_aad(double mag_z_aad) {
    this->_mag_z_aad = mag_z_aad;
}
double Features::get_mag_z_aad() const {
    return this->_mag_z_aad;
}

void Features::set_baro_aad(double baro_aad) {
    this->_baro_aad = baro_aad;
}
double Features::get_baro_aad() const {
    return this->_baro_aad;
}


void Features::set_acc_x_arc(double acc_x_arc) {
    this->_acc_x_arc = acc_x_arc;
}
double Features::get_acc_x_arc() const {
    return this->_acc_x_arc;
}


void Features::set_gyr_x_arc(double gyr_x_arc) {
    this->_gyr_x_arc = gyr_x_arc;
}
double Features::get_gyr_x_arc() const {
    return this->_gyr_x_arc;
}


void Features::set_mag_x_arc(double mag_x_arc) {
    this->_mag_x_arc = mag_x_arc;
}
double Features::get_mag_x_arc() const {
    return this->_mag_x_arc;
}

