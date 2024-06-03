#include <iomanip>
#include "FeaturesCalculatorVertical.hpp"
#include <android/log.h>
#define LOG_TAG "Calculator"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

const int _threshold = 80;

const int _start_wind5 = 62;
const int _start_wind20 = 54;
const int _start_wind30 = 49;
const int _start_wind50 = 39;
const int _start_wind60 = 34;
const int _start_wind70 = 29;
const int _start_wind80 = 24;

const int _window_size5 = 67;
const int _window_size20 = 75;
const int _window_size30 = 80;
const int _window_size50 = 90;
const int _window_size60 = 95;
const int _window_size70 = 100;
const int _window_size80 = 105;

// const int window_slide_step = 1;
// const int window_freq = 129;

// Default constructor
FeaturesCalculatorVertical::FeaturesCalculatorVertical() :_time(_threshold),_nb_step(_threshold),_baro(_threshold), _baro_norm(_threshold),_acc_norm(_threshold), _gyro_norm(_threshold), _acc_norm_nf(_threshold), _gyro_norm_nf(_threshold), _acc_x(_threshold), _acc_y(_threshold), _acc_z(_threshold),
                                          _gyro_x(_threshold), _gyro_y(_threshold), _gyro_z(_threshold),_mag_norm(_threshold), _mag_x(_threshold), _mag_y(_threshold), _mag_z(_threshold),_mag_norm_nf(_threshold) {};

// Destructor
FeaturesCalculatorVertical::~FeaturesCalculatorVertical () {}

// Extract a sub vector
vector<double> FeaturesCalculatorVertical::extractVector(const vector<double>& vectorData, int firstPoint, int lastPoint){
    vector<double> result;
    for (int iVec = firstPoint; iVec < lastPoint; iVec++) {
        result.push_back(vectorData[iVec]);
    }

    return result;
}

void FeaturesCalculatorVertical::rotateAndInsert(vector<double>& vectorData, double dataToInsert) {

    vectorData.push_back(dataToInsert);
}


void FeaturesCalculatorVertical::rotateAndInsert(vector<int>& vectorData, int dataToInsert) {

    vectorData.push_back(dataToInsert);
}


vector<double> FeaturesCalculatorVertical::Insert(vector<double>& vectorData, double dataToInsert) {
    vectorData.push_back(dataToInsert);

    return  vectorData;
}


// Scalar product
vector<double> FeaturesCalculatorVertical::scalarProduct(const vector<double>& vectorData, double scalar) {
    vector<double> result(vectorData.size());
    for(int iVec = 0; iVec < vectorData.size(); ++iVec) {
        result[iVec] = scalar * vectorData[iVec];
    }

    return result;
}

double FeaturesCalculatorVertical::mean(const vector<double>& vectorData) {
    double sum=0;
    for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {
        sum=sum+vectorData[iVec] ;

    }

    return sum/vectorData.size();

}

double FeaturesCalculatorVertical::computeNorm(const vector<double>& vectorData) {

    double sum =0;

    for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {

        sum=sum+pow(abs(vectorData[iVec]),2);

    }

    return sqrt(sum);
}




double FeaturesCalculatorVertical::computeVariance(const vector<double>& vectorData, const double& vectorDataMean, int windowSize) {
    double variance = 0.0;

    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        variance += pow( vectorData[iVec] - vectorDataMean, 2 );
    }
    return variance / (double) vectorData.size();
}

double FeaturesCalculatorVertical::kurtosis(const vector<double>& vectorData){
    double kurtosis = 0.0;
    double means = mean(vectorData);
    double variance = computeVariance(vectorData, means, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        kurtosis += pow( (vectorData[iVec] - means),4);
    }
    return (kurtosis / pow(variance, 2))/(double) vectorData.size() - 3.0;
}


double FeaturesCalculatorVertical::arc(const vector<double>& vector_x,const vector<double>& vector_y,const vector<double>& vector_z){

    vector<double> vector_sqrt_pow;

    for (int iVec = 0; iVec < vector_x.size(); ++iVec) {

        vector_sqrt_pow.push_back(sqrt(pow(vector_x[iVec],2)+pow(vector_y[iVec],2)+pow(vector_z[iVec],2)));

    }
    return mean(vector_sqrt_pow);

}

double FeaturesCalculatorVertical::aad(const vector<double>& vectorData){

    double means = mean(vectorData);

    vector<double> vector_absolue;

    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        vector_absolue.push_back(abs(vectorData[iVec]-means));
    }

    return mean(vector_absolue);

}

double FeaturesCalculatorVertical::std(const vector<double>& vectorData){

    double variance = computeVariance(vectorData, mean(vectorData), 0);

    return sqrt(variance);

}


double FeaturesCalculatorVertical::skewness(const vector<double>& vectorData){

    double skewness = 0.0;
    double means = mean(vectorData);
    double variance = computeVariance(vectorData, means, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        skewness += pow( (vectorData[iVec] - means), 3);
    }
    return (skewness/pow(variance,1.5)) /(double) vectorData.size();
}

vector<double> FeaturesCalculatorVertical::normalization(const std::vector<double>& vectorData) {
    double norm = computeNorm(vectorData);

    std::vector<double> normalized_vector;
    normalized_vector.reserve(vectorData.size());
    for (const auto& value : vectorData) {
        normalized_vector.push_back(value / norm);
    }
    return normalized_vector;
}

vector<double> FeaturesCalculatorVertical::cutVector(const vector<double>& inputVector , double percent) {
    vector<double> recoverVector;

    size_t size = inputVector.size();

    size_t halfSize = round(size *percent);

    for (size_t i = halfSize; i < size; ++i) {
        recoverVector.push_back(inputVector[i]);
    }

    return recoverVector;
}

double FeaturesCalculatorVertical::computeNorm(const double& x, const double& y, const double& z) {
    return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
}




double FeaturesCalculatorVertical::moyennePremierHalf(const vector<double>& vecteur) {
    size_t taille_demi = vecteur.size() / 2;

    double somme = std::accumulate(vecteur.begin(), vecteur.begin() + taille_demi, 0.0);

    double moyenne = somme / taille_demi;

    return moyenne;
}

double FeaturesCalculatorVertical::moyenneSecondHalf(const vector<double>& vecteur) {

    size_t taille_demi = vecteur.size() / 2;

    double somme = std::accumulate(vecteur.begin() + taille_demi, vecteur.end(), 0.0);

    double moyenne = somme / taille_demi;

    return moyenne;
}

double FeaturesCalculatorVertical::differenceMeanHalf(const vector<double>& vecteur) {

    double moyennePremier = moyennePremierHalf(vecteur);
    double moyenneSecond = moyenneSecondHalf(vecteur);

    double difference = moyennePremier - moyenneSecond;

    return difference;
}

double FeaturesCalculatorVertical::calculerPente(const vector<double>& y) {
    if (y.empty()) {
        return 0.0;
    }

    double moyenne_x = 0.0;
    for (size_t i = 0; i < y.size(); ++i) {
        moyenne_x += i;
    }
    moyenne_x /= y.size();

    double numerateur = 0.0, denominateur = 0.0;
    for (size_t i = 0; i < y.size(); ++i) {
        numerateur += (i - moyenne_x) * (y[i] - mean(y));
        denominateur += (i - moyenne_x) * (i - moyenne_x);
    }

    if (denominateur == 0) {
        return 0.0;
    }
    return numerateur / denominateur;
}


double FeaturesCalculatorVertical::rms(const std::vector<double>& donnees) {

    double somme_carres = 0.0;
    for (double valeur : donnees) {
        somme_carres += valeur * valeur;
    }

    double rms = std::sqrt(somme_carres / donnees.size());

    return rms;
}



bool FeaturesCalculatorVertical::computeSensor(Sensors* sensorsData) {


    rotateAndInsert(_acc_x, sensorsData->get_acc_x());
    rotateAndInsert(_acc_y, sensorsData->get_acc_y());
    rotateAndInsert(_acc_z, sensorsData->get_acc_z());
    rotateAndInsert(_gyro_x, sensorsData->get_gyro_x());
    rotateAndInsert(_gyro_y, sensorsData->get_gyro_y());
    rotateAndInsert(_gyro_z, sensorsData->get_gyro_z());
    rotateAndInsert(_mag_x, sensorsData->get_mag_x());
    rotateAndInsert(_mag_y, sensorsData->get_mag_y());
    rotateAndInsert(_mag_z, sensorsData->get_mag_z());
    rotateAndInsert(_baro, sensorsData->get_baro());
    rotateAndInsert(_nb_step,sensorsData->get_step());
    rotateAndInsert(_time, sensorsData->get_time());

    double time_diff=_time.back()-_time[0];

    int step_diff=_nb_step.back()-_nb_step[0];

    LOGD("Time_diff: %f", time_diff);

    if (time_diff>=3 || step_diff>=2){


        time_diff=0.0;
        step_diff=0;

        return true;

    }

    else{

        return false;
    }

}

Features* FeaturesCalculatorVertical::computeFeatureVertical() {

    for (int i=0;i<_acc_x.size();i++){

        rotateAndInsert(_acc_norm,computeNorm(_acc_x[i],_acc_y[i],_acc_z[i]));
        rotateAndInsert(_gyro_norm,computeNorm(_gyro_x[i],_gyro_y[i],_gyro_z[i]));
        rotateAndInsert(_mag_norm,computeNorm(_mag_x[i],_mag_y[i],_mag_z[i]));
    };


    Features* features = new Features();

    features->set_acc_x_arc(arc(normalization(_acc_x),normalization(_acc_y),normalization(_acc_z)));

    features->set_gyr_x_arc(arc(normalization(_gyro_x),normalization(_gyro_y),normalization(_gyro_z)));

    features->set_mag_x_arc(arc(normalization(_mag_x),normalization(_mag_y),normalization(_mag_z)));

    features->set_acc_x_aad(aad(normalization(_acc_x)));
    features->set_acc_x_mean(mean(normalization(_acc_x)));
    features->set_acc_x_std(std(normalization(_acc_x)));
    features->set_acc_x_kurt(kurtosis(normalization(_acc_x)));
    features->set_acc_x_skew(skewness(normalization(_acc_x)));

    features->set_acc_y_aad(aad(normalization(_acc_y)));
    features->set_acc_y_mean(mean(normalization(_acc_y)));
    features->set_acc_y_std(std(normalization(_acc_y)));
    features->set_acc_y_kurt(kurtosis(normalization(_acc_y)));
    features->set_acc_y_skew(skewness(normalization(_acc_y)));

    features->set_acc_z_aad(aad(normalization(_acc_z)));
    features->set_acc_z_mean(mean(normalization(_acc_z)));
    features->set_acc_z_std(std(normalization(_acc_z)));
    features->set_acc_z_kurt(kurtosis(normalization(_acc_z)));
    features->set_acc_z_skew(skewness(normalization(_acc_z)));

    features->set_gyr_x_aad(aad(normalization(_gyro_x)));
    features->set_gyr_x_mean(mean(normalization(_gyro_x)));
    features->set_gyr_x_std(std(normalization(_gyro_x)));
    features->set_gyr_x_kurt(kurtosis(normalization(_gyro_x)));
    features->set_gyr_x_skew(skewness(normalization(_gyro_x)));

    features->set_gyr_y_aad(aad(normalization(_gyro_y)));
    features->set_gyr_y_mean(mean(normalization(_gyro_y)));
    features->set_gyr_y_std(std(normalization(_gyro_y)));
    features->set_gyr_y_kurt(kurtosis(normalization(_gyro_y)));
    features->set_gyr_y_skew(skewness(normalization(_gyro_y)));

    features->set_gyr_z_aad(aad(normalization(_gyro_z)));
    features->set_gyr_z_mean(mean(normalization(_gyro_z)));
    features->set_gyr_z_std(std(normalization(_gyro_z)));
    features->set_gyr_z_kurt(kurtosis(normalization(_gyro_z)));
    features->set_gyr_z_skew(skewness(normalization(_gyro_z)));

    features->set_mag_x_aad(aad(normalization(_mag_x)));
    features->set_mag_x_mean(mean(normalization(_mag_x)));
    features->set_mag_x_std(std(normalization(_mag_x)));
    features->set_mag_x_kurt(kurtosis(normalization(_mag_x)));
    features->set_mag_x_skew(skewness(normalization(_mag_x)));

    features->set_mag_y_aad(aad(normalization(_mag_y)));
    features->set_mag_y_mean(mean(normalization(_mag_y)));
    features->set_mag_y_std(std(normalization(_mag_y)));
    features->set_mag_y_kurt(kurtosis(normalization(_mag_y)));
    features->set_mag_y_skew(skewness(normalization(_mag_y)));

    features->set_mag_z_aad(aad(normalization(_mag_z)));
    features->set_mag_z_mean(mean(normalization(_mag_z)));
    features->set_mag_z_std(std(normalization(_mag_z)));
    features->set_mag_z_kurt(kurtosis(normalization(_mag_z)));
    features->set_mag_z_skew(skewness(normalization(_mag_z)));
    features->set_baro_aad(aad(normalization(_baro)));
    features->set_baro_mean(mean(normalization(_baro)));
    features->set_baro_std(std(normalization(_baro)));
    features->set_baro_kurt(kurtosis(normalization(_baro)));
    features->set_baro_skew(skewness(normalization(_baro)));

    features->set_nb_step(_nb_step.back()-_nb_step[0]);

    features->set_acc_norm_aad(aad(_acc_norm));
    features->set_acc_norm_mean(mean(_acc_norm));
    features->set_acc_norm_std(std(_acc_norm));
    features->set_acc_norm_kurt(kurtosis(_acc_norm));
    features->set_acc_norm_skew(skewness(_acc_norm));

    features->set_gyro_norm_aad(aad(_gyro_norm));
    features->set_gyro_norm_mean(mean(_gyro_norm));
    features->set_gyro_norm_std(std(_gyro_norm));
    features->set_gyro_norm_kurt(kurtosis(_gyro_norm));
    features->set_gyro_norm_skew(skewness(_gyro_norm));

    features->set_mag_norm_aad(aad(_mag_norm));
    features->set_mag_norm_mean(mean(_mag_norm));
    features->set_mag_norm_std(std(_mag_norm));
    features->set_mag_norm_kurt(kurtosis(_mag_norm));
    features->set_mag_norm_skew(skewness(_mag_norm));

    _acc_x.clear();
    _acc_y.clear();
    _acc_z.clear();
    _mag_x.clear();
    _mag_y.clear();
    _mag_z.clear();
    _gyro_x.clear();
    _gyro_y.clear();
    _gyro_z.clear();
    _baro.clear();
    _time.clear();
    _nb_step.clear();

    return features;

}

