#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Sensors.hpp" 
#include "FeaturesCalculatorNorm.hpp"
#include "Features.hpp" 


std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

int main(int argc, char *argv[]) {

    
    FeaturesCalculatorNorm featureCalc;

    Features* features;

    std::string output_fichier=argv[2];

    std::ifstream fichier(argv[1]);
	
	std::cout << argv[2] << std::endl;


    std::ofstream outputFile(output_fichier); 


       outputFile <<"mode;"

        << "acc_norm_mean;"
        << "acc_norm_std;"
        << "acc_norm_kurt;"
        << "acc_norm_skew;"
        << "acc_norm_aad;"

        << "gyro_norm_mean;"
        << "gyro_norm_std;"
        << "gyro_norm_kurt;"
        << "gyro_norm_skew;"
        << "gyro_norm_aad;"

        << "mag_norm_mean;"
        << "mag_norm_std;"
        << "mag_norm_kurt;"
        << "mag_norm_skew;"
        << "mag_norm_aad;" 

        << "nb_step;\n" ;


    std::string ligne;
    int ligneCourante = 0;

    int nb_echantillion = 0;

    int taille_input=atoi(argv[3]);



    while (std::getline(fichier, ligne)) {
        std::istringstream iss(ligne);

        char delimiter = ',';
        
        std::vector<std::string> vec_string;

        std::vector<std::string> result = split(ligne, delimiter);

        float acc_x= std::stof(result[2]);
        float acc_y= std::stof(result[3]);
        float acc_z= std::stof(result[4]);
        float gyr_x= std::stof(result[5]);
        float gyr_y= std::stof(result[6]);
        float gyr_z= std::stof(result[7]);
        float mag_x= std::stof(result[8]);
        float mag_y= std::stof(result[9]);
        float mag_z= std::stof(result[10]);
        float baro= std::stof(result[11]);
        float temps= std::stof(result[1]);
        float step= std::stof(result[12]);
        string mode= result[0];


        ++ligneCourante;
        ++nb_echantillion;

        float valeur;
        char delim;


if (result.size() ==13 ){

            Sensors sensors(
                step,
                baro,
                acc_x,
                acc_y,
                acc_z,
                gyr_x,
                gyr_y,
                gyr_z,
                mag_x,
                mag_y,
                mag_z

        );

       features  = featureCalc.computeFeatures(&sensors, nb_echantillion,taille_input); 

       if (nb_echantillion>= taille_input){

        outputFile << mode << ";";
        outputFile <<  features->get_acc_norm_mean()<<  ";";
        outputFile <<  features->get_acc_norm_std()<<  ";";
        outputFile <<  features->get_acc_norm_kurt()<<  ";";
        outputFile <<  features->get_acc_norm_skew()<<  ";";
        outputFile <<  features->get_acc_norm_aad()<<  ";";
        outputFile <<  features->get_gyro_norm_mean()<<  ";";
        outputFile <<  features->get_gyro_norm_std()<<  ";";
        outputFile <<  features->get_gyro_norm_kurt()<<  ";";
        outputFile <<  features->get_gyro_norm_skew()<<  ";";
        outputFile <<  features->get_gyro_norm_aad()<<  ";";
        outputFile <<  features->get_mag_norm_mean()<<  ";";
        outputFile <<  features->get_mag_norm_std()<<  ";";
        outputFile <<  features->get_mag_norm_kurt()<<  ";";
        outputFile <<  features->get_mag_norm_skew()<<  ";";
        outputFile <<  features->get_mag_norm_aad()<<  ";";
        outputFile <<  features->get_nb_step()<< "\n ";


       }

        delete features;

         }


    }

    fichier.close();
    outputFile.close();

    return 0;
}
