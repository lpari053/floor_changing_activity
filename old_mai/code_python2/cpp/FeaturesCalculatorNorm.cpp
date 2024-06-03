#include <iomanip>
#include "FeaturesCalculatorNorm.hpp"

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
FeaturesCalculatorNorm::FeaturesCalculatorNorm() :_nb_step(_threshold),_baro(_threshold), _baro_norm(_threshold),_acc_norm(_threshold), _gyro_norm(_threshold), _acc_norm_nf(_threshold), _gyro_norm_nf(_threshold), _acc_x(_threshold), _acc_y(_threshold), _acc_z(_threshold),
 _gyro_x(_threshold), _gyro_y(_threshold), _gyro_z(_threshold),_mag_norm(_threshold), _mag_x(_threshold), _mag_y(_threshold), _mag_z(_threshold),_mag_norm_nf(_threshold) {};

// Destructor
FeaturesCalculatorNorm::~FeaturesCalculatorNorm () {}

// Extract a sub vector
vector<double> FeaturesCalculatorNorm::extractVector(const vector<double>& vectorData, int firstPoint, int lastPoint){
    vector<double> result;
    for (int iVec = firstPoint; iVec < lastPoint; iVec++) {
        result.push_back(vectorData[iVec]);
    }
    
    return result;
}

void FeaturesCalculatorNorm::rotateAndInsert(vector<double>& vectorData, double dataToInsert,int threshold,int taille_input) {

if (threshold >= taille_input) {

    rotate(vectorData.begin(), vectorData.begin() + 1, vectorData.end());
    vectorData.back() = dataToInsert;

}

else{

    vectorData.push_back(dataToInsert);
}

}

void FeaturesCalculatorNorm::rotateAndInsert(vector<int>& vectorData, double dataToInsert,int threshold,int taille_input) {

if (threshold >= taille_input) {

    rotate(vectorData.begin(), vectorData.begin() + 1, vectorData.end());
    vectorData.back() = dataToInsert;

}

else{

    vectorData.push_back(dataToInsert);
}

}


// Rotate and insert
vector<double> FeaturesCalculatorNorm::Insert(vector<double>& vectorData, double dataToInsert) {
    vectorData.push_back(dataToInsert);
    
    return  vectorData;
}


// Scalar product
vector<double> FeaturesCalculatorNorm::scalarProduct(const vector<double>& vectorData, double scalar) {
    vector<double> result(vectorData.size());
    for(int iVec = 0; iVec < vectorData.size(); ++iVec) {
        result[iVec] = scalar * vectorData[iVec];
    }
    
    return result;
}

int FeaturesCalculatorNorm::first_peak_index(const vector<double>& vectorData) {

std::vector<Complex> x(vectorData.size());

    for (size_t i = 0; i < vectorData.size(); ++i) {
        x[i].real = vectorData[i];
        x[i].imag = 0;
    }

    fft(x);

    std::vector<double> spectrum = magnitude(x);

    int peakIndex = firstPeakIndex(spectrum);

    return peakIndex;

}

double FeaturesCalculatorNorm::first_peak_value(const vector<double>& vectorData) {

std::vector<Complex> x(vectorData.size());

    for (size_t i = 0; i < vectorData.size(); ++i) {
        x[i].real = vectorData[i];
        x[i].imag = 0;
    }

    fft(x);

    std::vector<double> spectrum = magnitude(x);

    int peakValue = firstPeakValue(spectrum);

    return peakValue;

}

int FeaturesCalculatorNorm::second_peak_index(const vector<double>& vectorData) {

    const double SEARCH_WINDOW_FACTOR = 0.1; // Facteur pour déterminer la taille de la fenêtre de recherche

    int searchWindow = static_cast<int>(vectorData.size() * SEARCH_WINDOW_FACTOR);

    std::vector<Complex> x(vectorData.size());

    for (size_t i = 0; i < vectorData.size(); ++i) {
        x[i].real = vectorData[i];
        x[i].imag = 0;
    }

    fft(x);

    std::vector<double> spectrum = magnitude(x);

    // Recherche de l'indice du premier pic
    int firstPeakIndex = first_peak_index(spectrum);

    int searchStartIndex = max(0, firstPeakIndex - searchWindow);
    int searchEndIndex = min(static_cast<int>(spectrum.size()) - 1, firstPeakIndex + searchWindow);
    for (int i = searchStartIndex; i <= searchEndIndex; ++i) {
        spectrum[i] = 0.0;
    }

    // Recherche de l'indice du deuxième pic
    int secondPeakIndex = first_peak_index(spectrum);

    return secondPeakIndex;
}

double FeaturesCalculatorNorm::second_peak_value(const vector<double>& vectorData) {

    
    const double SEARCH_WINDOW_FACTOR = 0.1; // Facteur pour déterminer la taille de la fenêtre de recherche

    int searchWindow = static_cast<int>(vectorData.size() * SEARCH_WINDOW_FACTOR);

    std::vector<Complex> x(vectorData.size());

    for (size_t i = 0; i < vectorData.size(); ++i) {
        x[i].real = vectorData[i];
        x[i].imag = 0;
    }

    fft(x);

    std::vector<double> spectrum = magnitude(x);

    int firstPeakIndex = first_peak_index(spectrum);

    // Supprimer la zone autour du premier pic pour rechercher le deuxième pic
    int searchStartIndex = std::max(0, firstPeakIndex -  searchWindow);
    int searchEndIndex = std::min(static_cast<int>(spectrum.size()) - 1, firstPeakIndex +  searchWindow);
    for (int i = searchStartIndex; i <= searchEndIndex; ++i) {
        spectrum[i] = 0.0;
    }

    // Recherche de la valeur du deuxième pic
    double secondPeakValue = first_peak_value(spectrum);

    return secondPeakValue;
}


double FeaturesCalculatorNorm::mean(const vector<double>& vectorData) {
double sum=0;
for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {
sum=sum+vectorData[iVec] ;

    }

    return sum/vectorData.size();

}

double FeaturesCalculatorNorm::computeNorm(const vector<double>& vectorData) {

    double sum =0;

for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {

sum=sum+pow(abs(vectorData[iVec]),2);

    }


   
    return sqrt(sum);
}

double FeaturesCalculatorNorm::computeVariance(const vector<double>& vectorData, const double& vectorDataMean, int windowSize) {
    double variance = 0.0;
    
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        variance += pow( vectorData[iVec] - vectorDataMean, 2 );
    }
    return variance / (double) vectorData.size();
}

double FeaturesCalculatorNorm::kurtosis(const vector<double>& vectorData){
    double kurtosis = 0.0;
    double means = mean(vectorData);
    double variance = computeVariance(vectorData, means, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        kurtosis += pow( (vectorData[iVec] - means),4);
    }
    return (kurtosis / pow(variance, 2))/(double) vectorData.size() - 3.0;
}


double FeaturesCalculatorNorm::arc(const vector<double>& vector_x,const vector<double>& vector_y,const vector<double>& vector_z){

vector<double> vector_sqrt_pow;

for (int iVec = 0; iVec < vector_x.size(); ++iVec) {

        vector_sqrt_pow.push_back(sqrt(pow(vector_x[iVec],2)+pow(vector_y[iVec],2)+pow(vector_z[iVec],2)));

    }
    return mean(vector_sqrt_pow);

}

double FeaturesCalculatorNorm::aad(const vector<double>& vectorData){

    double means = mean(vectorData);

    vector<double> vector_absolue;

    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        vector_absolue.push_back(abs(vectorData[iVec]-means));
    }

    return mean(vector_absolue);

}

double FeaturesCalculatorNorm::std(const vector<double>& vectorData){
    
    double variance = computeVariance(vectorData, mean(vectorData), 0);

return sqrt(variance);

}


double FeaturesCalculatorNorm::skewness(const vector<double>& vectorData){
    
    double skewness = 0.0;
    double means = mean(vectorData);
    double variance = computeVariance(vectorData, means, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        skewness += pow( (vectorData[iVec] - means), 3);
    }
    return (skewness/pow(variance,1.5)) /(double) vectorData.size();
}

vector<double> FeaturesCalculatorNorm::normalization(const std::vector<double>& vectorData) {
    double norm = computeNorm(vectorData);
    
    std::vector<double> normalized_vector;
    normalized_vector.reserve(vectorData.size());
    for (const auto& value : vectorData) {
        normalized_vector.push_back(value / norm);
    }
    return normalized_vector;
}

vector<double> FeaturesCalculatorNorm::cutVector(const vector<double>& inputVector , double percent) {
    vector<double> recoverVector;

    size_t size = inputVector.size();

    size_t halfSize = round(size *percent);

    for (size_t i = halfSize; i < size; ++i) {
        recoverVector.push_back(inputVector[i]);
    }

    return recoverVector;
}

void FeaturesCalculatorNorm::cutFeatures(Sensors* sensorsData, double percent) {

    cutVector(_acc_x,percent);
    cutVector(_acc_y,percent);
    cutVector(_acc_z,percent);

    cutVector(_mag_x,percent);
    cutVector(_mag_y,percent);
    cutVector(_mag_z,percent);

    cutVector(_gyro_x,percent);
    cutVector(_gyro_y,percent);
    cutVector(_gyro_z,percent);

    cutVector(_baro,percent);
    
}

double FeaturesCalculatorNorm::computeNorm(const double& x, const double& y, const double& z) {
    return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
}


double FeaturesCalculatorNorm::moyennePremierHalf(const vector<double>& vecteur) {
    size_t taille_demi = vecteur.size() / 2;

    double somme = std::accumulate(vecteur.begin(), vecteur.begin() + taille_demi, 0.0);

    double moyenne = somme / taille_demi;

    return moyenne;
}

double FeaturesCalculatorNorm::moyenneSecondHalf(const vector<double>& vecteur) {

    size_t taille_demi = vecteur.size() / 2;

    double somme = std::accumulate(vecteur.begin() + taille_demi, vecteur.end(), 0.0);

    double moyenne = somme / taille_demi;

    return moyenne;
}

double FeaturesCalculatorNorm::differenceMeanHalf(const vector<double>& vecteur) {

    double moyennePremier = moyennePremierHalf(vecteur);
    double moyenneSecond = moyenneSecondHalf(vecteur);

    double difference = moyennePremier - moyenneSecond;

    return difference;
}

double FeaturesCalculatorNorm::calculerPente(const vector<double>& y) {
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


double FeaturesCalculatorNorm::rms(const std::vector<double>& donnees) {

    double somme_carres = 0.0;
    for (double valeur : donnees) {
        somme_carres += valeur * valeur;
    }

    double rms = std::sqrt(somme_carres / donnees.size());

    return rms;
}



Features* FeaturesCalculatorNorm::computeFeatures(Sensors* sensorsData, int threshold,int taille_input) {
    Features* features = new Features();


    rotateAndInsert(_acc_x, sensorsData->get_acc_x(),threshold,taille_input);
    rotateAndInsert(_acc_y, sensorsData->get_acc_y(),threshold,taille_input);
    rotateAndInsert(_acc_z, sensorsData->get_acc_z(),threshold,taille_input);
    rotateAndInsert(_gyro_x, sensorsData->get_gyro_x(),threshold,taille_input);
    rotateAndInsert(_gyro_y, sensorsData->get_gyro_y(),threshold,taille_input);
    rotateAndInsert(_gyro_z, sensorsData->get_gyro_z(),threshold,taille_input);
    rotateAndInsert(_mag_x, sensorsData->get_mag_x(),threshold,taille_input);
    rotateAndInsert(_mag_y, sensorsData->get_mag_y(),threshold,taille_input);
    rotateAndInsert(_mag_z, sensorsData->get_mag_z(),threshold,taille_input);
    rotateAndInsert(_baro, sensorsData->get_baro(),threshold,taille_input);

    rotateAndInsert(_nb_step,sensorsData->get_step(),threshold,taille_input);


    for (int k = 0; k < taille_input; ++k) {
        double norm_acc=computeNorm(_acc_x[k],_acc_y[k],_acc_z[k]);
        double norm_gyro=computeNorm(_gyro_x[k],_gyro_y[k],_gyro_z[k]);
        double norm_mag=computeNorm(_mag_x[k],_mag_y[k],_mag_z[k]);
        rotateAndInsert(_acc_norm,norm_acc,threshold,taille_input);
        rotateAndInsert(_gyro_norm,norm_acc,threshold,taille_input);
        rotateAndInsert(_mag_norm,norm_acc,threshold,taille_input);
    }


    if (threshold >= taille_input) {


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
        
        features->set_nb_step(_nb_step.back()-_nb_step[0]);

    }
    return features;
}

