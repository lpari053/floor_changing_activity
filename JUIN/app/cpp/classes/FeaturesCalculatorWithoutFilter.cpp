//
//  Features.cpp
//  labcom
//
//  Created by Yohann Tschudi on 15/02/2022.
//

#include <iomanip>
#include "FeaturesCalculatorWithoutFilter.hpp"
#include "tbb/task_group.h"
tbb::task_group g2;

const int _threshold = 129; // N timestamp minimum à 100Hz

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
FeaturesCalculatorWithoutFilter::FeaturesCalculatorWithoutFilter() : _acc_norm(_threshold), _gyro_norm(_threshold), _acc_norm_nf(_threshold), _gyro_norm_nf(_threshold), _acc_x(_threshold), _acc_y(_threshold), _acc_z(_threshold), _gyro_x(_threshold), _gyro_y(_threshold), _gyro_z(_threshold),
                                                                     _mag_norm(_threshold),_mag_x(_threshold), _mag_y(_threshold), _mag_z(_threshold),_mag_norm_nf(_threshold){};

// Destructor
FeaturesCalculatorWithoutFilter::~FeaturesCalculatorWithoutFilter () {}

// Extract a sub vector
vector<double> FeaturesCalculatorWithoutFilter::extractVector(const vector<double>& vectorData, int firstPoint, int lastPoint){
    vector<double> result;
    for (int iVec = firstPoint; iVec < lastPoint; iVec++) {
        result.push_back(vectorData[iVec]);
    }
    
    return result;
}

// Rotate and insert
void FeaturesCalculatorWithoutFilter::rotateAndInsert(vector<double>& vectorData, double dataToInsert) {
    // Simple rotation to the left
    rotate(vectorData.begin(), vectorData.begin() + 1, vectorData.end());
    vectorData.back() = dataToInsert;
}

// Maximum value of a vector
double FeaturesCalculatorWithoutFilter::getMaxValue(const vector<double>& vectorData){
    return *max_element(vectorData.begin(),vectorData.end());
}

// Element of the min value a vector -- Max or min ???? Pk enlever le mean ?
double FeaturesCalculatorWithoutFilter::getMinElement(const vector<double>& vectorData) {
    return min_element(vectorData.begin(),vectorData.end()) - vectorData.begin();
}

// Element of the max value of a vector -- Max or min ????
double FeaturesCalculatorWithoutFilter::getMaxElement(const vector<double>& vectorData) {
    return max_element(vectorData.begin(),vectorData.end()) - vectorData.begin();
}

// Middle of a vector
int FeaturesCalculatorWithoutFilter::findMiddle(const vector<double>& vectorData) {
    double mid = double(vectorData.size()/2.0);
    if(fmod(mid,2.0)!=0) {
        return int(mid - .5);
    } else {
        return int(mid);
    }
}
int FeaturesCalculatorWithoutFilter::findMiddle(const vector<int>& vectorData) {
    double mid = double(vectorData.size()/2.0);
    if(fmod(mid,2.0)!=0) {
        return int(mid - .5);
    } else {
        return int(mid);
    }
}

// Scalar product
vector<double> FeaturesCalculatorWithoutFilter::scalarProduct(const vector<double>& vectorData, double scalar) {
    vector<double> result(vectorData.size());
    for(int iVec = 0; iVec < vectorData.size(); ++iVec) {
        result[iVec] = scalar * vectorData[iVec];
    }
    
    return result;
}


// Mean
double FeaturesCalculatorWithoutFilter::computeMean(const vector<double>& vectorData) {
    return accumulate(begin(vectorData), end(vectorData), (double) 0.0) / (double) vectorData.size();
}

// Norm
double FeaturesCalculatorWithoutFilter::computeNorm(const double& x, const double& y, const double& z) {
    return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
}
double FeaturesCalculatorWithoutFilter::computeNorm(const vector<double>& vectorData) {
    return sqrt( pow(vectorData[0], 2) + pow(vectorData[1], 2) + pow(vectorData[2], 2) );
}

// SMA
double FeaturesCalculatorWithoutFilter::computeSMA(const vector<double>& vectorData) {
    double sma = 0.0;
    double meanVectorData = computeMean(vectorData);
    for (int iVec = 0; iVec < vectorData.size() ; ++iVec) {
        sma += abs(vectorData[iVec] - meanVectorData);
    }
    return sma;
}

// Variance
double FeaturesCalculatorWithoutFilter::computeVariance(const vector<double>& vectorData, const double& vectorDataMean, int windowSize) {
    double variance = 0.0;
    
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        variance += pow( vectorData[iVec] - vectorDataMean, 2 );
    }
    return variance / (double) vectorData.size();
}

// Lerp
double FeaturesCalculatorWithoutFilter::computeLerp(double minValue, double maxValue, double interpolationPoint) {
    return minValue + interpolationPoint * (maxValue - minValue);
}

// Quantile lerp
double FeaturesCalculatorWithoutFilter::computeQuantile(const vector<double>& vectorData) {
    const double prob = 0.5;
    
    if (vectorData.empty()) {
        return 0.0;
    }
    if (vectorData.size() == 1) {
        return vectorData[0];
    }
    
    vector<double> sortedVectorData = vectorData;
    sort(sortedVectorData.begin(), sortedVectorData.end());
    
    double sortedVectorData_Size = sortedVectorData.size();
    double sortedVectorData_Lerp = computeLerp(-0.5, sortedVectorData_Size - 0.5, prob);
    
    size_t left = max(int64_t(floor(sortedVectorData_Lerp)), int64_t(0));
    size_t right = min(int64_t(ceil(sortedVectorData_Lerp)), int64_t(sortedVectorData.size() - 1));
    
    double sortedVectorData_Left = sortedVectorData.at(left);
    double sortedVectorData_Right = sortedVectorData.at(right);
    
    return computeLerp(sortedVectorData_Left, sortedVectorData_Right, sortedVectorData_Lerp - sortedVectorData_Left);
}

// Kurtosis
double FeaturesCalculatorWithoutFilter::computeKurtosis(const vector<double>& vectorData){
    double kurtosis = 0.0;
    double mean = computeMean(vectorData);
    double variance = computeVariance(vectorData, mean, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        kurtosis += pow( (vectorData[iVec] - mean),4);
    }
    return (kurtosis / pow(variance, 2))/(double) vectorData.size() - 3.0;
}

// Skewness
double FeaturesCalculatorWithoutFilter::computeSkewness(const vector<double>& vectorData){
    
    double skewness = 0.0;
    double mean = computeMean(vectorData);
    double variance = computeVariance(vectorData, mean, 0);
    for (int iVec = 0; iVec < vectorData.size(); ++iVec) {
        skewness += pow( (vectorData[iVec] - mean), 3);
    }
    return (skewness/pow(variance,1.5)) /(double) vectorData.size();
}

// Prominence
double FeaturesCalculatorWithoutFilter::computeProminence(const vector<double>& vectorData, double extrema, int first, int last) {
    
    // Initialize parameters
    double prominence = 50;
    vector<double> vecLeft;
    vector<double> vecRight;
    double baseLeft;
    double baseRight;
    size_t maxLeft;
    size_t maxRight;
    vector<double> scaledVecData = scalarProduct(vectorData, extrema);
    vector<double> extractedData = extractVector(scaledVecData, first, last);
    
    // Get vector containing peaks
    PeakFinder* peakfinder = new PeakFinder();
    vector<int> vecPeaks = peakfinder->findPeaks(extractedData);
    
    // Compute parameters
    int middleVecPeaks = findMiddle(vecPeaks);
    size_t extractedData_Size = extractedData.size();
    
    if(vecPeaks.size() > 0) {
        // Find left min
        vecLeft = extractVector(extractedData, 0, vecPeaks[middleVecPeaks] + 1);
        maxLeft = getMaxElement(vecLeft);
        
        if (maxLeft == vecPeaks[middleVecPeaks]) {
            baseLeft = extractedData[getMinElement(vecLeft)];
        } else {
            size_t iteratorMin = vecLeft.size() - 1;
            while(iteratorMin > 0){
                iteratorMin--;
                if(extractedData[iteratorMin] > extractedData[vecPeaks[middleVecPeaks]]){
                    maxLeft = iteratorMin;
                    break;
                }
            }
            vecLeft = extractVector(extractedData, (int)maxLeft, vecPeaks[middleVecPeaks]+1);
            baseLeft = extractedData[getMinElement(vecLeft) + maxLeft];
        }
        
        // Find right min
        vecRight = extractVector(extractedData, vecPeaks[middleVecPeaks], (int)extractedData_Size);
        maxRight = getMaxElement(vecRight) + vecPeaks[middleVecPeaks];
        if (maxRight == vecPeaks[middleVecPeaks]){
            baseRight = extractedData[vecPeaks[middleVecPeaks] + getMinElement(vecRight)];
        } else {
            int iteratorMax = vecPeaks[middleVecPeaks] + 1;
            while(iteratorMax < extractedData_Size) {
                iteratorMax++;
                if(extractedData[iteratorMax] > extractedData[vecPeaks[middleVecPeaks]]) {
                    maxRight = iteratorMax;
                    break;
                }
            }
            vecRight = extractVector(extractedData,vecPeaks[middleVecPeaks], (int)maxRight + 1);
            baseRight = extractedData[vecPeaks[middleVecPeaks] + getMinElement(vecRight)];
        }
        
        // Return prominence
        double minim = max(baseRight, baseLeft);
        prominence = abs(extractedData[vecPeaks[middleVecPeaks]] - minim);
    }
    
    return prominence;
}

// find index of maximum value on array
int FeaturesCalculatorWithoutFilter::getMaxArrayIndex(const valarray<complex<double>>& ArrayData) {
    struct acc_t {
        double max_value;
        int max_idx, current_idx;
        
        constexpr acc_t next() const { return {max_value, max_idx, current_idx + 1}; }
        constexpr acc_t next_with(complex<double> const c) const {
            return {c.real(), current_idx, current_idx + 1};
        }
    };
    
    return accumulate(
                      begin(ArrayData), end(ArrayData), acc_t{},
                      [](acc_t const acc, complex<double> const c) {
                          return c.real() < acc.max_value
                          ? acc.next()
                          : acc.next_with(c);
                      }
                      ).max_idx;
}

valarray<complex<double>> FeaturesCalculatorWithoutFilter::getAbsoluteArray(const valarray<complex<double>> &ArrayData) {
    int len = (int)ArrayData.size();
    complex<double> ConvertDoubleToAbs[len];
    valarray<complex<double>> AbsArray(ConvertDoubleToAbs,len);
    for (int i = 0; i < len; ++i) {
        AbsArray[i]=abs(ArrayData[i]);
    }
    return AbsArray;
}

vector<double> FeaturesCalculatorWithoutFilter::computeDominantFrequency(const vector<double> &data) {
    int sampling_rate = 100;
    // int Ns=10;
    int nfft = 1024;
    int nfft2 = 512;
    int index_cutoff = 123;
    int lowind = 6;
    int upind = 40;
    
    double const ts  = 1./sampling_rate; // [s]
    int len = (int)data.size();
    
    vector<double> signal_x(len);
    double means=computeMean(data);
    for (int i=0; i<len ; i++) {
        signal_x[i] = (data[i]-means);
    }
    // double dim = (double)signal_x.size();
    
    // equivalent to np.fft.fftfreq(nfft)*sampling_rate in python
    Eigen::VectorXd time(nfft);
    Eigen::VectorXd freq(nfft2);
    for(int u = 0; u < nfft2; ++u) {
        time(u) = u * ts;
        freq(u) = sampling_rate * u / double(nfft);
    }
    
    // equivalent to https://numpy.org/doc/stable/reference/generated/numpy.hamming.html in python
    vector<double> haming(len);
    for(int i = 0; i < len; ++i) {
        haming[i]=0.54 - 0.46 * cos((4 * acos(0.0) * i)/(len - 1));
    }
    
    // do dot product
    vector<double> sign_ham(len);
    for (int i = 0; i < len; ++i) {
        sign_ham[i]= signal_x[i]*haming[i];
    }
    
    // convert double to complexe and complexe with padding
    complex<double> Convert_x_to_complex[nfft];
    for(int i = 0; i < len; ++i) {
        Convert_x_to_complex[i] = sign_ham[i];
        Convert_x_to_complex[nfft2-i]=0;
    }
    
    // initialize buffer size for fft calculation
    valarray<complex<double>> result_fft(Convert_x_to_complex,nfft);
    
    // forward fft
    FFT* fft = new FFT();
    fft->computeFFT(result_fft);
    valarray<complex<double>> sub_x_complex=result_fft[slice(0,nfft2,1)];
    
    // furval
    valarray<complex<double>> furval=(sub_x_complex*sub_x_complex.apply(conj));
    furval/=furval.sum();
    
    // keep freq less  cuttof ie index less than 123
    valarray<complex<double>> furval_= furval[slice(0,index_cutoff,1)];
    furval_/=furval_.sum();
    
    valarray<complex<double>> sub_furval= furval[slice(lowind,upind-lowind,1)];
    
    int ind=lowind+getMaxArrayIndex(getAbsoluteArray(sub_furval));
    
    vector<double> freq_cutoff(index_cutoff);
    for (int i = 0; i < index_cutoff; ++i) {
        freq_cutoff[i]= freq(i);
    }
    
    double domfreq=freq_cutoff[ind];
    return {furval_[getMaxArrayIndex(furval_)].real(),domfreq};
}

// Features
Features* FeaturesCalculatorWithoutFilter::computeFeatures(Sensors* sensorsData, int threshold) {
    Features* features = new Features();

    // Norm
    sensorsData->set_acc_norm(computeNorm(sensorsData->get_sensors_acc_xyz()));
    sensorsData->set_gyro_norm(computeNorm(sensorsData->get_sensors_gyro_xyz()));
    sensorsData->set_mag_norm(computeNorm(sensorsData->get_sensors_mag_xyz()));

    rotateAndInsert(_acc_norm_nf, sensorsData->get_acc_norm());
    rotateAndInsert(_gyro_norm_nf, sensorsData->get_gyro_norm());
    rotateAndInsert(_mag_norm_nf, sensorsData->get_mag_norm());
    
    // Rotation and insertion
    rotateAndInsert(_acc_x, sensorsData->get_acc_x());
    rotateAndInsert(_acc_y, sensorsData->get_acc_y());
    rotateAndInsert(_acc_z, sensorsData->get_acc_z());
    rotateAndInsert(_gyro_x, sensorsData->get_gyro_x());
    rotateAndInsert(_gyro_y, sensorsData->get_gyro_y());
    rotateAndInsert(_gyro_z, sensorsData->get_gyro_z());
    rotateAndInsert(_mag_x, sensorsData->get_mag_x());
    rotateAndInsert(_mag_y, sensorsData->get_mag_y());
    rotateAndInsert(_mag_z, sensorsData->get_mag_z());

    // Filter
    Filter* filter = new Filter();
    /*
    vector<double> accx_filrered;
    vector<double> accy_filrered;
    vector<double> accz_filrered;
    vector<double> gyrx_filrered;
    vector<double> gyry_filrered;
    vector<double> gyrz_filrered;

    g.run([&accx_filrered, this, &filter] {accx_filrered=filter->filtfilt(_acc_x);});
    g.run([&accy_filrered, this, &filter] {accy_filrered=filter->filtfilt(_acc_y);});
    g.run([&accz_filrered, this, &filter] {accz_filrered=filter->filtfilt(_acc_z);});
    g.run([&gyrx_filrered, this, &filter] {gyrx_filrered=filter->filtfilt(_gyro_x);});
    g.run([&gyry_filrered, this, &filter] {gyry_filrered=filter->filtfilt(_gyro_y);});
    g.run([&gyrz_filrered, this, &filter] {gyrz_filrered=filter->filtfilt(_gyro_z);});
    g.wait();*/

    //features->set_test_accx(accx_filrered[1]);
    vector<double> accx_filrered =_acc_x;
    vector<double> accy_filrered =_acc_y;
    vector<double> accz_filrered =_acc_z;
    vector<double> gyrx_filrered =_gyro_x;
    vector<double> gyry_filrered =_gyro_y;
    vector<double> gyrz_filrered =_gyro_z;
    vector<double> magx_filrered =_mag_x;
    vector<double> magy_filrered =_mag_y;
    vector<double> magz_filrered =_mag_z;

    for (int k = 0; k < _threshold; ++k) {
        rotateAndInsert(_acc_norm, computeNorm(accx_filrered[k],accy_filrered[k],accz_filrered[k]));
        rotateAndInsert(_gyro_norm,computeNorm(gyrx_filrered[k],gyry_filrered[k],gyrz_filrered[k]));
        rotateAndInsert(_mag_norm,computeNorm(magx_filrered[k],magy_filrered[k],magz_filrered[k]));

    }
    //threshold=10;
    // Compute features
    if (threshold >= _threshold - 1) {

        // // Features gyro
        features->set_gyro_skewness_win70(computeSkewness(extractVector(_gyro_norm, _start_wind70, _window_size70)));
        features->set_gyro_skewness_win30(computeSkewness(extractVector(_gyro_norm, _start_wind30, _window_size30)));
        features->set_gyro_maxElement_win60(getMinElement(extractVector(_gyro_norm, _start_wind60, _window_size60)));
        features->set_gyro_sma_win80(computeSMA(extractVector(_gyro_norm, _start_wind80, _window_size80)));
        features->set_gyro_variance_win20(computeVariance(extractVector(_gyro_norm, _start_wind20, _window_size20),
                                                          computeMean(extractVector(_gyro_norm, _start_wind20, _window_size20)), 1));
        features->set_gyro_maxValue_win70(getMaxValue(extractVector(_gyro_norm, _start_wind70, _window_size70)));
        features->set_gyro_valley_prominences_win80(computeProminence(_gyro_norm, -1, _start_wind80, _window_size80));

        // Features accelero
        features->set_acc_median_win80(computeQuantile(extractVector(_acc_norm, _start_wind80, _window_size80)));
        features->set_acc_kurtosis_win30(computeKurtosis(extractVector(_acc_norm, _start_wind30, _window_size30)));
        features->set_acc_skewness_win5(computeSkewness(extractVector(_acc_norm, _start_wind5, _window_size5)));
        features->set_acc_minElement_win30(getMaxElement(extractVector(_acc_norm, _start_wind30, _window_size30)));
        features->set_acc_valley_prominences_win80(computeProminence(_acc_norm, -1, _start_wind80, _window_size80));
        features->set_acc_peak_prominences_win50(computeProminence(_acc_norm, 1, _start_wind50, _window_size50));
        features->set_acc_peak_prominences_win80(computeProminence(_acc_norm, 1, _start_wind80, _window_size80));

        // Feature Mag
        features->set_mag_skewness_win70(computeSkewness(extractVector(_mag_norm, _start_wind70, _window_size70)));
        features->set_mag_skewness_win30(computeSkewness(extractVector(_mag_norm, _start_wind30, _window_size30)));
        features->set_mag_maxElement_win60(getMinElement(extractVector(_mag_norm, _start_wind60, _window_size60)));
        features->set_mag_sma_win80(computeSMA(extractVector(_mag_norm, _start_wind80, _window_size80)));
        features->set_mag_variance_win20(computeVariance(extractVector(_mag_norm, _start_wind20, _window_size20),
                                                         computeMean(extractVector(_mag_norm, _start_wind20, _window_size20)), 1));
        features->set_mag_maxValue_win70(getMaxValue(extractVector(_mag_norm, _start_wind70, _window_size70)));
        features->set_mag_valley_prominences_win80(computeProminence(_mag_norm, -1, _start_wind80, _window_size80));


    }
    return features;
}

