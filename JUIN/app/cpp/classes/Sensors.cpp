//
//  Sensors.cpp
//  labcom
//
//  Created by Yohann Tschudi on 15/02/2022.
//

#include "Sensors.hpp"

// Constructors
// Sensors::Sensors() :
// _acc_x(0.0), _acc_y(0.0), _acc_z(0.0), _gyro_x(0.0), _gyro_y(0.0), _gyro_z(0.0), _acc_norm_nf(0.0),_gyro_norm_nf(0.0), _acc_norm(0.0), _gyro_norm(0.0){}

Sensors::Sensors() :
        _mag_norm_nf(0.0),_mag_norm(0.0), _mag_x(0.0), _mag_y(0.0), _mag_z(0.0),_acc_x(0.0), _acc_y(0.0), _acc_z(0.0), _gyro_x(0.0), _gyro_y(0.0), _gyro_z(0.0), _acc_norm_nf(0.0),_gyro_norm_nf(0.0), _acc_norm(0.0), _gyro_norm(0.0){}


Sensors::Sensors(double acc_x, double acc_y, double acc_z, double gyro_x, double gyro_y, double gyro_z) :
_acc_x(acc_x), _acc_y(acc_y), _acc_z(acc_z), _gyro_x(gyro_x), _gyro_y(gyro_y), _gyro_z(gyro_z) {}


Sensors::Sensors(double acc_x, double acc_y, double acc_z, double gyro_x, double gyro_y, double gyro_z,
                 double mag_x, double mag_y, double mag_z) :
_acc_x(acc_x), _acc_y(acc_y), _acc_z(acc_z), _gyro_x(gyro_x), _gyro_y(gyro_y), _gyro_z(gyro_z),_mag_x(mag_x), _mag_y(mag_y), _mag_z(mag_z){}

Sensors::Sensors(double acc_x, double acc_y, double acc_z, double gyro_x, double gyro_y, double gyro_z,
                 double mag_x, double mag_y, double mag_z,double baro,int step,double time) :
        _acc_x(acc_x), _acc_y(acc_y), _acc_z(acc_z),
        _gyro_x(gyro_x), _gyro_y(gyro_y), _gyro_z(gyro_z),
        _mag_x(mag_x), _mag_y(mag_y), _mag_z(mag_z),
        baro(baro),step(step),time(time){}


void Sensors::set_baro(double baro) {
    this->baro = baro;
}
void Sensors::set_time(double time) {
    this->time = time;
}
void Sensors::set_step(int step) {
    this->step = step;
}

double Sensors::get_baro() const {
    return this->baro;
}

double Sensors::get_time() const {
    return this->time;
}

int Sensors::get_step() const {
    return this->step;
}

// Accelerometre
void Sensors::set_acc_x(double acc_x) {
    this->_acc_x = acc_x;
}
void Sensors::set_acc_y(double acc_y) {
    this->_acc_y = acc_y;
}
void Sensors::set_acc_z(double acc_z) {
    this->_acc_z = acc_z;
}
double Sensors::get_acc_x() const {
    return this->_acc_x;
}
double Sensors::get_acc_y() const {
    return this->_acc_y;
}
double Sensors::get_acc_z() const {
    return this->_acc_z;
}

void Sensors::set_acc_norm(double acc_norm) {
    this->_acc_norm = acc_norm;
}
double Sensors::get_acc_norm() const {
    return this->_acc_norm;
}

/*void Sensors::set_acc_norm_nf(double acc_norm_nf) {
 this->_acc_norm_nf = acc_norm_nf;
 }
 double Sensors::get_acc_norm_nf() const {
 return this->_acc_norm_nf;
 }*/


// Gyroscope
void Sensors::set_gyro_x(double gyro_x) {
    this->_gyro_x = gyro_x;
}
void Sensors::set_gyro_y(double gyro_y) {
    this->_gyro_y = gyro_y;
}
void Sensors::set_gyro_z(double gyro_z) {
    this->_gyro_z = gyro_z;
}
double Sensors::get_gyro_x() const {
    return this->_gyro_x;
}
double Sensors::get_gyro_y() const {
    return this->_gyro_y;
}
double Sensors::get_gyro_z() const {
    return this->_gyro_z;
}
void Sensors::set_gyro_norm(double gyro_norm) {
    this->_gyro_norm = gyro_norm;
}
double Sensors::get_gyro_norm() const {
    return this->_gyro_norm;
}
/*void Sensors::set_gyro_norm_nf(double gyro_norm_nf) {
 this->_gyro_norm_nf = gyro_norm_nf;
 }
 double Sensors::get_gyro_norm_nf() const {
 return this->_gyro_norm_nf;
 }*/

vector<double> Sensors::get_sensors_acc_gyro_xyz() const {
    vector<double> acc_gyro_xyz;
    
    acc_gyro_xyz.push_back(get_acc_x());
    acc_gyro_xyz.push_back(get_acc_y());
    acc_gyro_xyz.push_back(get_acc_z());
    acc_gyro_xyz.push_back(get_gyro_x());
    acc_gyro_xyz.push_back(get_gyro_y());
    acc_gyro_xyz.push_back(get_gyro_z());
    
    return acc_gyro_xyz;
}

vector<double> Sensors::get_sensors_acc_xyz() const {
    vector<double> acc_xyz;
    
    acc_xyz.push_back(get_acc_x());
    acc_xyz.push_back(get_acc_y());
    acc_xyz.push_back(get_acc_z());
    
    return acc_xyz;
}

vector<double> Sensors::get_sensors_gyro_xyz() const {
    vector<double> gyro_xyz;
    
    gyro_xyz.push_back(get_gyro_x());
    gyro_xyz.push_back(get_gyro_y());
    gyro_xyz.push_back(get_gyro_z());
    
    return gyro_xyz;
}


void Sensors::set_mag_x(double mag_x) {
    this->_mag_x = mag_x;
}
void Sensors::set_mag_y(double mag_y) {
    this->_mag_y = mag_y;
}
void Sensors::set_mag_z(double mag_z) {
    this->_mag_z = mag_z;
}
double Sensors::get_mag_x() const {
    return this->_mag_x;
}
double Sensors::get_mag_y() const {
    return this->_mag_y;
}
double Sensors::get_mag_z() const {
    return this->_mag_z;
}
void Sensors::set_mag_norm(double mag_norm) {
    this->_mag_norm = mag_norm;
}
double Sensors::get_mag_norm() const {
    return this->_mag_norm;
}


vector<double> Sensors::get_sensors_mag_xyz() const {
    vector<double> mag_xyz;

    mag_xyz.push_back(get_mag_x());
    mag_xyz.push_back(get_mag_y());
    mag_xyz.push_back(get_mag_z());

    return mag_xyz;
}

/*
Sensors::Sensors(jsize i) {

}*/
