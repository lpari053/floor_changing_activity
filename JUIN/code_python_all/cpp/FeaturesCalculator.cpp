#include <iomanip>
#include "FeaturesCalculator.hpp"

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
FeaturesCalculator::FeaturesCalculator() :_nb_step(_threshold),_baro(_threshold), _baro_norm(_threshold),_acc_norm(_threshold), _gyro_norm(_threshold), _acc_norm_nf(_threshold), _gyro_norm_nf(_threshold), _acc_x(_threshold), _acc_y(_threshold), _acc_z(_threshold),
 _gyro_x(_threshold), _gyro_y(_threshold), _gyro_z(_threshold),_mag_norm(_threshold), _mag_x(_threshold), _mag_y(_threshold), _mag_z(_threshold),_mag_norm_nf(_threshold) {};

// Destructor
FeaturesCalculator::~FeaturesCalculator () {}


/**
 * @brief Extract in a vector a sub vector according to a start point and end point
 * @param const vector<double>& vectorData The vector to be extract.
 * @param int firstPoint , index in the vectorData to begin the the extraction
 * @param int lastPoint , index in the vectorData to end the the extraction
 * @return A vector that is the original vectorData but reduce with an extrcation between firstPoint and LastPoint.
 */
vector<double> FeaturesCalculator::extractVector(const vector<double>& vectorData, int firstPoint, int lastPoint){
    vector<double> result;
    for (int iVec = firstPoint; iVec < lastPoint; iVec++) {
        result.push_back(vectorData[iVec]);
    }
    
    return result;
}

/**
 * @brief Insert a data at the end of a vector , a double data
 * @param const vector<double>& vectorData The vector to be extract.
 * @param double dataToInsert double to insert at the end of the vector
 */
void FeaturesCalculator::rotateAndInsert(vector<double>& vectorData, double dataToInsert) {

    vectorData.push_back(dataToInsert);
}

/**
 * @brief Insert a data at the end of a vector , a int data
 * @param const vector<int>& vectorData The vector to be extract.
 * @param int dataToInsert double to insert at the end of the vector
 */
void FeaturesCalculator::rotateAndInsert(vector<int>& vectorData, int dataToInsert) {

    vectorData.push_back(dataToInsert);
}

/**
 * @brief Insert a data at the end of a vector , a double data
 * @param const vector<double>& vectorData The vector to be extract.
 * @param double dataToInsert double to insert at the end of the vector
 * @return const vector<double>& vectorData with the addition at the end of the dataToInsert
 */
vector<double> FeaturesCalculator::Insert(vector<double>& vectorData, double dataToInsert) {
    vectorData.push_back(dataToInsert);
    
    return  vectorData;
}


/**
 * @brief Extract in a vector a sub vector according to a start point and end point
 * @param const vector<double>& vectorData The vector to be extract.
 * @param double dataToInsert double to insert at the end of the vector
 * @return const vector<double>& vectorData with the addition at the end of the dataToInsert
 */
vector<double> FeaturesCalculator::scalarProduct(const vector<double>& vectorData, double scalar) {
    vector<double> result(vectorData.size());
    for(int iVec = 0; iVec < vectorData.size(); ++iVec) {
        result[iVec] = scalar * vectorData[iVec];
    }
    
    return result;
}
/**
 * @brief Calculate the mean of a vector
 * @param const vector<double>& vectorData The vector that we want the mean of.
 * @return double Mean of the vector data
 */
double FeaturesCalculator::mean(const vector<double>& vectorData) {
double sum=0;
for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {
sum=sum+vectorData[iVec] ;

    }

    return sum/vectorData.size();

}
/**
 * @brief Calculate the norm of a vector
 * @param const vector<double>& vectorData The vector that we want the norm of.
 * @return double Norm of the vector data
 */
double FeaturesCalculator::computeNorm(const vector<double>& vectorData) {

    double sum =0;

for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {

sum=sum+pow(abs(vectorData[iVec]),2);

    }

    return sqrt(sum);
}


/**
 * @brief Calculate the variance of a vector
 * @param const vector<double>& vectorData The vector that we want the variance of.
 * @return double Variance of the vector data
 */
double FeaturesCalculator::computeVariance(const vector<double>& vectorData, const double& vectorDataMean, int windowSize) {
    double variance = 0.0;
    
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        variance += pow( vectorData[iVec] - vectorDataMean, 2 );
    }
    return variance / (double) vectorData.size();
}
/**
 * @brief Calculate the kurtosis of a vector
 * @param const vector<double>& vectorData The vector that we want the kurtosis of.
 * @return double Kurtosis of the vector data
 */
double FeaturesCalculator::kurtosis(const vector<double>& vectorData){
    double kurtosis = 0.0;
    double means = mean(vectorData);
    double variance = computeVariance(vectorData, means, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        kurtosis += pow( (vectorData[iVec] - means),4);
    }
    return (kurtosis / pow(variance, 2))/(double) vectorData.size() - 3.0;
}

/**
 * @brief Calculate the arc of a vector
 * @param const vector<double>& vectorData The vector that we want the arc  of.
 * @return double Arc  of the vector data
 */
double FeaturesCalculator::arc(const vector<double>& vector_x,const vector<double>& vector_y,const vector<double>& vector_z){

vector<double> vector_sqrt_pow;

for (int iVec = 0; iVec < vector_x.size(); ++iVec) {

        vector_sqrt_pow.push_back(sqrt(pow(vector_x[iVec],2)+pow(vector_y[iVec],2)+pow(vector_z[iVec],2)));

    }
    return mean(vector_sqrt_pow);

}
/**
 * @brief Calculate the aad of a vector
 * @param const vector<double>& vectorData The vector that we want the aad  of.
 * @return double Aad  of the vector data
 */
double FeaturesCalculator::aad(const vector<double>& vectorData){

    double means = mean(vectorData);

    vector<double> vector_absolue;

    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        vector_absolue.push_back(abs(vectorData[iVec]-means));
    }

    return mean(vector_absolue);

}

/**
 * @brief Calculate the std of a vector
 * @param const vector<double>& vectorData The vector that we want the std of.
 * @return double std  of the vector data
 */

double FeaturesCalculator::std(const vector<double>& vectorData){
    
    double variance = computeVariance(vectorData, mean(vectorData), 0);

return sqrt(variance);

}

/**
 * @brief Calculate the skewness of a vector
 * @param const vector<double>& vectorData The vector that we want the skewness of.
 * @return double Skewness  of the vector data
 */
double FeaturesCalculator::skewness(const vector<double>& vectorData){
    
    double skewness = 0.0;
    double means = mean(vectorData);
    double variance = computeVariance(vectorData, means, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        skewness += pow( (vectorData[iVec] - means), 3);
    }
    return (skewness/pow(variance,1.5)) /(double) vectorData.size();
}

/**
 * @brief Noramlize all the element of a vector 
 * @param const vector<double>& vectorData The vector that we want the skewness of.
 * @return normalized vector
 */
vector<double> FeaturesCalculator::normalization(const std::vector<double>& vectorData) {
    double norm = computeNorm(vectorData);
    
    std::vector<double> normalized_vector;
    normalized_vector.reserve(vectorData.size());
    for (const auto& value : vectorData) {
        normalized_vector.push_back(value / norm);
    }
    return normalized_vector;
}


/**
 * @brief Calculate the norm xyz
 * @param const vector<double>& vectorData The vector that we want the the norm xyz of.
 * @return double  norm xyz  of the vector data
 */
double FeaturesCalculator::computeNorm(const double& x, const double& y, const double& z) {
    return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
}




double FeaturesCalculator::moyennePremierHalf(const vector<double>& vecteur) {
    size_t taille_demi = vecteur.size() / 2;

    double somme = std::accumulate(vecteur.begin(), vecteur.begin() + taille_demi, 0.0);

    double moyenne = somme / taille_demi;

    return moyenne;
}

double FeaturesCalculator::moyenneSecondHalf(const vector<double>& vecteur) {

    size_t taille_demi = vecteur.size() / 2;

    double somme = std::accumulate(vecteur.begin() + taille_demi, vecteur.end(), 0.0);

    double moyenne = somme / taille_demi;

    return moyenne;
}

double FeaturesCalculator::differenceMeanHalf(const vector<double>& vecteur) {

    double moyennePremier = moyennePremierHalf(vecteur);
    double moyenneSecond = moyenneSecondHalf(vecteur);

    double difference = moyennePremier - moyenneSecond;

    return difference;
}

double FeaturesCalculator::calculerPente(const vector<double>& y) {
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

/**
 * @brief Calculate the rmd
 * @param const vector<double>& vectorData The vector that we want the rmd of.
 * @return double rms  of the vector data
 */
double FeaturesCalculator::rms(const std::vector<double>& donnees) {

    double somme_carres = 0.0;
    for (double valeur : donnees) {
        somme_carres += valeur * valeur;
    }

    double rms = std::sqrt(somme_carres / donnees.size());

    return rms;
}


/**
 * @brief Create the vector data for each sensor 
 * @param Sensor Sensor data for each data set up.
 */
void* FeaturesCalculator::computeSensor(Sensors* sensorsData) {


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


}
/**
 * @brief Create the vector data for each sensor 
 * @return Features  Calculate and Set up the feature for each sensor.
 */ 
Features* FeaturesCalculator::computeFeatureVertical() {

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


return features;

}

