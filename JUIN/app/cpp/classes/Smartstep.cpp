//
//  Features.cpp
//  labcom
//
//  Created by Yacouba KONE on 31/05/2022.
//

#include "FeaturesCalculator.hpp"
#include "Features.hpp"
#include "Sensors.hpp"
#include "GyroscopeModel.hpp"
#include "AccelerometerModel.hpp"
#include "StepProbabilities.hpp"
#include "Smartstep.hpp"
#include "StepProbabilities.hpp"


// Default constructor
Smartstep::Smartstep() {};
// Destructor
Smartstep::~Smartstep () {};

void Smartstep::Init(const char* accModel, const char* gyroModel){
	    // Model
    accelerometerModel = new AccelerometerModel(accModel);
    gyroscopeModel = new GyroscopeModel(gyroModel);
    /* TODO ANOMALY FINDER WITH ISSAM */
    /*anomalyModel = new AnomalyModel(anomalyModel)*/
	featuresCalculator = new FeaturesCalculator();
}

double Smartstep::Inference(Sensors* VectData, int threshold){

    Features *features=featuresCalculator->computeFeatures(VectData, threshold);
    // acc = [np.median(mag80a), valley80a, stats.kurtosis(mag30a), peak50a, stats.skew(mag5a), peak80a, domfreq[0, 0], calc_index_min(mag30a_nomean)]

    vector<float> inputValuesAcc = {
            (float) features->get_acc_median_win80(),
            (float) features->get_acc_valley_prominences_win80(),
            (float) features->get_acc_kurtosis_win30(),
            (float) features->get_acc_peak_prominences_win50(),
            (float) features->get_acc_skewness_win5(),
            (float) features->get_acc_peak_prominences_win80(),
            (float) features->get_acc_dominant_frequency(),
            (float) features->get_acc_minElement_win30()
        };

    vector<float> probabilitiesAcc = accelerometerModel->runModel(inputValuesAcc);

    vector<float> inputValuesGyro = {
            (float) features->get_gyro_skewness_win70(),
            (float) features->get_gyro_skewness_win30(),
            (float) features->get_gyro_maxElement_win60(),
            (float) features->get_gyro_sma_win80(),
            (float) features->get_gyro_variance_win20(),
            (float) features->get_gyro_maxValue_win70(),
            (float) features->get_gyro_valley_prominences_win80(),
            (float) features->get_gyro_max_frequency()
        };
    vector<float> probabilitiesGyro = gyroscopeModel->runModel(inputValuesGyro);

    /* TODO ANOMALY FINDER WITH ISSAM */
    /*vector<float> anomalyFinder = anomalyModel->runModel(inputValues)*/





    StepProbabilities *stepProbabilities = new StepProbabilities();
    stepProbabilities->set_accProb0(probabilitiesAcc.at(0));
    stepProbabilities->set_accProb1(probabilitiesAcc.at(1));
    stepProbabilities->set_gyroProb0(probabilitiesGyro.at(0));
    stepProbabilities->set_gyroProb1(probabilitiesGyro.at(1));

    //Step instant
    /* TODO ANOMALY FINDER WITH ISSAM */
    /*if ((stepProbabilities->get_accProb1() > 0.5 && anomalyFinder = 0)|| (stepProbabilities->get_gyroProb1() > 0.5 && anomalyFinder = 0))*/
    if (stepProbabilities->get_accProb1() > 0.5 || stepProbabilities->get_gyroProb1() > 0.5) {
        stepProbabilities->set_isStepInstant(true);

    }
    return (double)  stepProbabilities->get_isStepInstant();
}
