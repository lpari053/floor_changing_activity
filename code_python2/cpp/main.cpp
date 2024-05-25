#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Sensors.hpp" 
#include "FeaturesCalculator.hpp"
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

    
    FeaturesCalculator featureCalc;

    Features* features;

    std::string output_fichier=argv[2];

    std::ifstream fichier(argv[1]);
	
	std::cout << argv[2] << std::endl;


    std::ofstream outputFile(output_fichier); 


       outputFile <<"mode;"

         << "acc_arc;"

         << "gyr_arc;"

         << "mag_arc;"

         << "acc_x_aad;"
         << "acc_x_mean;"
         << "acc_x_std;"
         << "acc_x_kurt;"
         << "acc_x_skew;"

        << "acc_y_aad;"
        << "acc_y_mean;"
        << "acc_y_std;"
         << "acc_y_kurt;"
         << "acc_y_skew;"

        << "acc_z_aad;"
        << "acc_z_mean;"
        << "acc_z_std;"
        << "acc_z_kurt;"
        << "acc_z_skew;"

         << "gyr_x_aad;"
         << "gyr_x_mean;"
         << "gyr_x_std;"
         << "gyr_x_kurt;"
         << "gyr_x_skew;"

        << "gyr_y_aad;"
        << "gyr_y_mean;"
        << "gyr_y_std;"
         << "gyr_y_kurt;"
         << "gyr_y_skew;"

        << "gyr_z_aad;"
        << "gyr_z_mean;"
        << "gyr_z_std;"
        << "gyr_z_kurt;"
        << "gyr_z_skew;"

         << "mag_x_aad;"
         << "mag_x_mean;"
         << "mag_x_std;"
         << "mag_x_kurt;"
         << "mag_x_skew;"

        << "mag_y_aad;"
        << "mag_y_mean;"
        << "mag_y_std;"
         << "mag_y_kurt;"
         << "mag_y_skew;"

        << "mag_z_aad;"
        << "mag_z_mean;"
        << "mag_z_std;"
        << "mag_z_kurt;"
        << "mag_z_skew;"

        << "baro_aad;"
        << "baro_mean;"
        << "baro_std;"
        << "baro_kurt;"
        << "baro_skew;"
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


         outputFile << features->get_acc_x_arc()<< ";";

         outputFile << features->get_gyr_x_arc()<< ";";

         outputFile << features->get_mag_x_arc()<< ";";

         outputFile << features->get_acc_x_aad()<< ";";
         outputFile << features->get_acc_x_mean()<< ";";
         outputFile << features->get_acc_x_std()<< ";";
         outputFile << features->get_acc_x_kurt()<< ";";
         outputFile << features->get_acc_x_skew()<< ";";

        outputFile <<  features->get_acc_y_aad()<< ";";
        outputFile <<  features->get_acc_y_mean()<< ";";
        outputFile <<  features->get_acc_y_std()<< ";";
         outputFile << features->get_acc_y_kurt()<< ";";
         outputFile << features->get_acc_y_skew()<< ";";

        outputFile <<  features->get_acc_z_aad()<< ";";
        outputFile <<  features->get_acc_z_mean()<< ";";
        outputFile <<  features->get_acc_z_std()<< ";";
        outputFile <<  features->get_acc_z_kurt()<< ";";
        outputFile <<  features->get_acc_z_skew()<< ";";

         outputFile << features->get_gyr_x_aad()<< ";";
         outputFile << features->get_gyr_x_mean()<< ";";
         outputFile << features->get_gyr_x_std()<< ";";
         outputFile << features->get_gyr_x_kurt()<< ";";
         outputFile << features->get_gyr_x_skew()<< ";";

        outputFile <<  features->get_gyr_y_aad()<< ";";
        outputFile <<  features->get_gyr_y_mean()<< ";";
        outputFile <<  features->get_gyr_y_std()<< ";";
         outputFile << features->get_gyr_y_kurt()<< ";";
         outputFile << features->get_gyr_y_skew()<< ";";

        outputFile <<  features->get_gyr_z_aad()<< ";";
        outputFile <<  features->get_gyr_z_mean()<< ";";
        outputFile <<  features->get_gyr_z_std()<< ";";
        outputFile <<  features->get_gyr_z_kurt()<< ";";
        outputFile <<  features->get_gyr_z_skew()<< ";";

         outputFile << features->get_mag_x_aad()<< ";";
         outputFile << features->get_mag_x_mean()<< ";";
         outputFile << features->get_mag_x_std()<< ";";
         outputFile << features->get_mag_x_kurt()<< ";";
         outputFile << features->get_mag_x_skew()<< ";";

        outputFile <<  features->get_mag_y_aad()<< ";";
        outputFile <<  features->get_mag_y_mean()<< ";";
        outputFile <<  features->get_mag_y_std()<< ";";
         outputFile << features->get_mag_y_kurt()<< ";";
         outputFile << features->get_mag_y_skew()<< ";";

        outputFile <<  features->get_mag_z_aad()<< ";";
        outputFile <<  features->get_mag_z_mean()<< ";";
        outputFile <<  features->get_mag_z_std()<< ";";
        outputFile <<  features->get_mag_z_kurt()<< ";";
        outputFile <<  features->get_mag_z_skew()<< ";";

        outputFile <<  features->get_baro_aad()<< ";";
        outputFile <<  features->get_baro_mean()<< ";";
        outputFile <<  features->get_baro_std()<< ";";
        outputFile <<  features->get_baro_kurt()<< ";";
        outputFile <<  features->get_baro_skew()<< ";";

        outputFile <<  features->get_nb_step()<< "\n ";


       }

        delete features;

         }


    }

    fichier.close();
    outputFile.close();

    return 0;
}
