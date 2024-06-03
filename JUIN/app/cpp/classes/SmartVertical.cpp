//
//  Features.cpp
//  labcom
//
//  Created by Yacouba KONE on 31/05/2022.
//

#include "FeaturesCalculatorVertical.hpp"
#include "Features.hpp"
#include "Sensors.hpp"
#include "VerticalModel.hpp"
#include "VerticalProbabilities.hpp"
#include "SmartVertical.hpp"
#include <android/log.h>
#define LOG_TAG "SmartVertical"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// Default constructor
SmartVertical::SmartVertical() {};
// Destructor
SmartVertical::~SmartVertical() {};

void SmartVertical::Init(const char* actiModel){
    verticalModel = new VerticalModel(actiModel);
	featuresCalculatorvertical = new FeaturesCalculatorVertical();
}

vector<double> SmartVertical::Inference(Sensors* VectData, int threshold){

    bool stage=featuresCalculatorvertical->computeSensor(VectData);

    if (stage){

Features *features = featuresCalculatorvertical->computeFeatureVertical();

    vector<float> inputValuesAll = {

            (float) features->get_acc_x_arc(),
            (float)  features->get_gyr_x_arc(),
            (float)   features->get_mag_x_arc(),
            (float) features->get_acc_x_aad(),
            (float)  features->get_acc_x_mean(),
            (float)  features->get_acc_x_std(),
            (float)  features->get_acc_x_kurt(),
            (float)    features->get_acc_x_skew(),
            (float)    features->get_acc_y_aad(),
            (float)  features->get_acc_y_mean(),
            (float)   features->get_acc_y_std(),
            (float)    features->get_acc_y_kurt(),
            (float)    features->get_acc_y_skew(),
            (float)   features->get_acc_z_aad(),
            (float)  features->get_acc_z_mean(),
            (float) features->get_acc_z_std(),
            (float)  features->get_acc_z_kurt(),
            (float)   features->get_acc_z_skew(),
            (float)  features->get_gyr_x_aad(),
            (float) features->get_gyr_x_mean(),
            (float) features->get_gyr_x_std(),
            (float) features->get_gyr_x_kurt(),
            (float)  features->get_gyr_x_skew(),
            (float) features->get_gyr_y_aad(),
            (float)  features->get_gyr_y_mean(),
            (float)  features->get_gyr_y_std(),
            (float)    features->get_gyr_y_kurt(),
            (float)     features->get_gyr_y_skew(),
            (float)    features->get_gyr_z_aad(),
            (float)    features->get_gyr_z_mean(),
            (float)    features->get_gyr_z_std(),
            (float)   features->get_gyr_z_kurt(),
            (float)   features->get_gyr_z_skew(),
            (float) features->get_mag_x_aad(),
            (float)   features->get_mag_x_mean(),
            (float)   features->get_mag_x_std(),
            (float)   features->get_mag_x_kurt(),
            (float)   features->get_mag_x_skew(),
            (float)   features->get_mag_y_aad(),
            (float)   features->get_mag_y_mean(),
            (float)     features->get_mag_y_std(),
            (float)    features->get_mag_y_kurt(),
            (float)    features->get_mag_y_skew(),
            (float)    features->get_mag_z_aad(),
            (float)   features->get_mag_z_mean(),
            (float)     features->get_mag_z_std(),
            (float)     features->get_mag_z_kurt(),
            (float)     features->get_mag_z_skew(),
            (float)    features->get_baro_aad(),
            (float)   features->get_baro_mean(),
            (float)   features->get_baro_std(),
            (float)  features->get_baro_kurt(),
            (float) features->get_baro_skew(),
            (float)    features->get_nb_step(),
            (float)    features->get_acc_norm_aad(),
            (float)    features->get_acc_norm_mean(),
            (float)    features->get_acc_norm_std(),
            (float)     features->get_acc_norm_kurt(),
            (float)    features->get_acc_norm_skew(),
            (float)     features->get_gyro_norm_aad(),
            (float)    features->get_gyro_norm_mean(),
            (float)     features->get_gyro_norm_std(),
            (float)     features->get_gyro_norm_kurt(),
            (float)    features->get_gyro_norm_skew(),
            (float)   features->get_mag_norm_aad(),
            (float)    features->get_mag_norm_mean(),
            (float)    features->get_mag_norm_std(),
            (float)    features->get_mag_norm_kurt(),
            (float)   features->get_mag_norm_skew()
    
    
    };


   vector<double> probabilitiesVertical = verticalModel->runModel(inputValuesAll);
        LOGD("Example double value: %f", features->get_mag_norm_skew());
        LOGD("Example double value: %f", probabilitiesVertical[1]);
         VerticalProbabilities *vertiProbabilities = new VerticalProbabilities();
           vertiProbabilities->set_vertical(probabilitiesVertical);

          return (vector<double>) vertiProbabilities->get_vertical();
     //   return{-2.0,-2.0};
    }

    else{

        return{-1.0,-1.0};

    }

}
