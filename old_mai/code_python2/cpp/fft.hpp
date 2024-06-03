#ifndef FFT_HPP
#define FFT_HPP

#include <vector>
#include <cmath>

const double PI = 3.14159265358979323846;

// Structure pour les nombres complexes
struct Complex {
    double real;
    double imag;
};

// Fonction pour effectuer la FFT
void fft(std::vector<Complex>& x);

// Fonction pour calculer la magnitude du spectre
std::vector<double> magnitude(const std::vector<Complex>& x);

// Fonction pour trouver l'indice du premier pic dans le spectre
int firstPeakIndex(const std::vector<double>& spectrum);

int firstPeakValue(const std::vector<double>& spectrum);



#endif // FFT_HPP

