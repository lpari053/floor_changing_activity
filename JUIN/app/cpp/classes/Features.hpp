//
//  Features.hpp
//  labcom
//
//  Created by William OCCELLI on 08/04/2022.
//

#ifndef Features_hpp
#define Features_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Features {
public:
    Features();
    ~Features();

    void set_nb_step(int nb_step);
    int get_nb_step() const;


    void set_acc_norm_mean(double acc_norm_mean);
    double get_acc_norm_mean() const;

    void set_acc_norm_mad(double acc_norm_mad);
    double get_acc_norm_mad() const;

    void set_acc_norm_aad(double acc_norm_aad);
    double get_acc_norm_aad() const;

    void set_acc_norm_std(double acc_norm_std);
    double get_acc_norm_std() const;

    void set_acc_norm_kurt(double acc_norm_kurt);
    double get_acc_norm_kurt() const;

    void set_acc_norm_skew(double acc_norm_skew);
    double get_acc_norm_skew() const;

    void set_acc_norm_first_peak_index(double acc_norm_first_peak_index);
    double get_acc_norm_first_peak_index() const;

    void set_acc_norm_first_peak_value(double acc_norm_first_peak_value);
    double get_acc_norm_first_peak_value() const;

    void set_acc_norm_second_peak_index(double acc_norm_second_peak_index);
    double get_acc_norm_second_peak_index() const;

    void set_acc_norm_second_peak_value(double acc_norm_second_peak_value);
    double get_acc_norm_second_peak_value() const;


    void set_gyro_norm_mean(double gyro_norm_mean);
    double get_gyro_norm_mean() const;

    void set_gyro_norm_aad(double gyro_norm_aad);
    double get_gyro_norm_aad() const;

    void set_gyro_norm_std(double gyro_norm_std);
    double get_gyro_norm_std() const;

    void set_gyro_norm_kurt(double gyro_norm_kurt);
    double get_gyro_norm_kurt() const;

    void set_gyro_norm_skew(double gyro_norm_skew);
    double get_gyro_norm_skew() const;


    void set_mag_norm_mean(double mag_norm_mean);
    double get_mag_norm_mean() const;


    void set_mag_norm_aad(double mag_norm_aad);
    double get_mag_norm_aad() const;

    void set_mag_norm_std(double mag_norm_std);
    double get_mag_norm_std() const;

    void set_mag_norm_kurt(double mag_norm_kurt);
    double get_mag_norm_kurt() const;

    void set_mag_norm_skew(double mag_norm_skew);
    double get_mag_norm_skew() const;

    
    void set_acc_median_win80(double);
    double get_acc_median_win80() const;
    void set_acc_kurtosis_win30(double);
    double get_acc_kurtosis_win30() const;
    void set_acc_skewness_win5(double);
    double get_acc_skewness_win5() const;
    void set_acc_minElement_win30(double);
    double get_acc_minElement_win30() const;
    void set_acc_valley_prominences_win80(double);
    double get_acc_valley_prominences_win80() const;
    void set_acc_peak_prominences_win80(double);
    double get_acc_peak_prominences_win80() const;
    void set_acc_peak_prominences_win50(double);
    double get_acc_peak_prominences_win50() const;
    void set_acc_dominant_frequency(double);
    double get_acc_dominant_frequency() const;

    void set_gyro_skewness_win70(double);
    double get_gyro_skewness_win70() const;
    void set_gyro_skewness_win30(double);
    double get_gyro_skewness_win30() const;
    void set_gyro_maxElement_win60(double);
    double get_gyro_maxElement_win60() const;
    void set_gyro_sma_win80(double);
    double get_gyro_sma_win80() const;
    void set_gyro_variance_win20(double);
    double get_gyro_variance_win20() const;
    void set_gyro_maxValue_win70(double);
    double get_gyro_maxValue_win70() const;
    void set_gyro_valley_prominences_win80(double);
    double get_gyro_valley_prominences_win80() const;
    void set_gyro_max_frequency(double);
    double get_gyro_max_frequency() const;

    void set_mag_skewness_win70(double);
    double get_mag_skewness_win70() const;
    void set_mag_skewness_win30(double);
    double get_mag_skewness_win30() const;
    void set_mag_maxElement_win60(double);
    double get_mag_maxElement_win60() const;
    void set_mag_sma_win80(double);
    double get_mag_sma_win80() const;
    void set_mag_variance_win20(double);
    double get_mag_variance_win20() const;
    void set_mag_maxValue_win70(double);
    double get_mag_maxValue_win70() const;
    void set_mag_valley_prominences_win80(double);
    double get_mag_valley_prominences_win80() const;
    void set_mag_max_frequency(double);
    double get_mag_max_frequency() const;


    void set_acc_x_mean(double acc_x_mean);
    double get_acc_x_mean() const;

    void set_acc_y_mean(double acc_y_mean);
    double get_acc_y_mean() const;

    void set_acc_z_mean(double acc_z_mean);
    double get_acc_z_mean() const;

    void set_acc_x_std(double acc_x_std);
    double get_acc_x_std() const;

    void set_acc_y_std(double acc_y_std);
    double get_acc_y_std() const;

    void set_acc_z_std(double acc_z_std);
    double get_acc_z_std() const;

    void set_acc_x_skew(double acc_x_skew);
    double get_acc_x_skew() const;

    void set_acc_y_skew(double acc_y_skew);
    double get_acc_y_skew() const;

    void set_acc_z_skew(double acc_z_skew);
    double get_acc_z_skew() const ;

    void set_acc_x_kurt(double acc_x_kurt);
    double get_acc_x_kurt() const;

    void set_acc_y_kurt(double acc_y_kurt);
    double get_acc_y_kurt() const;

    void set_acc_z_kurt(double acc_z_kurt);
    double get_acc_z_kurt() const ;

    void set_acc_x_aad(double acc_x_aad);
    double get_acc_x_aad() const;

    void set_acc_y_aad(double acc_y_aad);
    double get_acc_y_aad() const;

    void set_acc_z_aad(double acc_z_aad);
    double get_acc_z_aad() const ;



    void set_acc_x_arc(double acc_x_arc) ;
    double get_acc_x_arc() const;

    void set_gyr_x_mean(double gyr_x_mean);
    double get_gyr_x_mean() const;

    void set_gyr_y_mean(double gyr_y_mean);
    double get_gyr_y_mean() const;

    void set_gyr_z_mean(double gyr_z_mean);
    double get_gyr_z_mean() const;

    void set_gyr_x_std(double gyr_x_std);
    double get_gyr_x_std() const;

    void set_gyr_y_std(double gyr_y_std);
    double get_gyr_y_std() const;

    void set_gyr_z_std(double gyr_z_std);
    double get_gyr_z_std() const;

    void set_gyr_x_skew(double gyr_x_skew);
    double get_gyr_x_skew() const;

    void set_gyr_y_skew(double gyr_y_skew);
    double get_gyr_y_skew() const;

    void set_gyr_z_skew(double gyr_z_skew);
    double get_gyr_z_skew() const ;

    void set_gyr_x_kurt(double gyr_x_kurt);
    double get_gyr_x_kurt() const;

    void set_gyr_y_kurt(double gyr_y_kurt);
    double get_gyr_y_kurt() const;

    void set_gyr_z_kurt(double gyr_z_kurt);
    double get_gyr_z_kurt() const ;

    void set_gyr_x_aad(double gyr_x_aad);
    double get_gyr_x_aad() const;

    void set_gyr_y_aad(double gyr_y_aad);
    double get_gyr_y_aad() const;

    void set_gyr_z_aad(double gyr_z_aad);
    double get_gyr_z_aad() const ;

    void set_gyr_x_arc(double gyr_x_arc) ;
    double get_gyr_x_arc() const;

    void set_mag_x_mean(double mag_x_mean);
    double get_mag_x_mean() const;

    void set_mag_y_mean(double mag_y_mean);
    double get_mag_y_mean() const;

    void set_mag_z_mean(double mag_z_mean);
    double get_mag_z_mean() const;

    void set_mag_x_std(double mag_x_std);
    double get_mag_x_std() const;

    void set_mag_y_std(double mag_y_std);
    double get_mag_y_std() const;

    void set_mag_z_std(double mag_z_std);
    double get_mag_z_std() const;

    void set_mag_x_skew(double mag_x_skew);
    double get_mag_x_skew() const;

    void set_mag_y_skew(double mag_y_skew);
    double get_mag_y_skew() const;

    void set_mag_z_skew(double mag_z_skew);
    double get_mag_z_skew() const ;

    void set_mag_x_kurt(double mag_x_kurt);
    double get_mag_x_kurt() const;

    void set_mag_y_kurt(double mag_y_kurt);
    double get_mag_y_kurt() const;

    void set_mag_z_kurt(double mag_z_kurt);
    double get_mag_z_kurt() const ;

    void set_mag_x_aad(double mag_x_aad);
    double get_mag_x_aad() const;

    void set_mag_y_aad(double mag_y_aad);
    double get_mag_y_aad() const;

    void set_mag_z_aad(double mag_z_aad);
    double get_mag_z_aad() const ;

    void set_mag_x_arc(double mag_x_arc) ;
    double get_mag_x_arc() const;

    void set_baro_mean(double baro_mean);
    double get_baro_mean() const ;

    void set_baro_std(double baro_std);
    double get_baro_std() const ;

    void set_baro_skew(double baro_skew);
    double get_baro_skew() const;


    void set_baro_kurt(double baro_kurt);
    double get_baro_kurt() const;


    void set_baro_aad(double baro_aad);
    double get_baro_aad() const;



private:

    int nb_step;
    double _test_accx;
    double _acc_median_win80;
    double _acc_kurtosis_win30;
    double _acc_skewness_win5;
    double _acc_minElement_win30;
    double _acc_peak_prominences_win50;
    double _acc_peak_prominences_win80;
    double _acc_valley_prominences_win80;
    double _acc_dominant_frequency;

    double _gyro_skewness_win70;
    double _gyro_skewness_win30;
    double _gyro_maxElement_win60;
    double _gyro_sma_win80;
    double _gyro_variance_win20;
    double _gyro_maxValue_win70;
    double _gyro_valley_prominences_win80;
    double _gyro_max_frequency;

    double _mag_skewness_win70;
    double _mag_skewness_win30;
    double _mag_maxElement_win60;
    double _mag_sma_win80;
    double _mag_variance_win20;
    double _mag_maxValue_win70;
    double _mag_valley_prominences_win80;
    double _mag_max_frequency;


    double _acc_norm_mean;
    double _acc_norm_std;
    double _acc_norm_mad;
    double _acc_norm_kurt;
    double _acc_norm_skew;
    double _acc_norm_aad;
    double _gyro_norm_mean;
    double _gyro_norm_std;
    double _gyro_norm_mad;
    double _gyro_norm_kurt;
    double _gyro_norm_skew;
    double _gyro_norm_aad;
    double _mag_norm_mean;
    double _mag_norm_std;
    double _mag_norm_mad;
    double _mag_norm_kurt;
    double _mag_norm_skew;
    double _mag_norm_aad;
    double _acc_x_mean;
    double _acc_y_mean;
    double _acc_z_mean;

    double _gyr_x_mean;
    double _gyr_y_mean;
    double _gyr_z_mean;


    double _mag_x_mean;
    double _mag_y_mean;
    double _mag_z_mean;

    double _baro_mean;

    double _acc_x_std;
    double _acc_y_std;
    double _acc_z_std;

    double _gyr_x_std;
    double _gyr_y_std;
    double _gyr_z_std;


    double _mag_x_std;
    double _mag_y_std;
    double _mag_z_std;

    double _baro_std;

    double _acc_x_skew;
    double _acc_y_skew;
    double _acc_z_skew;

    double _gyr_x_skew;
    double _gyr_y_skew;
    double _gyr_z_skew;


    double _mag_x_skew;
    double _mag_y_skew;
    double _mag_z_skew;

    double _baro_skew;

    double _acc_x_kurt;
    double _acc_y_kurt;
    double _acc_z_kurt;

    double _gyr_x_kurt;
    double _gyr_y_kurt;
    double _gyr_z_kurt;


    double _mag_x_kurt;
    double _mag_y_kurt;
    double _mag_z_kurt;

    double _baro_kurt;

    double _acc_x_aad;
    double _acc_y_aad;
    double _acc_z_aad;

    double _gyr_x_aad;
    double _gyr_y_aad;
    double _gyr_z_aad;


    double _mag_x_aad;
    double _mag_y_aad;
    double _mag_z_aad;

    double _baro_aad;


    double _acc_x_pc;
    double _acc_y_pc;
    double _acc_z_pc;

    double _gyr_x_pc;
    double _gyr_y_pc;
    double _gyr_z_pc;


    double _mag_x_pc;
    double _mag_y_pc;
    double _mag_z_pc;

    double _baro_pc;

    double _acc_x_arc;
    double _acc_y_arc;
    double _acc_z_arc;

    double _gyr_x_arc;
    double _gyr_y_arc;
    double _gyr_z_arc;


    double _mag_x_arc;
    double _mag_y_arc;
    double _mag_z_arc;

    double _baro_arc;


    double _acc_x_mad;
    double _acc_y_mad;
    double _acc_z_mad;

    double _gyr_x_mad;
    double _gyr_y_mad;
    double _gyr_z_mad;


    double _mag_x_mad;
    double _mag_y_mad;
    double _mag_z_mad;

    double _baro_mad;







}
;


#endif /* Features_hpp */
