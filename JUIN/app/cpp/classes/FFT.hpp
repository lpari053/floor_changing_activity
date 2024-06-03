//
//  FFT.hpp
//  labcom
//
//  Created by Yohann Tschudi on 01/04/2022.
//

#ifndef FFT_hpp
#define FFT_hpp

#include <complex>
#include <iostream>
#include <valarray>

using namespace std;

class FFT
{
    public:
        void computeFFT(valarray<complex<double>> &);
};


#endif /* FFT_hpp */
