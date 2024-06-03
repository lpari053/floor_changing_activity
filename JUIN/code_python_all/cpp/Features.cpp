#include "Features.hpp"

// Constructors
Features::Features():

_acc_norm_aad(0.0),_acc_norm_first_peak_index(0.0),_acc_norm_first_peak_value(0.0),_acc_norm_kurt(0.0),
_acc_norm_mean(0.0),_acc_norm_second_peak_index(0.0),_acc_norm_second_peak_value(0.0),
_acc_norm_skew(0.0),_acc_norm_mad(0.0),_acc_norm_std(0.0),

/*
_acc_x_mean_first_half(0.0),_acc_x_mean_second_half(0.0),_acc_x_mean_difference(0.0),acc_x_mean_pente(0.0),acc_x_rms(0.0),
_acc_y_mean_first_half(0.0),_acc_y_mean_second_half(0.0),_acc_y_mean_difference(0.0),acc_y_mean_pente(0.0),acc_y_rms(0.0),
_acc_z_mean_first_half(0.0),_acc_z_mean_second_half(0.0),_acc_z_mean_difference(0.0),acc_z_mean_pente(0.0),acc_z_rms(0.0),
_acc_norm_mean_first_half(0.0),_acc_norm_mean_second_half(0.0),_acc_norm_mean_difference(0.0),acc_norm_mean_pente(0.0),acc_norm_rms(0.0),*/

_gyro_norm_aad(0.0),_gyro_norm_first_peak_index(0.0),_gyro_norm_first_peak_value(0.0),_gyro_norm_kurt(0.0),
_gyro_norm_mean(0.0),_gyro_norm_second_peak_index(0.0),_gyro_norm_second_peak_value(0.0),
_gyro_norm_skew(0.0),_gyro_norm_mad(0.0),_gyro_norm_std(0.0),

/*
_gyro_x_mean_first_half(0.0),_gyro_x_mean_second_half(0.0),_gyro_x_mean_difference(0.0),gyro_x_mean_pente(0.0),gyro_x_rms(0.0),
_gyro_y_mean_first_half(0.0),_gyro_y_mean_second_half(0.0),_gyro_y_mean_difference(0.0),gyro_y_mean_pente(0.0),gyro_y_rms(0.0),
_gyro_z_mean_first_half(0.0),_gyro_z_mean_second_half(0.0),_gyro_z_mean_difference(0.0),gyro_z_mean_pente(0.0),gyro_z_rms(0.0),
_gyro_norm_mean_first_half(0.0),_gyro_norm_mean_second_half(0.0),_gyro_norm_mean_difference(0.0),gyro_norm_mean_pente(0.0),gyro_norm_rms(0.0),
*/
_mag_norm_aad(0.0),_mag_norm_first_peak_index(0.0),_mag_norm_first_peak_value(0.0),_mag_norm_kurt(0.0),
_mag_norm_mean(0.0),_mag_norm_second_peak_index(0.0),_mag_norm_second_peak_value(0.0),
_mag_norm_skew(0.0),_mag_norm_mad(0.0),_mag_norm_std(0.0),

/*
_mag_x_mean_first_half(0.0),_mag_x_mean_second_half(0.0),_mag_x_mean_difference(0.0),mag_x_mean_pente(0.0),mag_x_rms(0.0),
_mag_y_mean_first_half(0.0),_mag_y_mean_second_half(0.0),_mag_y_mean_difference(0.0),mag_y_mean_pente(0.0),mag_y_rms(0.0),
_mag_z_mean_first_half(0.0),_mag_z_mean_second_half(0.0),_mag_z_mean_difference(0.0),mag_z_mean_pente(0.0),mag_z_rms(0.0),
_mag_norm_mean_first_half(0.0),_mag_norm_mean_second_half(0.0),_mag_norm_mean_difference(0.0),mag_norm_mean_pente(0.0),mag_norm_rms(0.0),
*/
_acc_x_aad(0.0),_acc_x_arc(0.0),_acc_x_first_peak_index(0.0),_acc_x_first_peak_value(0.0),_acc_x_kurt(0.0),
_acc_x_mean(0.0),_acc_x_pc(0.0),_acc_x_second_peak_index(0.0),_acc_x_second_peak_value(0.0),
_acc_x_skew(0.0),_acc_x_mad(0.0),_acc_x_std(0.0),

_acc_y_aad(0.0),_acc_y_arc(0.0),_acc_y_first_peak_index(0.0),_acc_y_first_peak_value(0.0),_acc_y_kurt(0.0),
_acc_y_mean(0.0),_acc_y_pc(0.0),_acc_y_second_peak_index(0.0),_acc_y_second_peak_value(0.0),
_acc_y_skew(0.0),_acc_y_mad(0.0),_acc_y_std(0.0),


_acc_z_aad(0.0),_acc_z_arc(0.0),_acc_z_first_peak_index(0.0),_acc_z_first_peak_value(0.0),_acc_z_kurt(0.0),
_acc_z_mean(0.0),_acc_z_pc(0.0),_acc_z_second_peak_index(0.0),_acc_z_second_peak_value(0.0),
_acc_z_skew(0.0),_acc_z_mad(0.0),_acc_z_std(0.0),

_gyr_x_aad(0.0),_gyr_x_arc(0.0),_gyr_x_first_peak_index(0.0),_gyr_x_first_peak_value(0.0),_gyr_x_kurt(0.0),
_gyr_x_mean(0.0),_gyr_x_pc(0.0),_gyr_x_second_peak_index(0.0),_gyr_x_second_peak_value(0.0),
_gyr_x_skew(0.0),_gyr_x_mad(0.0),_gyr_x_std(0.0),

_gyr_y_aad(0.0),_gyr_y_arc(0.0),_gyr_y_first_peak_index(0.0),_gyr_y_first_peak_value(0.0),_gyr_y_kurt(0.0),
_gyr_y_mean(0.0),_gyr_y_pc(0.0),_gyr_y_second_peak_index(0.0),_gyr_y_second_peak_value(0.0),
_gyr_y_skew(0.0),_gyr_y_mad(0.0),_gyr_y_std(0.0),


_gyr_z_aad(0.0),_gyr_z_arc(0.0),_gyr_z_first_peak_index(0.0),_gyr_z_first_peak_value(0.0),_gyr_z_kurt(0.0),
_gyr_z_mean(0.0),_gyr_z_pc(0.0),_gyr_z_second_peak_index(0.0),_gyr_z_second_peak_value(0.0),
_gyr_z_skew(0.0),_gyr_z_mad(0.0),_gyr_z_std(0.0),

_mag_x_aad(0.0),_mag_x_arc(0.0),_mag_x_first_peak_index(0.0),_mag_x_first_peak_value(0.0),_mag_x_kurt(0.0),
_mag_x_mean(0.0),_mag_x_pc(0.0),_mag_x_second_peak_index(0.0),_mag_x_second_peak_value(0.0),
_mag_x_skew(0.0),_mag_x_mad(0.0),_mag_x_std(0.0),

_mag_y_aad(0.0),_mag_y_arc(0.0),_mag_y_first_peak_index(0.0),_mag_y_first_peak_value(0.0),_mag_y_kurt(0.0),
_mag_y_mean(0.0),_mag_y_pc(0.0),_mag_y_second_peak_index(0.0),_mag_y_second_peak_value(0.0),
_mag_y_skew(0.0),_mag_y_mad(0.0),_mag_y_std(0.0),


_mag_z_aad(0.0),_mag_z_arc(0.0),_mag_z_first_peak_index(0.0),_mag_z_first_peak_value(0.0),_mag_z_kurt(0.0),
_mag_z_mean(0.0),_mag_z_pc(0.0),_mag_z_second_peak_index(0.0),_mag_z_second_peak_value(0.0),
_mag_z_skew(0.0),_mag_z_mad(0.0),_mag_z_std(0.0),

_baro_aad(0.0),_baro_arc(0.0),_baro_first_peak_index(0.0),_baro_first_peak_value(0.0),_baro_kurt(0.0),
_baro_mean(0.0),_baro_pc(0.0),_baro_second_peak_index(0.0),_baro_second_peak_value(0.0),
_baro_skew(0.0),_baro_mad(0.0),_baro_std(0.0) ,

nb_step(0){}

Features::~Features() {}


/*

void Features::set_acc_norm_mean_first_half(double acc_norm_mean_first_half) {
    this->_acc_norm_mean_first_half = acc_norm_mean_first_half;
}
double Features::get_acc_norm_mean_first_half() const {
    return this->_acc_norm_mean_first_half;
}

void Features::set_acc_norm_mean_second_half(double acc_norm_mean_second_half) {
    this->_acc_norm_mean_second_half = acc_norm_mean_second_half;
}
double Features::get_acc_norm_mean_second_half() const {
    return this->_acc_norm_mean_second_half;
}


void Features::set_acc_norm_difference_mean(double acc_norm_difference_mean) {
    this->_acc_norm_difference_mean = acc_norm_difference_mean;
}
double Features::get_acc_norm_difference_mean() const {
    return this->_acc_norm_difference_mean;
}



void Features::set_acc_norm_rms(double acc_norm_rms) {
    this->_acc_norm_rms = acc_norm_rms;
}
double Features::get_acc_norm_rms() const {
    return this->_acc_norm_rms;
}


void Features::set_acc_norm_slope(double acc_norm_slope) {
    this->_acc_norm_slope = acc_norm_slope;
}
double Features::get_acc_norm_slope() const {
    return this->_acc_norm_slope;
}

void Features::set_acc_x_mean_first_half(double acc_x_mean_first_half) {
    this->_acc_x_mean_first_half = acc_x_mean_first_half;
}
double Features::get_acc_x_mean_first_half() const {
    return this->_acc_x_mean_first_half;
}

void Features::set_acc_x_mean_second_half(double acc_x_mean_second_half) {
    this->_acc_x_mean_second_half = acc_x_mean_second_half;
}
double Features::get_acc_x_mean_second_half() const {
    return this->_acc_x_mean_second_half;
}


void Features::set_acc_x_difference_mean(double acc_x_difference_mean) {
    this->_acc_x_difference_mean = acc_x_difference_mean;
}
double Features::get_acc_x_difference_mean() const {
    return this->_acc_x_difference_mean;
}



void Features::set_acc_x_rms(double acc_x_rms) {
    this->_acc_x_rms = acc_x_rms;
}
double Features::get_acc_x_rms() const {
    return this->_acc_x_rms;
}


void Features::set_acc_x_slope(double acc_x_slope) {
    this->_acc_x_slope = acc_x_slope;
}
double Features::get_acc_x_slope() const {
    return this->_acc_x_slope;
}


void Features::set_acc_y_mean_first_half(double acc_y_mean_first_half) {
    this->_acc_y_mean_first_half = acc_y_mean_first_half;
}
double Features::get_acc_y_mean_first_half() const {
    return this->_acc_y_mean_first_half;
}

void Features::set_acc_y_mean_second_half(double acc_y_mean_second_half) {
    this->_acc_y_mean_second_half = acc_y_mean_second_half;
}
double Features::get_acc_y_mean_second_half() const {
    return this->_acc_y_mean_second_half;
}


void Features::set_acc_y_difference_mean(double acc_y_difference_mean) {
    this->_acc_y_difference_mean = acc_y_difference_mean;
}
double Features::get_acc_y_difference_mean() const {
    return this->_acc_y_difference_mean;
}



void Features::set_acc_y_rms(double acc_y_rms) {
    this->_acc_y_rms = acc_y_rms;
}
double Features::get_acc_y_rms() const {
    return this->_acc_y_rms;
}


void Features::set_acc_y_slope(double acc_y_slope) {
    this->_acc_y_slope = acc_y_slope;
}
double Features::get_acc_y_slope() const {
    return this->_acc_y_slope;
}

void Features::set_acc_z_mean_first_half(double acc_z_mean_first_half) {
    this->_acc_z_mean_first_half = acc_z_mean_first_half;
}
double Features::get_acc_z_mean_first_half() const {
    return this->_acc_z_mean_first_half;
}

void Features::set_acc_z_mean_second_half(double acc_z_mean_second_half) {
    this->_acc_z_mean_second_half = acc_z_mean_second_half;
}
double Features::get_acc_z_mean_second_half() const {
    return this->_acc_z_mean_second_half;
}


void Features::set_acc_z_difference_mean(double acc_z_difference_mean) {
    this->_acc_z_difference_mean = acc_z_difference_mean;
}
double Features::get_acc_z_difference_mean() const {
    return this->_acc_z_difference_mean;
}



void Features::set_acc_z_rms(double acc_z_rms) {
    this->_acc_z_rms = acc_z_rms;
}
double Features::get_acc_z_rms() const {
    return this->_acc_z_rms;
}


void Features::set_acc_z_slope(double acc_z_slope) {
    this->_acc_z_slope = acc_z_slope;
}
double Features::get_acc_z_slope() const {
    return this->_acc_z_slope;
}

void Features::set_gyro_norm_mean_first_half(double gyro_norm_mean_first_half) {
    this->_gyro_norm_mean_first_half = gyro_norm_mean_first_half;
}
double Features::get_gyro_norm_mean_first_half() const {
    return this->_gyro_norm_mean_first_half;
}

void Features::set_gyro_norm_mean_second_half(double gyro_norm_mean_second_half) {
    this->_gyro_norm_mean_second_half = gyro_norm_mean_second_half;
}
double Features::get_gyro_norm_mean_second_half() const {
    return this->_gyro_norm_mean_second_half;
}


void Features::set_gyro_norm_difference_mean(double gyro_norm_difference_mean) {
    this->_gyro_norm_difference_mean = gyro_norm_difference_mean;
}
double Features::get_gyro_norm_difference_mean() const {
    return this->_gyro_norm_difference_mean;
}



void Features::set_gyro_norm_rms(double gyro_norm_rms) {
    this->_gyro_norm_rms = gyro_norm_rms;
}
double Features::get_gyro_norm_rms() const {
    return this->_gyro_norm_rms;
}


void Features::set_gyro_norm_slope(double gyro_norm_slope) {
    this->_gyro_norm_slope = gyro_norm_slope;
}
double Features::get_gyro_norm_slope() const {
    return this->_gyro_norm_slope;
}

void Features::set_gyro_x_mean_first_half(double gyro_x_mean_first_half) {
    this->_gyro_x_mean_first_half = gyro_x_mean_first_half;
}
double Features::get_gyro_x_mean_first_half() const {
    return this->_gyro_x_mean_first_half;
}

void Features::set_gyro_x_mean_second_half(double gyro_x_mean_second_half) {
    this->_gyro_x_mean_second_half = gyro_x_mean_second_half;
}
double Features::get_gyro_x_mean_second_half() const {
    return this->_gyro_x_mean_second_half;
}


void Features::set_gyro_x_difference_mean(double gyro_x_difference_mean) {
    this->_gyro_x_difference_mean = gyro_x_difference_mean;
}
double Features::get_gyro_x_difference_mean() const {
    return this->_gyro_x_difference_mean;
}



void Features::set_gyro_x_rms(double gyro_x_rms) {
    this->_gyro_x_rms = gyro_x_rms;
}
double Features::get_gyro_x_rms() const {
    return this->_gyro_x_rms;
}


void Features::set_gyro_x_slope(double gyro_x_slope) {
    this->_gyro_x_slope = gyro_x_slope;
}
double Features::get_gyro_x_slope() const {
    return this->_gyro_x_slope;
}


void Features::set_gyro_y_mean_first_half(double gyro_y_mean_first_half) {
    this->_gyro_y_mean_first_half = gyro_y_mean_first_half;
}
double Features::get_gyro_y_mean_first_half() const {
    return this->_gyro_y_mean_first_half;
}

void Features::set_gyro_y_mean_second_half(double gyro_y_mean_second_half) {
    this->_gyro_y_mean_second_half = gyro_y_mean_second_half;
}
double Features::get_gyro_y_mean_second_half() const {
    return this->_gyro_y_mean_second_half;
}


void Features::set_gyro_y_difference_mean(double gyro_y_difference_mean) {
    this->_gyro_y_difference_mean = gyro_y_difference_mean;
}
double Features::get_gyro_y_difference_mean() const {
    return this->_gyro_y_difference_mean;
}



void Features::set_gyro_y_rms(double gyro_y_rms) {
    this->_gyro_y_rms = gyro_y_rms;
}
double Features::get_gyro_y_rms() const {
    return this->_gyro_y_rms;
}


void Features::set_gyro_y_slope(double gyro_y_slope) {
    this->_gyro_y_slope = gyro_y_slope;
}
double Features::get_gyro_y_slope() const {
    return this->_gyro_y_slope;
}

void Features::set_gyro_z_mean_first_half(double gyro_z_mean_first_half) {
    this->_gyro_z_mean_first_half = gyro_z_mean_first_half;
}
double Features::get_gyro_z_mean_first_half() const {
    return this->_gyro_z_mean_first_half;
}

void Features::set_gyro_z_mean_second_half(double gyro_z_mean_second_half) {
    this->_gyro_z_mean_second_half = gyro_z_mean_second_half;
}
double Features::get_gyro_z_mean_second_half() const {
    return this->_gyro_z_mean_second_half;
}


void Features::set_gyro_z_difference_mean(double gyro_z_difference_mean) {
    this->_gyro_z_difference_mean = gyro_z_difference_mean;
}
double Features::get_gyro_z_difference_mean() const {
    return this->_gyro_z_difference_mean;
}



void Features::set_gyro_z_rms(double gyro_z_rms) {
    this->_gyro_z_rms = gyro_z_rms;
}
double Features::get_gyro_z_rms() const {
    return this->_gyro_z_rms;
}


void Features::set_gyro_z_slope(double gyro_z_slope) {
    this->_gyro_z_slope = gyro_z_slope;
}
double Features::get_gyro_z_slope() const {
    return this->_gyro_z_slope;
}


void Features::set_mag_norm_mean_first_half(double mag_norm_mean_first_half) {
    this->_mag_norm_mean_first_half = mag_norm_mean_first_half;
}
double Features::get_mag_norm_mean_first_half() const {
    return this->_mag_norm_mean_first_half;
}

void Features::set_mag_norm_mean_second_half(double mag_norm_mean_second_half) {
    this->_mag_norm_mean_second_half = mag_norm_mean_second_half;
}
double Features::get_mag_norm_mean_second_half() const {
    return this->_mag_norm_mean_second_half;
}


void Features::set_mag_norm_difference_mean(double mag_norm_difference_mean) {
    this->_mag_norm_difference_mean = mag_norm_difference_mean;
}
double Features::get_mag_norm_difference_mean() const {
    return this->_mag_norm_difference_mean;
}



void Features::set_mag_norm_rms(double mag_norm_rms) {
    this->_mag_norm_rms = mag_norm_rms;
}
double Features::get_mag_norm_rms() const {
    return this->_mag_norm_rms;
}


void Features::set_mag_norm_slope(double mag_norm_slope) {
    this->_mag_norm_slope = mag_norm_slope;
}
double Features::get_mag_norm_slope() const {
    return this->_mag_norm_slope;
}

void Features::set_mag_x_mean_first_half(double mag_x_mean_first_half) {
    this->_mag_x_mean_first_half = mag_x_mean_first_half;
}
double Features::get_mag_x_mean_first_half() const {
    return this->_mag_x_mean_first_half;
}

void Features::set_mag_x_mean_second_half(double mag_x_mean_second_half) {
    this->_mag_x_mean_second_half = mag_x_mean_second_half;
}
double Features::get_mag_x_mean_second_half() const {
    return this->_mag_x_mean_second_half;
}


void Features::set_mag_x_difference_mean(double mag_x_difference_mean) {
    this->_mag_x_difference_mean = mag_x_difference_mean;
}
double Features::get_mag_x_difference_mean() const {
    return this->_mag_x_difference_mean;
}



void Features::set_mag_x_rms(double mag_x_rms) {
    this->_mag_x_rms = mag_x_rms;
}
double Features::get_mag_x_rms() const {
    return this->_mag_x_rms;
}


void Features::set_mag_x_slope(double mag_x_slope) {
    this->_mag_x_slope = mag_x_slope;
}
double Features::get_mag_x_slope() const {
    return this->_mag_x_slope;
}


void Features::set_mag_y_mean_first_half(double mag_y_mean_first_half) {
    this->_mag_y_mean_first_half = mag_y_mean_first_half;
}
double Features::get_mag_y_mean_first_half() const {
    return this->_mag_y_mean_first_half;
}

void Features::set_mag_y_mean_second_half(double mag_y_mean_second_half) {
    this->_mag_y_mean_second_half = mag_y_mean_second_half;
}
double Features::get_mag_y_mean_second_half() const {
    return this->_mag_y_mean_second_half;
}


void Features::set_mag_y_difference_mean(double mag_y_difference_mean) {
    this->_mag_y_difference_mean = mag_y_difference_mean;
}
double Features::get_mag_y_difference_mean() const {
    return this->_mag_y_difference_mean;
}



void Features::set_mag_y_rms(double mag_y_rms) {
    this->_mag_y_rms = mag_y_rms;
}
double Features::get_mag_y_rms() const {
    return this->_mag_y_rms;
}


void Features::set_mag_y_slope(double mag_y_slope) {
    this->_mag_y_slope = mag_y_slope;
}
double Features::get_mag_y_slope() const {
    return this->_mag_y_slope;
}

void Features::set_mag_z_mean_first_half(double mag_z_mean_first_half) {
    this->_mag_z_mean_first_half = mag_z_mean_first_half;
}
double Features::get_mag_z_mean_first_half() const {
    return this->_mag_z_mean_first_half;
}

void Features::set_mag_z_mean_second_half(double mag_z_mean_second_half) {
    this->_mag_z_mean_second_half = mag_z_mean_second_half;
}
double Features::get_mag_z_mean_second_half() const {
    return this->_mag_z_mean_second_half;
}


void Features::set_mag_z_difference_mean(double mag_z_difference_mean) {
    this->_mag_z_difference_mean = mag_z_difference_mean;
}
double Features::get_mag_z_difference_mean() const {
    return this->_mag_z_difference_mean;
}



void Features::set_mag_z_rms(double mag_z_rms) {
    this->_mag_z_rms = mag_z_rms;
}
double Features::get_mag_z_rms() const {
    return this->_mag_z_rms;
}


void Features::set_mag_z_slope(double mag_z_slope) {
    this->_mag_z_slope = mag_z_slope;
}
double Features::get_mag_z_slope() const {
    return this->_mag_z_slope;
}

*/

/**
 * @brief Set_acc_norm_first_peak_index
 * @param param1 double acc_norm_first_peak_index.
 */
void Features::set_acc_norm_first_peak_index(double acc_norm_first_peak_index) {
    this->_acc_norm_first_peak_index = acc_norm_first_peak_index;
}

/**
 * @brief Get_acc_norm_first_peak_index
 * @return _acc_norm_first_peak_index.
 */

double Features::get_acc_norm_first_peak_index() const {
    return this->_acc_norm_first_peak_index;
}


/**
 * @brief Set_acc_norm_first_peak_value
 * @param param1 double acc_norm_first_peak_value.
 */
void Features::set_acc_norm_first_peak_value(double acc_norm_first_peak_value) {
    this->_acc_norm_first_peak_value= acc_norm_first_peak_value;
}

/**
 * @brief Get_acc_norm_first_peak_value
 * @return _acc_norm_first_peak_value.
 */
double Features::get_acc_norm_first_peak_value() const {
    return this->_acc_norm_first_peak_value;
}
/**
 * @brief Set_acc_norm_second_peak_index
 * @param param1 double acc_norm_second_peak_index.
 */
void Features::set_acc_norm_second_peak_index(double acc_norm_second_peak_index) {
    this->_acc_norm_second_peak_index = acc_norm_second_peak_index;
}
/**
 * @brief Get_acc_norm_second_peak_index
 * @return _acc_norm__second_peak_index
 */
double Features::get_acc_norm_second_peak_index() const {
    return this->_acc_norm_second_peak_index;
}
/**
 * @brief Set_acc_norm_second_peak_value
 * @param param1 double acc_norm_second_peak_value.
 */
void Features::set_acc_norm_second_peak_value(double acc_norm_second_peak_value) {
    this->_acc_norm_second_peak_value= acc_norm_second_peak_value;
}
/**
 * @brief Get_acc_norm_second_peak_value
 * @return _acc_norm__second_peak_value
 */
double Features::get_acc_norm_second_peak_value() const {
    return this->_acc_norm_second_peak_value;
}

/**
 * @brief Set_gyro_norm_first_peak_index
 * @param param1 double gyro_norm_first_peak_index.
 */
void Features::set_gyro_norm_first_peak_index(double gyro_norm_first_peak_index) {
    this->_gyro_norm_first_peak_index = gyro_norm_first_peak_index;
}

/**
 * @brief Get_gyro_norm_first_peak_index
 * @return _gyro_norm_first_peak_index.
 */

double Features::get_gyro_norm_first_peak_index() const {
    return this->_gyro_norm_first_peak_index;
}


/**
 * @brief Set_gyro_norm_first_peak_value
 * @param param1 double gyro_norm_first_peak_value.
 */
void Features::set_gyro_norm_first_peak_value(double gyro_norm_first_peak_value) {
    this->_gyro_norm_first_peak_value= gyro_norm_first_peak_value;
}

/**
 * @brief Get_gyro_norm_first_peak_value
 * @return _gyro_norm_first_peak_value.
 */
double Features::get_gyro_norm_first_peak_value() const {
    return this->_gyro_norm_first_peak_value;
}
/**
 * @brief Set_gyro_norm_second_peak_index
 * @param param1 double gyro_norm_second_peak_index.
 */
void Features::set_gyro_norm_second_peak_index(double gyro_norm_second_peak_index) {
    this->_gyro_norm_second_peak_index = gyro_norm_second_peak_index;
}
/**
 * @brief Get_gyro_norm_second_peak_index
 * @return _gyro_norm__second_peak_index
 */
double Features::get_gyro_norm_second_peak_index() const {
    return this->_gyro_norm_second_peak_index;
}
/**
 * @brief Set_gyro_norm_second_peak_value
 * @param param1 double gyro_norm_second_peak_value.
 */
void Features::set_gyro_norm_second_peak_value(double gyro_norm_second_peak_value) {
    this->_gyro_norm_second_peak_value= gyro_norm_second_peak_value;
}
/**
 * @brief Get_gyro_norm_second_peak_value
 * @return _gyro_norm__second_peak_value
 */
double Features::get_gyro_norm_second_peak_value() const {
    return this->_gyro_norm_second_peak_value;
}

/**
 * @brief Set_mag_norm_first_peak_index
 * @param param1 double mag_norm_first_peak_index.
 */
void Features::set_mag_norm_first_peak_index(double mag_norm_first_peak_index) {
    this->_mag_norm_first_peak_index = mag_norm_first_peak_index;
}

/**
 * @brief Get_mag_norm_first_peak_index
 * @return _mag_norm_first_peak_index.
 */

double Features::get_mag_norm_first_peak_index() const {
    return this->_mag_norm_first_peak_index;
}


/**
 * @brief Set_mag_norm_first_peak_value
 * @param param1 double mag_norm_first_peak_value.
 */
void Features::set_mag_norm_first_peak_value(double mag_norm_first_peak_value) {
    this->_mag_norm_first_peak_value= mag_norm_first_peak_value;
}

/**
 * @brief Get_mag_norm_first_peak_value
 * @return _mag_norm_first_peak_value.
 */
double Features::get_mag_norm_first_peak_value() const {
    return this->_mag_norm_first_peak_value;
}
/**
 * @brief Set_mag_norm_second_peak_index
 * @param param1 double mag_norm_second_peak_index.
 */
void Features::set_mag_norm_second_peak_index(double mag_norm_second_peak_index) {
    this->_mag_norm_second_peak_index = mag_norm_second_peak_index;
}
/**
 * @brief Get_mag_norm_second_peak_index
 * @return _mag_norm__second_peak_index
 */
double Features::get_mag_norm_second_peak_index() const {
    return this->_mag_norm_second_peak_index;
}
/**
 * @brief Set_mag_norm_second_peak_value
 * @param param1 double mag_norm_second_peak_value.
 */
void Features::set_mag_norm_second_peak_value(double mag_norm_second_peak_value) {
    this->_mag_norm_second_peak_value= mag_norm_second_peak_value;
}
/**
 * @brief Get_mag_norm_second_peak_value
 * @return _mag_norm__second_peak_value
 */
double Features::get_mag_norm_second_peak_value() const {
    return this->_mag_norm_second_peak_value;
}




/**
 * @brief Set_acc_norm_mean
 * @param param1 acc_norm_mean
 */
void Features::set_acc_norm_mean(double acc_norm_mean) {
    this->_acc_norm_mean = acc_norm_mean;
}
/**
 * @brief Get_acc_norm_mean
 * @return _acc_norm_mean
 */
double Features::get_acc_norm_mean() const {
    return this->_acc_norm_mean;
}
/**
 * @brief Set_acc_norm_std
 * @param param1 acc_norm_std
 */
void Features::set_acc_norm_std(double acc_norm_std) {
    this->_acc_norm_std = acc_norm_std;
}
/**
 * @brief Get_acc_norm_std
 * @return _acc_norm_std
 */
double Features::get_acc_norm_std() const {
    return this->_acc_norm_std;
}
/**
 * @brief Set_acc_norm_mad
 * @param param1 acc_norm_mad
 */
void Features::set_acc_norm_mad(double acc_norm_mad) {
    this->_acc_norm_mad = acc_norm_mad;
}
/**
 * @brief Get_acc_norm_mad
 * @return _acc_norm_mad
 */
double Features::get_acc_norm_mad() const {
    return this->_acc_norm_mad;
}
/**
 * @brief Set_acc_norm_kurt
 * @param param1 acc_norm_kurt
 */
void Features::set_acc_norm_kurt(double acc_norm_kurt) {
    this->_acc_norm_kurt = acc_norm_kurt;
}
/**
 * @brief Get_acc_norm_kurt
 * @return _acc_norm_kurt
 */
double Features::get_acc_norm_kurt() const {
    return this->_acc_norm_kurt;
}
/**
 * @brief Set_acc_norm_skew
 * @param param1 acc_norm_skew
 */
void Features::set_acc_norm_skew(double acc_norm_skew) {
    this->_acc_norm_skew = acc_norm_skew;
}
/**
 * @brief Get_acc_norm_skew
 * @return _acc_norm_skew
 */
double Features::get_acc_norm_skew() const {
    return this->_acc_norm_skew;
}
/**
 * @brief Set_acc_norm_aad
 * @param param1 acc_norm_aad
 */
void Features::set_acc_norm_aad(double acc_norm_aad) {
    this->_acc_norm_aad = acc_norm_aad;
}
/**
 * @brief Get_acc_norm_aad
 * @return _acc_norm_aad
 */
double Features::get_acc_norm_aad() const {
    return this->_acc_norm_aad;
}

/**
 * @brief Set_gyro_norm_mean
 * @param param1 gyro_norm_mean
 */
void Features::set_gyro_norm_mean(double gyro_norm_mean) {
    this->_gyro_norm_mean = gyro_norm_mean;
}
/**
 * @brief Get_gyro_norm_mean
 * @return _gyro_norm_mean
 */
double Features::get_gyro_norm_mean() const {
    return this->_gyro_norm_mean;
}
/**
 * @brief Set_gyro_norm_std
 * @param param1 gyro_norm_std
 */
void Features::set_gyro_norm_std(double gyro_norm_std) {
    this->_gyro_norm_std = gyro_norm_std;
}
/**
 * @brief Get_gyro_norm_std
 * @return _gyro_norm_std
 */
double Features::get_gyro_norm_std() const {
    return this->_gyro_norm_std;
}
/**
 * @brief Set_gyro_norm_mad
 * @param param1 gyro_norm_mad
 */
void Features::set_gyro_norm_mad(double gyro_norm_mad) {
    this->_gyro_norm_mad = gyro_norm_mad;
}
/**
 * @brief Get_gyro_norm_mad
 * @return _gyro_norm_mad
 */
double Features::get_gyro_norm_mad() const {
    return this->_gyro_norm_mad;
}
/**
 * @brief Set_gyro_norm_kurt
 * @param param1 gyro_norm_kurt
 */
void Features::set_gyro_norm_kurt(double gyro_norm_kurt) {
    this->_gyro_norm_kurt = gyro_norm_kurt;
}
/**
 * @brief Get_gyro_norm_kurt
 * @return _gyro_norm_kurt
 */
double Features::get_gyro_norm_kurt() const {
    return this->_gyro_norm_kurt;
}
/**
 * @brief Set_gyro_norm_skew
 * @param param1 gyro_norm_skew
 */
void Features::set_gyro_norm_skew(double gyro_norm_skew) {
    this->_gyro_norm_skew = gyro_norm_skew;
}
/**
 * @brief Get_gyro_norm_skew
 * @return _gyro_norm_skew
 */
double Features::get_gyro_norm_skew() const {
    return this->_gyro_norm_skew;
}
/**
 * @brief Set_gyro_norm_aad
 * @param param1 gyro_norm_aad
 */
void Features::set_gyro_norm_aad(double gyro_norm_aad) {
    this->_gyro_norm_aad = gyro_norm_aad;
}
/**
 * @brief Get_gyro_norm_aad
 * @return _gyro_norm_aad
 */
double Features::get_gyro_norm_aad() const {
    return this->_gyro_norm_aad;
}


/**
 * @brief Set_mag_norm_mean
 * @param param1 mag_norm_mean
 */
void Features::set_mag_norm_mean(double mag_norm_mean) {
    this->_mag_norm_mean = mag_norm_mean;
}
/**
 * @brief Get_mag_norm_mean
 * @return _mag_norm_mean
 */
double Features::get_mag_norm_mean() const {
    return this->_mag_norm_mean;
}
/**
 * @brief Set_mag_norm_std
 * @param param1 mag_norm_std
 */
void Features::set_mag_norm_std(double mag_norm_std) {
    this->_mag_norm_std = mag_norm_std;
}
/**
 * @brief Get_mag_norm_std
 * @return _mag_norm_std
 */
double Features::get_mag_norm_std() const {
    return this->_mag_norm_std;
}
/**
 * @brief Set_mag_norm_mad
 * @param param1 mag_norm_mad
 */
void Features::set_mag_norm_mad(double mag_norm_mad) {
    this->_mag_norm_mad = mag_norm_mad;
}
/**
 * @brief Get_mag_norm_mad
 * @return _mag_norm_mad
 */
double Features::get_mag_norm_mad() const {
    return this->_mag_norm_mad;
}
/**
 * @brief Set_mag_norm_kurt
 * @param param1 mag_norm_kurt
 */
void Features::set_mag_norm_kurt(double mag_norm_kurt) {
    this->_mag_norm_kurt = mag_norm_kurt;
}
/**
 * @brief Get_mag_norm_kurt
 * @return _mag_norm_kurt
 */
double Features::get_mag_norm_kurt() const {
    return this->_mag_norm_kurt;
}
/**
 * @brief Set_mag_norm_skew
 * @param param1 mag_norm_skew
 */
void Features::set_mag_norm_skew(double mag_norm_skew) {
    this->_mag_norm_skew = mag_norm_skew;
}
/**
 * @brief Get_mag_norm_skew
 * @return _mag_norm_skew
 */
double Features::get_mag_norm_skew() const {
    return this->_mag_norm_skew;
}
/**
 * @brief Set_mag_norm_aad
 * @param param1 mag_norm_aad
 */
void Features::set_mag_norm_aad(double mag_norm_aad) {
    this->_mag_norm_aad = mag_norm_aad;
}
/**
 * @brief Get_mag_norm_aad
 * @return _mag_norm_aad
 */
double Features::get_mag_norm_aad() const {
    return this->_mag_norm_aad;
}



/**
 * @brief Set_nb_step
 * @param param1 _nb_step
 */
void Features::set_nb_step(int _nb_step) {
    this->nb_step = _nb_step;
}
/**
 * @brief Get_nb_step
 * @return nb_step
 */
int Features::get_nb_step() const {
    return this->nb_step;
}


/**
 * @brief Set_acc_x_mean
 * @param param1 _acc_x_mean
 */
void Features::set_acc_x_mean(double acc_x_mean) {
    this->_acc_x_mean = acc_x_mean;
}
/**
 * @brief Get_acc_x_mean
 * @return _acc_x_mean
 */
double Features::get_acc_x_mean() const {
    return this->_acc_x_mean;
}

/**
 * @brief Set_acc_y_mean
 * @param param1 _acc_y_mean
 */
void Features::set_acc_y_mean(double acc_y_mean) {
    this->_acc_y_mean = acc_y_mean;
}
/**
 * @brief Get_acc_y_mean
 * @return _acc_y_mean
 */
double Features::get_acc_y_mean() const {
    return this->_acc_y_mean;
}

/**
 * @brief Set_acc_z_mean
 * @param param1 _acc_z_mean
 */
void Features::set_acc_z_mean(double acc_z_mean) {
    this->_acc_z_mean = acc_z_mean;
}
/**
 * @brief Get_acc_z_mean
 * @return _acc_z_mean
 */
double Features::get_acc_z_mean() const {
    return this->_acc_z_mean;
}

/**
 * @brief Set_gyr_x_mean
 * @param param1 _gyr_x_mean
 */
void Features::set_gyr_x_mean(double gyr_x_mean) {
    this->_gyr_x_mean = gyr_x_mean;
}
/**
 * @brief Get_gyr_x_mean
 * @return _gyr_x_mean
 */
double Features::get_gyr_x_mean() const {
    return this->_gyr_x_mean;
}

/**
 * @brief Set_gyr_y_mean
 * @param param1 _gyr_y_mean
 */
void Features::set_gyr_y_mean(double gyr_y_mean) {
    this->_gyr_y_mean = gyr_y_mean;
}
/**
 * @brief Get_gyr_y_mean
 * @return _gyr_y_mean
 */
double Features::get_gyr_y_mean() const {
    return this->_gyr_y_mean;
}

/**
 * @brief Set_gyr_z_mean
 * @param param1 _gyr_z_mean
 */
void Features::set_gyr_z_mean(double gyr_z_mean) {
    this->_gyr_z_mean = gyr_z_mean;
}
/**
 * @brief Get_gyr_z_mean
 * @return _gyr_z_mean
 */
double Features::get_gyr_z_mean() const {
    return this->_gyr_z_mean;
}



/**
 * @brief Set_mag_x_mean
 * @param param1 _mag_x_mean
 */
void Features::set_mag_x_mean(double mag_x_mean) {
    this->_mag_x_mean = mag_x_mean;
}
/**
 * @brief Get_mag_x_mean
 * @return _mag_x_mean
 */
double Features::get_mag_x_mean() const {
    return this->_mag_x_mean;
}

/**
 * @brief Set_mag_y_mean
 * @param param1 _mag_y_mean
 */
void Features::set_mag_y_mean(double mag_y_mean) {
    this->_mag_y_mean = mag_y_mean;
}
/**
 * @brief Get_mag_y_mean
 * @return _mag_y_mean
 */
double Features::get_mag_y_mean() const {
    return this->_mag_y_mean;
}

/**
 * @brief Set_mag_z_mean
 * @param param1 _mag_z_mean
 */
void Features::set_mag_z_mean(double mag_z_mean) {
    this->_mag_z_mean = mag_z_mean;
}
/**
 * @brief Get_mag_z_mean
 * @return _mag_z_mean
 */
double Features::get_mag_z_mean() const {
    return this->_mag_z_mean;
}


/**
 * @brief Set_baro_mean
 * @param param1 _baro_mean
 */
void Features::set_baro_mean(double baro_mean) {
    this->_baro_mean = baro_mean;
}
/**
 * @brief Get_baro_mean
 * @return _baro_mean
 */
double Features::get_baro_mean() const {
    return this->_baro_mean;
}


/**
 * @brief Set_acc_x_std
 * @param param1 _acc_x_std
 */
void Features::set_acc_x_std(double acc_x_std) {
    this->_acc_x_std = acc_x_std;
}
/**
 * @brief Get_acc_x_std
 * @return _acc_x_std
 */
double Features::get_acc_x_std() const {
    return this->_acc_x_std;
}

/**
 * @brief Set_acc_y_std
 * @param param1 _acc_y_std
 */
void Features::set_acc_y_std(double acc_y_std) {
    this->_acc_y_std = acc_y_std;
}
/**
 * @brief Get_acc_y_std
 * @return _acc_y_std
 */
double Features::get_acc_y_std() const {
    return this->_acc_y_std;
}

/**
 * @brief Set_acc_z_std
 * @param param1 _acc_z_std
 */
void Features::set_acc_z_std(double acc_z_std) {
    this->_acc_z_std = acc_z_std;
}
/**
 * @brief Get_acc_z_std
 * @return _acc_z_std
 */
double Features::get_acc_z_std() const {
    return this->_acc_z_std;
}

/**
 * @brief Set_gyr_x_std
 * @param param1 _gyr_x_std
 */
void Features::set_gyr_x_std(double gyr_x_std) {
    this->_gyr_x_std = gyr_x_std;
}
/**
 * @brief Get_gyr_x_std
 * @return _gyr_x_std
 */
double Features::get_gyr_x_std() const {
    return this->_gyr_x_std;
}

/**
 * @brief Set_gyr_y_std
 * @param param1 _gyr_y_std
 */
void Features::set_gyr_y_std(double gyr_y_std) {
    this->_gyr_y_std = gyr_y_std;
}
/**
 * @brief Get_gyr_y_std
 * @return _gyr_y_std
 */
double Features::get_gyr_y_std() const {
    return this->_gyr_y_std;
}

/**
 * @brief Set_gyr_z_std
 * @param param1 _gyr_z_std
 */
void Features::set_gyr_z_std(double gyr_z_std) {
    this->_gyr_z_std = gyr_z_std;
}
/**
 * @brief Get_gyr_z_std
 * @return _gyr_z_std
 */
double Features::get_gyr_z_std() const {
    return this->_gyr_z_std;
}



/**
 * @brief Set_mag_x_std
 * @param param1 _mag_x_std
 */
void Features::set_mag_x_std(double mag_x_std) {
    this->_mag_x_std = mag_x_std;
}
/**
 * @brief Get_mag_x_std
 * @return _mag_x_std
 */
double Features::get_mag_x_std() const {
    return this->_mag_x_std;
}

/**
 * @brief Set_mag_y_std
 * @param param1 _mag_y_std
 */
void Features::set_mag_y_std(double mag_y_std) {
    this->_mag_y_std = mag_y_std;
}
/**
 * @brief Get_mag_y_std
 * @return _mag_y_std
 */
double Features::get_mag_y_std() const {
    return this->_mag_y_std;
}

/**
 * @brief Set_mag_z_std
 * @param param1 _mag_z_std
 */
void Features::set_mag_z_std(double mag_z_std) {
    this->_mag_z_std = mag_z_std;
}
/**
 * @brief Get_mag_z_std
 * @return _mag_z_std
 */
double Features::get_mag_z_std() const {
    return this->_mag_z_std;
}


/**
 * @brief Set_baro_std
 * @param param1 _baro_std
 */
void Features::set_baro_std(double baro_std) {
    this->_baro_std = baro_std;
}
/**
 * @brief Get_baro_std
 * @return _baro_std
 */
double Features::get_baro_std() const {
    return this->_baro_std;
}

/**
 * @brief Set_acc_x_skew
 * @param param1 _acc_x_skew
 */
void Features::set_acc_x_skew(double acc_x_skew) {
    this->_acc_x_skew = acc_x_skew;
}
/**
 * @brief Get_acc_x_skew
 * @return _acc_x_skew
 */
double Features::get_acc_x_skew() const {
    return this->_acc_x_skew;
}

/**
 * @brief Set_acc_y_skew
 * @param param1 _acc_y_skew
 */
void Features::set_acc_y_skew(double acc_y_skew) {
    this->_acc_y_skew = acc_y_skew;
}
/**
 * @brief Get_acc_y_skew
 * @return _acc_y_skew
 */
double Features::get_acc_y_skew() const {
    return this->_acc_y_skew;
}

/**
 * @brief Set_acc_z_skew
 * @param param1 _acc_z_skew
 */
void Features::set_acc_z_skew(double acc_z_skew) {
    this->_acc_z_skew = acc_z_skew;
}
/**
 * @brief Get_acc_z_skew
 * @return _acc_z_skew
 */
double Features::get_acc_z_skew() const {
    return this->_acc_z_skew;
}

/**
 * @brief Set_gyr_x_skew
 * @param param1 _gyr_x_skew
 */
void Features::set_gyr_x_skew(double gyr_x_skew) {
    this->_gyr_x_skew = gyr_x_skew;
}
/**
 * @brief Get_gyr_x_skew
 * @return _gyr_x_skew
 */
double Features::get_gyr_x_skew() const {
    return this->_gyr_x_skew;
}

/**
 * @brief Set_gyr_y_skew
 * @param param1 _gyr_y_skew
 */
void Features::set_gyr_y_skew(double gyr_y_skew) {
    this->_gyr_y_skew = gyr_y_skew;
}
/**
 * @brief Get_gyr_y_skew
 * @return _gyr_y_skew
 */
double Features::get_gyr_y_skew() const {
    return this->_gyr_y_skew;
}

/**
 * @brief Set_gyr_z_skew
 * @param param1 _gyr_z_skew
 */
void Features::set_gyr_z_skew(double gyr_z_skew) {
    this->_gyr_z_skew = gyr_z_skew;
}
/**
 * @brief Get_gyr_z_skew
 * @return _gyr_z_skew
 */
double Features::get_gyr_z_skew() const {
    return this->_gyr_z_skew;
}



/**
 * @brief Set_mag_x_skew
 * @param param1 _mag_x_skew
 */
void Features::set_mag_x_skew(double mag_x_skew) {
    this->_mag_x_skew = mag_x_skew;
}
/**
 * @brief Get_mag_x_skew
 * @return _mag_x_skew
 */
double Features::get_mag_x_skew() const {
    return this->_mag_x_skew;
}

/**
 * @brief Set_mag_y_skew
 * @param param1 _mag_y_skew
 */
void Features::set_mag_y_skew(double mag_y_skew) {
    this->_mag_y_skew = mag_y_skew;
}
/**
 * @brief Get_mag_y_skew
 * @return _mag_y_skew
 */
double Features::get_mag_y_skew() const {
    return this->_mag_y_skew;
}

/**
 * @brief Set_mag_z_skew
 * @param param1 _mag_z_skew
 */
void Features::set_mag_z_skew(double mag_z_skew) {
    this->_mag_z_skew = mag_z_skew;
}
/**
 * @brief Get_mag_z_skew
 * @return _mag_z_skew
 */
double Features::get_mag_z_skew() const {
    return this->_mag_z_skew;
}


/**
 * @brief Set_baro_skew
 * @param param1 _baro_skew
 */
void Features::set_baro_skew(double baro_skew) {
    this->_baro_skew = baro_skew;
}
/**
 * @brief Get_baro_skew
 * @return _baro_skew
 */
double Features::get_baro_skew() const {
    return this->_baro_skew;
}

/**
 * @brief Set_acc_x_kurt
 * @param param1 _acc_x_kurt
 */
void Features::set_acc_x_kurt(double acc_x_kurt) {
    this->_acc_x_kurt = acc_x_kurt;
}
/**
 * @brief Get_acc_x_kurt
 * @return _acc_x_kurt
 */
double Features::get_acc_x_kurt() const {
    return this->_acc_x_kurt;
}

/**
 * @brief Set_acc_y_kurt
 * @param param1 _acc_y_kurt
 */
void Features::set_acc_y_kurt(double acc_y_kurt) {
    this->_acc_y_kurt = acc_y_kurt;
}
/**
 * @brief Get_acc_y_kurt
 * @return _acc_y_kurt
 */
double Features::get_acc_y_kurt() const {
    return this->_acc_y_kurt;
}

/**
 * @brief Set_acc_z_kurt
 * @param param1 _acc_z_kurt
 */
void Features::set_acc_z_kurt(double acc_z_kurt) {
    this->_acc_z_kurt = acc_z_kurt;
}
/**
 * @brief Get_acc_z_kurt
 * @return _acc_z_kurt
 */
double Features::get_acc_z_kurt() const {
    return this->_acc_z_kurt;
}

/**
 * @brief Set_gyr_x_kurt
 * @param param1 _gyr_x_kurt
 */
void Features::set_gyr_x_kurt(double gyr_x_kurt) {
    this->_gyr_x_kurt = gyr_x_kurt;
}
/**
 * @brief Get_gyr_x_kurt
 * @return _gyr_x_kurt
 */
double Features::get_gyr_x_kurt() const {
    return this->_gyr_x_kurt;
}

/**
 * @brief Set_gyr_y_kurt
 * @param param1 _gyr_y_kurt
 */
void Features::set_gyr_y_kurt(double gyr_y_kurt) {
    this->_gyr_y_kurt = gyr_y_kurt;
}
/**
 * @brief Get_gyr_y_kurt
 * @return _gyr_y_kurt
 */
double Features::get_gyr_y_kurt() const {
    return this->_gyr_y_kurt;
}

/**
 * @brief Set_gyr_z_kurt
 * @param param1 _gyr_z_kurt
 */
void Features::set_gyr_z_kurt(double gyr_z_kurt) {
    this->_gyr_z_kurt = gyr_z_kurt;
}
/**
 * @brief Get_gyr_z_kurt
 * @return _gyr_z_kurt
 */
double Features::get_gyr_z_kurt() const {
    return this->_gyr_z_kurt;
}



/**
 * @brief Set_mag_x_kurt
 * @param param1 _mag_x_kurt
 */
void Features::set_mag_x_kurt(double mag_x_kurt) {
    this->_mag_x_kurt = mag_x_kurt;
}
/**
 * @brief Get_mag_x_kurt
 * @return _mag_x_kurt
 */
double Features::get_mag_x_kurt() const {
    return this->_mag_x_kurt;
}

/**
 * @brief Set_mag_y_kurt
 * @param param1 _mag_y_kurt
 */
void Features::set_mag_y_kurt(double mag_y_kurt) {
    this->_mag_y_kurt = mag_y_kurt;
}
/**
 * @brief Get_mag_y_kurt
 * @return _mag_y_kurt
 */
double Features::get_mag_y_kurt() const {
    return this->_mag_y_kurt;
}

/**
 * @brief Set_mag_z_kurt
 * @param param1 _mag_z_kurt
 */
void Features::set_mag_z_kurt(double mag_z_kurt) {
    this->_mag_z_kurt = mag_z_kurt;
}
/**
 * @brief Get_mag_z_kurt
 * @return _mag_z_kurt
 */
double Features::get_mag_z_kurt() const {
    return this->_mag_z_kurt;
}


/**
 * @brief Set_baro_kurt
 * @param param1 _baro_kurt
 */
void Features::set_baro_kurt(double baro_kurt) {
    this->_baro_kurt = baro_kurt;
}
/**
 * @brief Get_baro_kurt
 * @return _baro_kurt
 */
double Features::get_baro_kurt() const {
    return this->_baro_kurt;
}

/**
 * @brief Set_acc_x_aad
 * @param param1 _acc_x_aad
 */
void Features::set_acc_x_aad(double acc_x_aad) {
    this->_acc_x_aad = acc_x_aad;
}
/**
 * @brief Get_acc_x_aad
 * @return _acc_x_aad
 */
double Features::get_acc_x_aad() const {
    return this->_acc_x_aad;
}

/**
 * @brief Set_acc_y_aad
 * @param param1 _acc_y_aad
 */
void Features::set_acc_y_aad(double acc_y_aad) {
    this->_acc_y_aad = acc_y_aad;
}
/**
 * @brief Get_acc_y_aad
 * @return _acc_y_aad
 */
double Features::get_acc_y_aad() const {
    return this->_acc_y_aad;
}

/**
 * @brief Set_acc_z_aad
 * @param param1 _acc_z_aad
 */
void Features::set_acc_z_aad(double acc_z_aad) {
    this->_acc_z_aad = acc_z_aad;
}
/**
 * @brief Get_acc_z_aad
 * @return _acc_z_aad
 */
double Features::get_acc_z_aad() const {
    return this->_acc_z_aad;
}

/**
 * @brief Set_gyr_x_aad
 * @param param1 _gyr_x_aad
 */
void Features::set_gyr_x_aad(double gyr_x_aad) {
    this->_gyr_x_aad = gyr_x_aad;
}
/**
 * @brief Get_gyr_x_aad
 * @return _gyr_x_aad
 */
double Features::get_gyr_x_aad() const {
    return this->_gyr_x_aad;
}

/**
 * @brief Set_gyr_y_aad
 * @param param1 _gyr_y_aad
 */
void Features::set_gyr_y_aad(double gyr_y_aad) {
    this->_gyr_y_aad = gyr_y_aad;
}
/**
 * @brief Get_gyr_y_aad
 * @return _gyr_y_aad
 */
double Features::get_gyr_y_aad() const {
    return this->_gyr_y_aad;
}

/**
 * @brief Set_gyr_z_aad
 * @param param1 _gyr_z_aad
 */
void Features::set_gyr_z_aad(double gyr_z_aad) {
    this->_gyr_z_aad = gyr_z_aad;
}
/**
 * @brief Get_gyr_z_aad
 * @return _gyr_z_aad
 */
double Features::get_gyr_z_aad() const {
    return this->_gyr_z_aad;
}



/**
 * @brief Set_mag_x_aad
 * @param param1 _mag_x_aad
 */
void Features::set_mag_x_aad(double mag_x_aad) {
    this->_mag_x_aad = mag_x_aad;
}
/**
 * @brief Get_mag_x_aad
 * @return _mag_x_aad
 */
double Features::get_mag_x_aad() const {
    return this->_mag_x_aad;
}

/**
 * @brief Set_mag_y_aad
 * @param param1 _mag_y_aad
 */
void Features::set_mag_y_aad(double mag_y_aad) {
    this->_mag_y_aad = mag_y_aad;
}
/**
 * @brief Get_mag_y_aad
 * @return _mag_y_aad
 */
double Features::get_mag_y_aad() const {
    return this->_mag_y_aad;
}

/**
 * @brief Set_mag_z_aad
 * @param param1 _mag_z_aad
 */
void Features::set_mag_z_aad(double mag_z_aad) {
    this->_mag_z_aad = mag_z_aad;
}
/**
 * @brief Get_mag_z_aad
 * @return _mag_z_aad
 */
double Features::get_mag_z_aad() const {
    return this->_mag_z_aad;
}


/**
 * @brief Set_baro_aad
 * @param param1 _baro_aad
 */
void Features::set_baro_aad(double baro_aad) {
    this->_baro_aad = baro_aad;
}
/**
 * @brief Get_baro_aad
 * @return _baro_aad
 */
double Features::get_baro_aad() const {
    return this->_baro_aad;
}


/**
 * @brief Set_acc_x_pc
 * @param param1 _acc_x_pc
 */
void Features::set_acc_x_pc(double acc_x_pc) {
    this->_acc_x_pc = acc_x_pc;
}
/**
 * @brief Get_acc_x_pc
 * @return _acc_x_pc
 */
double Features::get_acc_x_pc() const {
    return this->_acc_x_pc;
}

/**
 * @brief Set_acc_y_pc
 * @param param1 _acc_y_pc
 */
void Features::set_acc_y_pc(double acc_y_pc) {
    this->_acc_y_pc = acc_y_pc;
}
/**
 * @brief Get_acc_y_pc
 * @return _acc_y_pc
 */
double Features::get_acc_y_pc() const {
    return this->_acc_y_pc;
}

/**
 * @brief Set_acc_z_pc
 * @param param1 _acc_z_pc
 */
void Features::set_acc_z_pc(double acc_z_pc) {
    this->_acc_z_pc = acc_z_pc;
}
/**
 * @brief Get_acc_z_pc
 * @return _acc_z_pc
 */
double Features::get_acc_z_pc() const {
    return this->_acc_z_pc;
}

/**
 * @brief Set_gyr_x_pc
 * @param param1 _gyr_x_pc
 */
void Features::set_gyr_x_pc(double gyr_x_pc) {
    this->_gyr_x_pc = gyr_x_pc;
}
/**
 * @brief Get_gyr_x_pc
 * @return _gyr_x_pc
 */
double Features::get_gyr_x_pc() const {
    return this->_gyr_x_pc;
}

/**
 * @brief Set_gyr_y_pc
 * @param param1 _gyr_y_pc
 */
void Features::set_gyr_y_pc(double gyr_y_pc) {
    this->_gyr_y_pc = gyr_y_pc;
}
/**
 * @brief Get_gyr_y_pc
 * @return _gyr_y_pc
 */
double Features::get_gyr_y_pc() const {
    return this->_gyr_y_pc;
}

/**
 * @brief Set_gyr_z_pc
 * @param param1 _gyr_z_pc
 */
void Features::set_gyr_z_pc(double gyr_z_pc) {
    this->_gyr_z_pc = gyr_z_pc;
}
/**
 * @brief Get_gyr_z_pc
 * @return _gyr_z_pc
 */
double Features::get_gyr_z_pc() const {
    return this->_gyr_z_pc;
}



/**
 * @brief Set_mag_x_pc
 * @param param1 _mag_x_pc
 */
void Features::set_mag_x_pc(double mag_x_pc) {
    this->_mag_x_pc = mag_x_pc;
}
/**
 * @brief Get_mag_x_pc
 * @return _mag_x_pc
 */
double Features::get_mag_x_pc() const {
    return this->_mag_x_pc;
}

/**
 * @brief Set_mag_y_pc
 * @param param1 _mag_y_pc
 */
void Features::set_mag_y_pc(double mag_y_pc) {
    this->_mag_y_pc = mag_y_pc;
}
/**
 * @brief Get_mag_y_pc
 * @return _mag_y_pc
 */
double Features::get_mag_y_pc() const {
    return this->_mag_y_pc;
}

/**
 * @brief Set_mag_z_pc
 * @param param1 _mag_z_pc
 */
void Features::set_mag_z_pc(double mag_z_pc) {
    this->_mag_z_pc = mag_z_pc;
}
/**
 * @brief Get_mag_z_pc
 * @return _mag_z_pc
 */
double Features::get_mag_z_pc() const {
    return this->_mag_z_pc;
}


/**
 * @brief Set_baro_pc
 * @param param1 _baro_pc
 */
void Features::set_baro_pc(double baro_pc) {
    this->_baro_pc = baro_pc;
}
/**
 * @brief Get_baro_pc
 * @return _baro_pc
 */
double Features::get_baro_pc() const {
    return this->_baro_pc;
}


void Features::set_acc_x_arc(double acc_x_arc) {
    this->_acc_x_arc = acc_x_arc;
}
double Features::get_acc_x_arc() const {
    return this->_acc_x_arc;
}

// Area Under the Curve (suite)
void Features::set_acc_y_arc(double acc_y_arc) {
    this->_acc_y_arc = acc_y_arc;
}
double Features::get_acc_y_arc() const {
    return this->_acc_y_arc;
}

void Features::set_acc_z_arc(double acc_z_arc) {
    this->_acc_z_arc = acc_z_arc;
}
double Features::get_acc_z_arc() const {
    return this->_acc_z_arc;
}

void Features::set_gyr_x_arc(double gyr_x_arc) {
    this->_gyr_x_arc = gyr_x_arc;
}
double Features::get_gyr_x_arc() const {
    return this->_gyr_x_arc;
}

void Features::set_gyr_y_arc(double gyr_y_arc) {
    this->_gyr_y_arc = gyr_y_arc;
}
double Features::get_gyr_y_arc() const {
    return this->_gyr_y_arc;
}

void Features::set_gyr_z_arc(double gyr_z_arc) {
    this->_gyr_z_arc = gyr_z_arc;
}
double Features::get_gyr_z_arc() const {
    return this->_gyr_z_arc;
}

void Features::set_mag_x_arc(double mag_x_arc) {
    this->_mag_x_arc = mag_x_arc;
}
double Features::get_mag_x_arc() const {
    return this->_mag_x_arc;
}

void Features::set_mag_y_arc(double mag_y_arc) {
    this->_mag_y_arc = mag_y_arc;
}
double Features::get_mag_y_arc() const {
    return this->_mag_y_arc;
}

void Features::set_mag_z_arc(double mag_z_arc) {
    this->_mag_z_arc = mag_z_arc;
}
double Features::get_mag_z_arc() const {
    return this->_mag_z_arc;
}

void Features::set_baro_arc(double baro_arc) {
    this->_baro_arc = baro_arc;
}
double Features::get_baro_arc() const {
    return this->_baro_arc;
}

/**
 * @brief Set_acc_x_mad
 * @param param1 _acc_x_mad
 */
void Features::set_acc_x_mad(double acc_x_mad) {
    this->_acc_x_mad = acc_x_mad;
}
/**
 * @brief Get_acc_x_mad
 * @return _acc_x_mad
 */
double Features::get_acc_x_mad() const {
    return this->_acc_x_mad;
}

/**
 * @brief Set_acc_y_mad
 * @param param1 _acc_y_mad
 */
void Features::set_acc_y_mad(double acc_y_mad) {
    this->_acc_y_mad = acc_y_mad;
}
/**
 * @brief Get_acc_y_mad
 * @return _acc_y_mad
 */
double Features::get_acc_y_mad() const {
    return this->_acc_y_mad;
}

/**
 * @brief Set_acc_z_mad
 * @param param1 _acc_z_mad
 */
void Features::set_acc_z_mad(double acc_z_mad) {
    this->_acc_z_mad = acc_z_mad;
}
/**
 * @brief Get_acc_z_mad
 * @return _acc_z_mad
 */
double Features::get_acc_z_mad() const {
    return this->_acc_z_mad;
}

/**
 * @brief Set_gyr_x_mad
 * @param param1 _gyr_x_mad
 */
void Features::set_gyr_x_mad(double gyr_x_mad) {
    this->_gyr_x_mad = gyr_x_mad;
}
/**
 * @brief Get_gyr_x_mad
 * @return _gyr_x_mad
 */
double Features::get_gyr_x_mad() const {
    return this->_gyr_x_mad;
}

/**
 * @brief Set_gyr_y_mad
 * @param param1 _gyr_y_mad
 */
void Features::set_gyr_y_mad(double gyr_y_mad) {
    this->_gyr_y_mad = gyr_y_mad;
}
/**
 * @brief Get_gyr_y_mad
 * @return _gyr_y_mad
 */
double Features::get_gyr_y_mad() const {
    return this->_gyr_y_mad;
}

/**
 * @brief Set_gyr_z_mad
 * @param param1 _gyr_z_mad
 */
void Features::set_gyr_z_mad(double gyr_z_mad) {
    this->_gyr_z_mad = gyr_z_mad;
}
/**
 * @brief Get_gyr_z_mad
 * @return _gyr_z_mad
 */
double Features::get_gyr_z_mad() const {
    return this->_gyr_z_mad;
}



/**
 * @brief Set_mag_x_mad
 * @param param1 _mag_x_mad
 */
void Features::set_mag_x_mad(double mag_x_mad) {
    this->_mag_x_mad = mag_x_mad;
}
/**
 * @brief Get_mag_x_mad
 * @return _mag_x_mad
 */
double Features::get_mag_x_mad() const {
    return this->_mag_x_mad;
}

/**
 * @brief Set_mag_y_mad
 * @param param1 _mag_y_mad
 */
void Features::set_mag_y_mad(double mag_y_mad) {
    this->_mag_y_mad = mag_y_mad;
}
/**
 * @brief Get_mag_y_mad
 * @return _mag_y_mad
 */
double Features::get_mag_y_mad() const {
    return this->_mag_y_mad;
}

/**
 * @brief Set_mag_z_mad
 * @param param1 _mag_z_mad
 */
void Features::set_mag_z_mad(double mag_z_mad) {
    this->_mag_z_mad = mag_z_mad;
}
/**
 * @brief Get_mag_z_mad
 * @return _mag_z_mad
 */
double Features::get_mag_z_mad() const {
    return this->_mag_z_mad;
}


/**
 * @brief Set_baro_mad
 * @param param1 _baro_mad
 */
void Features::set_baro_mad(double baro_mad) {
    this->_baro_mad = baro_mad;
}
/**
 * @brief Get_baro_mad
 * @return _baro_mad
 */
double Features::get_baro_mad() const {
    return this->_baro_mad;
}

// First Peak Index
void Features::set_acc_x_first_peak_index(double acc_x_first_peak_index) {
    this->_acc_x_first_peak_index = acc_x_first_peak_index;
}
double Features::get_acc_x_first_peak_index() const {
    return this->_acc_x_first_peak_index;
}
// First Peak Index (suite)
void Features::set_acc_y_first_peak_index(double acc_y_first_peak_index) {
    this->_acc_y_first_peak_index = acc_y_first_peak_index;
}
double Features::get_acc_y_first_peak_index() const {
    return this->_acc_y_first_peak_index;
}

void Features::set_acc_z_first_peak_index(double acc_z_first_peak_index) {
    this->_acc_z_first_peak_index = acc_z_first_peak_index;
}
double Features::get_acc_z_first_peak_index() const {
    return this->_acc_z_first_peak_index;
}

void Features::set_gyr_x_first_peak_index(double gyr_x_first_peak_index) {
    this->_gyr_x_first_peak_index = gyr_x_first_peak_index;
}
double Features::get_gyr_x_first_peak_index() const {
    return this->_gyr_x_first_peak_index;
}

void Features::set_gyr_y_first_peak_index(double gyr_y_first_peak_index) {
    this->_gyr_y_first_peak_index = gyr_y_first_peak_index;
}
double Features::get_gyr_y_first_peak_index() const {
    return this->_gyr_y_first_peak_index;
}

void Features::set_gyr_z_first_peak_index(double gyr_z_first_peak_index) {
    this->_gyr_z_first_peak_index = gyr_z_first_peak_index;
}
double Features::get_gyr_z_first_peak_index() const {
    return this->_gyr_z_first_peak_index;
}

void Features::set_mag_x_first_peak_index(double mag_x_first_peak_index) {
    this->_mag_x_first_peak_index = mag_x_first_peak_index;
}
double Features::get_mag_x_first_peak_index() const {
    return this->_mag_x_first_peak_index;
}

void Features::set_mag_y_first_peak_index(double mag_y_first_peak_index) {
    this->_mag_y_first_peak_index = mag_y_first_peak_index;
}
double Features::get_mag_y_first_peak_index() const {
    return this->_mag_y_first_peak_index;
}

void Features::set_mag_z_first_peak_index(double mag_z_first_peak_index) {
    this->_mag_z_first_peak_index = mag_z_first_peak_index;
}
double Features::get_mag_z_first_peak_index() const {
    return this->_mag_z_first_peak_index;
}

void Features::set_baro_first_peak_index(double baro_first_peak_index) {
    this->_baro_first_peak_index = baro_first_peak_index;
}
double Features::get_baro_first_peak_index() const {
    return this->_baro_first_peak_index;
}

// First Peak Value
void Features::set_acc_x_first_peak_value(double acc_x_first_peak_value) {
    this->_acc_x_first_peak_value = acc_x_first_peak_value;
}
double Features::get_acc_x_first_peak_value() const {
    return this->_acc_x_first_peak_value;
}
// First Peak Value (suite)
void Features::set_acc_y_first_peak_value(double acc_y_first_peak_value) {
    this->_acc_y_first_peak_value = acc_y_first_peak_value;
}
double Features::get_acc_y_first_peak_value() const {
    return this->_acc_y_first_peak_value;
}

void Features::set_acc_z_first_peak_value(double acc_z_first_peak_value) {
    this->_acc_z_first_peak_value = acc_z_first_peak_value;
}
double Features::get_acc_z_first_peak_value() const {
    return this->_acc_z_first_peak_value;
}

void Features::set_gyr_x_first_peak_value(double gyr_x_first_peak_value) {
    this->_gyr_x_first_peak_value = gyr_x_first_peak_value;
}
double Features::get_gyr_x_first_peak_value() const {
    return this->_gyr_x_first_peak_value;
}

void Features::set_gyr_y_first_peak_value(double gyr_y_first_peak_value) {
    this->_gyr_y_first_peak_value = gyr_y_first_peak_value;
}
double Features::get_gyr_y_first_peak_value() const {
    return this->_gyr_y_first_peak_value;
}

void Features::set_gyr_z_first_peak_value(double gyr_z_first_peak_value) {
    this->_gyr_z_first_peak_value = gyr_z_first_peak_value;
}
double Features::get_gyr_z_first_peak_value() const {
    return this->_gyr_z_first_peak_value;
}

void Features::set_mag_x_first_peak_value(double mag_x_first_peak_value) {
    this->_mag_x_first_peak_value = mag_x_first_peak_value;
}
double Features::get_mag_x_first_peak_value() const {
    return this->_mag_x_first_peak_value;
}

void Features::set_mag_y_first_peak_value(double mag_y_first_peak_value) {
    this->_mag_y_first_peak_value = mag_y_first_peak_value;
}
double Features::get_mag_y_first_peak_value() const {
    return this->_mag_y_first_peak_value;
}

void Features::set_mag_z_first_peak_value(double mag_z_first_peak_value) {
    this->_mag_z_first_peak_value = mag_z_first_peak_value;
}
double Features::get_mag_z_first_peak_value() const {
    return this->_mag_z_first_peak_value;
}

void Features::set_baro_first_peak_value(double baro_first_peak_value) {
    this->_baro_first_peak_value = baro_first_peak_value;
}
double Features::get_baro_first_peak_value() const {
    return this->_baro_first_peak_value;
}

// Second Peak Index
void Features::set_acc_x_second_peak_index(double acc_x_second_peak_index) {
    this->_acc_x_second_peak_index = acc_x_second_peak_index;
}
double Features::get_acc_x_second_peak_index() const {
    return this->_acc_x_second_peak_index;
}
// Second Peak Index (suite)
void Features::set_acc_y_second_peak_index(double acc_y_second_peak_index) {
    this->_acc_y_second_peak_index = acc_y_second_peak_index;
}
double Features::get_acc_y_second_peak_index() const {
    return this->_acc_y_second_peak_index;
}

void Features::set_acc_z_second_peak_index(double acc_z_second_peak_index) {
    this->_acc_z_second_peak_index = acc_z_second_peak_index;
}
double Features::get_acc_z_second_peak_index() const {
    return this->_acc_z_second_peak_index;
}

void Features::set_gyr_x_second_peak_index(double gyr_x_second_peak_index) {
    this->_gyr_x_second_peak_index = gyr_x_second_peak_index;
}
double Features::get_gyr_x_second_peak_index() const {
    return this->_gyr_x_second_peak_index;
}

void Features::set_gyr_y_second_peak_index(double gyr_y_second_peak_index) {
    this->_gyr_y_second_peak_index = gyr_y_second_peak_index;
}
double Features::get_gyr_y_second_peak_index() const {
    return this->_gyr_y_second_peak_index;
}

void Features::set_gyr_z_second_peak_index(double gyr_z_second_peak_index) {
    this->_gyr_z_second_peak_index = gyr_z_second_peak_index;
}
double Features::get_gyr_z_second_peak_index() const {
    return this->_gyr_z_second_peak_index;
}

void Features::set_mag_x_second_peak_index(double mag_x_second_peak_index) {
    this->_mag_x_second_peak_index = mag_x_second_peak_index;
}
double Features::get_mag_x_second_peak_index() const {
    return this->_mag_x_second_peak_index;
}

void Features::set_mag_y_second_peak_index(double mag_y_second_peak_index) {
    this->_mag_y_second_peak_index = mag_y_second_peak_index;
}
double Features::get_mag_y_second_peak_index() const {
    return this->_mag_y_second_peak_index;
}

void Features::set_mag_z_second_peak_index(double mag_z_second_peak_index) {
    this->_mag_z_second_peak_index = mag_z_second_peak_index;
}
double Features::get_mag_z_second_peak_index() const {
    return this->_mag_z_second_peak_index;
}

void Features::set_baro_second_peak_index(double baro_second_peak_index) {
    this->_baro_second_peak_index = baro_second_peak_index;
}
double Features::get_baro_second_peak_index() const {
    return this->_baro_second_peak_index;
}

void Features::set_acc_x_second_peak_value(double acc_x_second_peak_value) {
    this->_acc_x_second_peak_value = acc_x_second_peak_value;
}
double Features::get_acc_x_second_peak_value() const {
    return this->_acc_x_second_peak_value;
}
// Second Peak Value (suite)
void Features::set_acc_y_second_peak_value(double acc_y_second_peak_value) {
    this->_acc_y_second_peak_value = acc_y_second_peak_value;
}
double Features::get_acc_y_second_peak_value() const {
    return this->_acc_y_second_peak_value;
}

void Features::set_acc_z_second_peak_value(double acc_z_second_peak_value) {
    this->_acc_z_second_peak_value = acc_z_second_peak_value;
}
double Features::get_acc_z_second_peak_value() const {
    return this->_acc_z_second_peak_value;
}

void Features::set_gyr_x_second_peak_value(double gyr_x_second_peak_value) {
    this->_gyr_x_second_peak_value = gyr_x_second_peak_value;
}
double Features::get_gyr_x_second_peak_value() const {
    return this->_gyr_x_second_peak_value;
}

void Features::set_gyr_y_second_peak_value(double gyr_y_second_peak_value) {
    this->_gyr_y_second_peak_value = gyr_y_second_peak_value;
}
double Features::get_gyr_y_second_peak_value() const {
    return this->_gyr_y_second_peak_value;
}

void Features::set_gyr_z_second_peak_value(double gyr_z_second_peak_value) {
    this->_gyr_z_second_peak_value = gyr_z_second_peak_value;
}
double Features::get_gyr_z_second_peak_value() const {
    return this->_gyr_z_second_peak_value;
}

void Features::set_mag_x_second_peak_value(double mag_x_second_peak_value) {
    this->_mag_x_second_peak_value = mag_x_second_peak_value;
}
double Features::get_mag_x_second_peak_value() const {
    return this->_mag_x_second_peak_value;
}

void Features::set_mag_y_second_peak_value(double mag_y_second_peak_value) {
    this->_mag_y_second_peak_value = mag_y_second_peak_value;
}
double Features::get_mag_y_second_peak_value() const {
    return this->_mag_y_second_peak_value;
}

void Features::set_mag_z_second_peak_value(double mag_z_second_peak_value) {
    this->_mag_z_second_peak_value = mag_z_second_peak_value;
}
double Features::get_mag_z_second_peak_value() const {
    return this->_mag_z_second_peak_value;
}

void Features::set_baro_second_peak_value(double baro_second_peak_value) {
    this->_baro_second_peak_value = baro_second_peak_value;
}
double Features::get_baro_second_peak_value() const {
    return this->_baro_second_peak_value;
}




