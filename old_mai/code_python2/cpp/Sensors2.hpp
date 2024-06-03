//
//  Sensors2.hpp
//  labcom
//
//  Created by Yohann Tschudi on 15/02/2022.
//

#ifndef Sensors2_hpp
#define Sensors2_hpp

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Sensors2 {
public:
    // Constructors and destructor
    Sensors2();
    Sensors2(double acc_x, double acc_y, double acc_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z);

    ~Sensors2();

    // Accessors and mutators
    void set_acc_x(double);
    double get_acc_x() const;
    void set_acc_y(double);
    double get_acc_y() const;
    void set_acc_z(double);
    double get_acc_z() const;

    void set_gyro_x(double);
    double get_gyro_x() const;
    void set_gyro_y(double);
    double get_gyro_y() const;
    void set_gyro_z(double);
    double get_gyro_z() const;

    void set_mag_x(double mag_x);
    double get_mag_x() const;
    void set_mag_y(double mag_y);
    double get_mag_y() const;
    void set_mag_z(double mag_z);
    double get_mag_z() const;

    void set_acc_norm(double);
    double get_acc_norm() const;
    void set_gyro_norm(double);
    double get_gyro_norm() const;
    void set_mag_norm(double);
    double get_mag_norm() const;

   /* void set_acc_norm_nf(double);
    double get_acc_norm_nf() const;

    void set_gyro_norm_nf(double);
    double get_gyro_norm_nf() const;*/

    // Others methods
    std::vector<double>  get_sensors_acc_gyro_xyz() const;
    std::vector<double>  get_sensors_acc_xyz() const;
    std::vector<double>  get_sensors_gyro_xyz() const;
    std::vector<double>  get_sensors_mag_xyz() const;
    std::vector<double>  get_sensors_acc_gyro_mag_xyz() const;


private:

    // Accelerometre
    double _acc_x;
    double _acc_y;
    double _acc_z;

    double _acc_norm_nf;
    double _acc_norm;

    // Gyroscope
    double _gyro_x;
    double _gyro_y;
    double _gyro_z;

    // Magnetometre
    double _mag_x;
    double _mag_y;
    double _mag_z;
    double _mag_norm;
    double _mag_norm_nf;

    //delete after
    double _acc_x_f;
    double _gyro_norm;
    double _gyro_norm_nf;
};

#endif /* Sensors2_hpp */
