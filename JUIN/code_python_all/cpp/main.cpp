/**
 * @file main.cpp
 * @brief Main program for calculating features from sensor data.
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Sensors.hpp" 
#include "FeaturesCalculator.hpp"
#include "Features.hpp" 

/**
 * @brief Function to split a string into tokens using a specified delimiter.
 * @param str The string to split.
 * @param delimiter The delimiter character used to separate tokens.
 * @return A vector containing the resulting tokens.
 */
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * @brief Main function of the program.
 * @param argc The number of command-line arguments.
 * @param argv An array of pointers to the command-line arguments.
 * @return 0 if the program executed successfully, a non-zero value in case of error.
 */

int main(int argc, char *argv[]) {

    FeaturesCalculator featureCalc;

    Features* features;

    std::string output_fichier=argv[2];

    std::ifstream fichier(argv[1]);
	
    std::ofstream outputFile(output_fichier); 

    string mode;
    
    std::cout  <<  argv[2]  <<  std::endl;

    outputFile 
        <<  "mode;"
          <<  "acc_arc;"

          <<  "gyr_arc;"

          <<  "mag_arc;"

          <<  "acc_x_aad;"
          <<  "acc_x_mean;"
          <<  "acc_x_std;"
          <<  "acc_x_kurt;"
          <<  "acc_x_skew;"

         <<  "acc_y_aad;"
         <<  "acc_y_mean;"
         <<  "acc_y_std;"
          <<  "acc_y_kurt;"
          <<  "acc_y_skew;"

         <<  "acc_z_aad;"
         <<  "acc_z_mean;"
         <<  "acc_z_std;"
         <<  "acc_z_kurt;"
         <<  "acc_z_skew;"

          <<  "gyr_x_aad;"
          <<  "gyr_x_mean;"
          <<  "gyr_x_std;"
          <<  "gyr_x_kurt;"
          <<  "gyr_x_skew;"

         <<  "gyr_y_aad;"
         <<  "gyr_y_mean;"
         <<  "gyr_y_std;"
          <<  "gyr_y_kurt;"
          <<  "gyr_y_skew;"

         <<  "gyr_z_aad;"
         <<  "gyr_z_mean;"
         <<  "gyr_z_std;"
         <<  "gyr_z_kurt;"
         <<  "gyr_z_skew;"

          <<  "mag_x_aad;"
          <<  "mag_x_mean;"
          <<  "mag_x_std;"
          <<  "mag_x_kurt;"
          <<  "mag_x_skew;"

         <<  "mag_y_aad;"
         <<  "mag_y_mean;"
         <<  "mag_y_std;"
          <<  "mag_y_kurt;"
          <<  "mag_y_skew;"

         <<  "mag_z_aad;"
         <<  "mag_z_mean;"
         <<  "mag_z_std;"
         <<  "mag_z_kurt;"
         <<  "mag_z_skew;"

         <<  "baro_aad;"
         <<  "baro_mean;"
         <<  "baro_std;"
         <<  "baro_kurt;"
         <<  "baro_skew;"
         <<  "nb_step;"


         <<  "aad_acc_norm;"
         <<  "mean_acc_norm;"
         <<  "std_acc_norm;"
         <<  "kurt_acc_norm;"
         <<  "skew_acc_norm;"
        
        
         <<  "aad_gyro_norm;"
         <<  "mean_gyro_norm;"
         <<  "std_gyro_norm;"
         <<  "kurtosis_gyro_norm;"
         <<  "skewness_gyro_norm;"

         <<  "aad_mag_norm;"
         <<  "mean_mag_norm;"
         <<  "std_mag_norm;"
         <<  "kurt_mag_norm;"
         <<  "skew_mag_norm \n" ;


    std::string ligne;
    int ligneCourante = 0;

    while (std::getline(fichier, ligne)) {
        std::istringstream iss(ligne);

        char delimiter = ',';
        
        std::vector<std::string> vec_string;

        std::vector<std::string> result = split(ligne, delimiter);

//       for (int i=0;i<result.size();i++){
//  std::cout  <<  i  <<  std::endl;
//  std::cout  <<  result[i]  <<  std::endl;
//          }


        float acc_x= std::stof(result[1]);
        float acc_y= std::stof(result[2]);
        float acc_z= std::stof(result[3]);
        float gyr_x= std::stof(result[4]);
        float gyr_y= std::stof(result[5]);
        float gyr_z= std::stof(result[6]);
        float mag_x= std::stof(result[7]);
        float mag_y= std::stof(result[8]);
        float mag_z= std::stof(result[9]);
        float baro= std::stof(result[10]);
        float temps= std::stof(result[11]);
        float step= std::stof(result[12]);
        mode= result[0];

        

        ++ligneCourante;

        float valeur;
        char delim;

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

      

        featureCalc.computeSensor(&sensors); 
	   
      
    } //fin lecture ligne

    features=featureCalc.computeFeatureVertical();
        outputFile  <<  mode      <<  ";";
         outputFile  <<  features->get_acc_x_arc()      <<  ";";
         outputFile  <<  features->get_gyr_x_arc()      <<  ";";
         outputFile  <<  features->get_mag_x_arc()      <<  ";";
         outputFile  <<  features->get_acc_x_aad()      <<  ";";
         outputFile  <<  features->get_acc_x_mean()      <<  ";";
         outputFile  <<  features->get_acc_x_std()      <<  ";";
         outputFile  <<  features->get_acc_x_kurt()      <<  ";";
         outputFile  <<  features->get_acc_x_skew()      <<  ";";
        outputFile  <<   features->get_acc_y_aad()      <<  ";";
        outputFile  <<   features->get_acc_y_mean()      <<  ";";
        outputFile  <<   features->get_acc_y_std()      <<  ";";
         outputFile  <<  features->get_acc_y_kurt()      <<  ";";
         outputFile  <<  features->get_acc_y_skew()      <<  ";";
        outputFile  <<   features->get_acc_z_aad()      <<  ";";
        outputFile  <<   features->get_acc_z_mean()      <<  ";";
        outputFile  <<   features->get_acc_z_std()      <<  ";";
        outputFile  <<   features->get_acc_z_kurt()      <<  ";";
        outputFile  <<   features->get_acc_z_skew()      <<  ";";
         outputFile  <<  features->get_gyr_x_aad()      <<  ";";
         outputFile  <<  features->get_gyr_x_mean()      <<  ";";
         outputFile  <<  features->get_gyr_x_std()      <<  ";";
         outputFile  <<  features->get_gyr_x_kurt()      <<  ";";
         outputFile  <<  features->get_gyr_x_skew()      <<  ";";
        outputFile  <<   features->get_gyr_y_aad()      <<  ";";
        outputFile  <<   features->get_gyr_y_mean()      <<  ";";
        outputFile  <<   features->get_gyr_y_std()      <<  ";";
         outputFile  <<  features->get_gyr_y_kurt()      <<  ";";
         outputFile  <<  features->get_gyr_y_skew()      <<  ";";
        outputFile  <<   features->get_gyr_z_aad()      <<  ";";
        outputFile  <<   features->get_gyr_z_mean()      <<  ";";
        outputFile  <<   features->get_gyr_z_std()      <<  ";";
        outputFile  <<   features->get_gyr_z_kurt()      <<  ";";
        outputFile  <<   features->get_gyr_z_skew()      <<  ";";
         outputFile  <<  features->get_mag_x_aad()      <<  ";";
         outputFile  <<  features->get_mag_x_mean()      <<  ";";
         outputFile  <<  features->get_mag_x_std()      <<  ";";
         outputFile  <<  features->get_mag_x_kurt()      <<  ";";
         outputFile  <<  features->get_mag_x_skew()      <<  ";";
        outputFile  <<   features->get_mag_y_aad()      <<  ";";
        outputFile  <<   features->get_mag_y_mean()      <<  ";";
        outputFile  <<   features->get_mag_y_std()      <<  ";";
         outputFile  <<  features->get_mag_y_kurt()      <<  ";";
         outputFile  <<  features->get_mag_y_skew()      <<  ";";
        outputFile  <<   features->get_mag_z_aad()      <<  ";";
        outputFile  <<   features->get_mag_z_mean()      <<  ";";
        outputFile  <<   features->get_mag_z_std()      <<  ";";
        outputFile  <<   features->get_mag_z_kurt()      <<  ";";
        outputFile  <<   features->get_mag_z_skew()      <<  ";";
        outputFile  <<   features->get_baro_aad()      <<  ";";
        outputFile  <<   features->get_baro_mean()      <<  ";";
        outputFile  <<   features->get_baro_std()      <<  ";";
        outputFile  <<   features->get_baro_kurt()      <<  ";";
        outputFile  <<   features->get_baro_skew()      <<  ";";
        outputFile  <<   features->get_nb_step()      <<  ";";


        outputFile  <<   features->get_acc_norm_aad()      <<  ";";
        outputFile  <<   features->get_acc_norm_mean()      <<  ";";
        outputFile  <<   features->get_acc_norm_std()      <<  ";";
        outputFile  <<   features->get_acc_norm_kurt()      <<  ";";
        outputFile  <<   features->get_acc_norm_skew()      <<  ";";
 
        outputFile  <<   features->get_gyro_norm_aad()      <<  ";";
        outputFile  <<   features->get_gyro_norm_mean()      <<  ";";
        outputFile  <<   features->get_gyro_norm_std()      <<  ";";
        outputFile  <<   features->get_gyro_norm_kurt()      <<  ";";
        outputFile  <<   features->get_gyro_norm_skew()      <<  ";";
 
        outputFile  <<   features->get_mag_norm_aad()      <<  ";";
        outputFile  <<   features->get_mag_norm_mean()      <<  ";";
        outputFile  <<   features->get_mag_norm_std()      <<  ";";
        outputFile  <<   features->get_mag_norm_kurt()      <<  ";";
        outputFile  <<   features->get_mag_norm_skew();


    delete features;

    fichier.close();
    outputFile.close();

    return 0;
}
