#include "FFT.hpp"

void fft(std::vector<Complex>& x) {
    int N = x.size();
    if (N <= 1) return;

    std::vector<Complex> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; ++i) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft(even);
    fft(odd);

    for (int k = 0; k < N / 2; ++k) {
        double angle = -2 * PI * k / N;
        Complex w = {cos(angle), sin(angle)};
        w.real *= odd[k].real;
        w.imag *= odd[k].imag;

        x[k].real = even[k].real + w.real;
        x[k].imag = even[k].imag + w.imag;

        x[k + N / 2].real = even[k].real - w.real;
        x[k + N / 2].imag = even[k].imag - w.imag;
    }
}

// Fonction pour calculer la magnitude du spectre
std::vector<double> magnitude(const std::vector<Complex>& x) {
    std::vector<double> mag(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        mag[i] = sqrt(x[i].real * x[i].real + x[i].imag * x[i].imag);
    }
    return mag;
}


int firstPeakIndex(const std::vector<double>& spectrum) {
    double maxVal = spectrum[1];
    int peakIndex = 1;

    for (size_t i = 2; i < spectrum.size(); ++i) {
        if (spectrum[i] > maxVal) {
            maxVal = spectrum[i];
            peakIndex = i;
        }
    }

    return peakIndex;
}



int firstPeakValue(const std::vector<double>& spectrum) {
    double maxVal = spectrum[1];
    int peakIndex = 1;

    for (size_t i = 2; i < spectrum.size(); ++i) {
        if (spectrum[i] > maxVal) {
            maxVal = spectrum[i];
            peakIndex = i;
        }
    }

    return maxVal;
}