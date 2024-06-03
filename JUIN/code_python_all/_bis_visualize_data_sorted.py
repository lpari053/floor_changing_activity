
"""
File: _1_visualisation_data.py

by Laura Parisot 24/05/2024

Contains 2 functions:
    
    visu_data(dataframe,dataframe,dataframe,dataframe,string)
    showing()

"""

"Importing libraries"
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os


"""
Function visu_data(dataframe,dataframe,dataframe,dataframe,string)

This function permit to visualize the data collected , 
The data need to be interpolate to the same time line.
It save the graphcis in a specific folder accoridng to the activty practice


Input: 
    
    data_acc: Pandas Dataframe of the accelerometer data made with columns like
    mode,time,acc_x,acc_y,acc_z and number of step
    
    data_gyr: Pandas Dataframe of the gyroscope data made with columns like
    mode,time,gyr_x,gyr_y,gyr_z and number of step
    
    data_mag: Pandas Dataframe of the magnetometer data made with columns like
    mode,time,mag_x,mag_y,mag_z and number of step
    
    data_baro: Pandas Dataframe of the barometer data made with columns like
    mode,time,pressure and number of step
    
    
    chemin :  String wich is the name of the folder containig the data
        
Output :
    
    None

"""


def visu_data_sorted(chemin,file):
    
    data=pd.read_csv(chemin)
    print(data.columns)
    
    data_acc = data[['mode', 'time', 'acc_x', 'acc_y', 'acc_z', 'nb_step']]
    data_gyr = data[['mode', 'time', 'gyr_x', 'gyr_y', 'gyr_z', 'nb_step']]
    data_mag = data[['mode', 'time', 'mag_x', 'mag_y', 'mag_z', 'nb_step']]
    data_baro = data[['mode', 'time', 'pressure', 'nb_step']]


    max_acc_x = data_acc.iloc[:, 2].max()+1
    max_acc_y = data_acc.iloc[:, 3].max()+1
    max_acc_z = data_acc.iloc[:, 4].max()+1
    
    max_gyr_x = data_gyr.iloc[:, 2].max()+1
    max_gyr_y = data_gyr.iloc[:, 3].max()+1
    max_gyr_z = data_gyr.iloc[:, 4].max()+1
    
    max_mag_x = data_mag.iloc[:, 2].max()+1
    max_mag_y = data_mag.iloc[:, 3].max()+1
    max_mag_z = data_mag.iloc[:, 4].max()+1
    
    min_acc_x = data_acc.iloc[:, 2].min()-1
    min_acc_y = data_acc.iloc[:, 3].min()-1
    min_acc_z = data_acc.iloc[:, 4].min()-1
    
    min_gyr_x = data_gyr.iloc[:, 2].min()-1
    min_gyr_y = data_gyr.iloc[:, 3].min()-1
    min_gyr_z = data_gyr.iloc[:, 4].min()-1
    
    min_mag_x = data_mag.iloc[:, 2].min()-1
    min_mag_y = data_mag.iloc[:, 3].min()-1
    min_mag_z = data_mag.iloc[:, 4].min()-1
    
    
    nom_dossier = os.path.basename(chemin)
    
    parties = nom_dossier.split('_')
    if parties[0]=='no':
        parties=['no_name',parties[2],parties[3]]
    personne = parties[0]
    date = parties[1]
    type_activite =parties[2].split(".")[0]
    print("Chemin:", chemin)
    print("Personne:", personne)
    print("Date:", date)
    print("Type d'activité:", type_activite.split(".")[0])
    print()
    
    titre=fr"{type_activite.upper()} Date : {date}  Personne : {personne}"
    
        
    fig, axs = plt.subplots(4, 4, figsize=(14, 10))
    axs[1, 3].plot(data_baro.iloc[:,1], data_baro.iloc[:,2], label='Pressure [hPa]', color='violet')
    axs[1, 3].legend()
    axs[1, 3].set_xlabel('Temps [s]')
    axs[1, 3].set_title('Baro data')
    
    axs[0, 3].plot(data_acc.iloc[:,1], data_acc.iloc[:,5], label='Number of Step', color='violet')
    axs[0, 3].legend()
    axs[0, 3].set_xlabel('Temps [s]')
    axs[0, 3].set_title('Step data')
    
    
    fig.delaxes(axs[2, 3])
    fig.delaxes(axs[3, 3])
    
    
    

    axs[0,0].plot(data_acc.iloc[:,1], data_acc.iloc[:,2], label='Accx [m/s2]',color='g')
    axs[0,0].set_title('ACC Data')
    axs[0, 0].set_xlabel('Temps [s]')
    axs[0,0].set_ylim(min_acc_x,max_acc_x)
    axs[0,0].legend()
    
    axs[1,0].plot(data_acc.iloc[:,1], data_acc.iloc[:,3], label='Accy [m/s2]',color='r')
    axs[1,0].set_ylim(min_acc_y,max_acc_y)
    axs[1,0].set_xlabel('Temps [s]')
    axs[1,0].legend()
    
    
    axs[2,0].plot(data_acc.iloc[:,1], data_acc.iloc[:,4], label='Accz [m/s2]',color='b')
    axs[2,0].set_ylim(min_acc_z,max_acc_z)
    axs[2,0].set_xlabel('Temps [s]')
    axs[2,0].legend()
    
    axs[3,0].plot(data_acc.iloc[:,1], np.sqrt(data_acc.iloc[:,4]**2+data_acc.iloc[:,3]**2+data_acc.iloc[:,2]**2), label='Norme Acc [m/s2]',color='c')
    axs[3,0].set_xlabel('Temps [s]')
    axs[3,0].legend()
    
    
    
    axs[0,1].plot(data_gyr.iloc[:,1], data_gyr.iloc[:,2], label='Gyrx [rad/s]',color='g')
    axs[0,1].set_title('GYR Data')
    axs[0,1].set_ylim(min_gyr_x,max_gyr_x)
    axs[0,1].set_xlabel('Temps [s]')
    axs[0,1].legend()
    
    axs[1,1].plot(data_gyr.iloc[:,1], data_gyr.iloc[:,3], label='Gyrcy [rad/s]',color='r')
    axs[1,1].set_ylim(min_gyr_y,max_gyr_y)
    axs[1,1].set_xlabel('Temps [s]')
    axs[1,1].legend()
    
    axs[2,1].plot(data_gyr.iloc[:,1], data_gyr.iloc[:,4], label='Gyrz [rad/s]',color='b')
    axs[2,1].set_ylim(min_gyr_z,max_gyr_z)
    axs[2,1].set_xlabel('Temps [s]')
    axs[2,1].legend()
    
    axs[3,1].plot(data_gyr.iloc[:,1], np.sqrt(data_gyr.iloc[:,4]**2+data_gyr.iloc[:,3]**2+data_gyr.iloc[:,2]**2), label='Norme Gyr [rad/s]',color='c')
    axs[3,1].set_xlabel('Temps [s]')
    axs[3,1].legend()
    
    
    
    
    
    axs[0,2].plot(data_mag.iloc[:,1], data_mag.iloc[:,2], label='Magx [μT]',color='g')
    axs[0,2].set_title('Mag Data')
    axs[0,2].set_ylim(min_mag_x,max_mag_x)
    axs[0,2].set_xlabel('Temps [s]')
    axs[0,2].legend()
    
    axs[1,2].plot(data_mag.iloc[:,1], data_mag.iloc[:,3], label='Magcy [μT]',color='r')
    axs[1,2].set_ylim(min_mag_y,max_mag_y)
    axs[1,2].set_xlabel('Temps [s]')
    axs[1,2].legend()
    
    axs[2,2].plot(data_mag.iloc[:,1], data_mag.iloc[:,4], label='Magz [μT]',color='b')
    axs[2,2].set_ylim(min_mag_z,max_mag_z)
    axs[2,2].set_xlabel('Temps [s]')
    axs[2,2].legend()
    
    axs[3,2].plot(data_mag.iloc[:,1], np.sqrt(data_mag.iloc[:,4]**2+data_mag.iloc[:,3]**2+data_mag.iloc[:,2]**2), label='Norme Mag [μT]',color='c')
    axs[3,2].set_xlabel('Temps [s]')
    axs[3,2].legend()
    
    plt.suptitle(titre)
    plt.tight_layout()
    
            
    if not os.path.exists(f'../graphics_sorted/{str(type_activite).split(".")[0]}'):
            os.makedirs(f'../graphics_sorted/{str(type_activite).split(".")[0]}')
    
    plt.savefig(f'../graphics_sorted/{str(type_activite).split(".")[0]}/{file.split(".")[0]}.png')
    plt.show()
    
    
    
"""
Function showing()

This function permit to navigate between all the folder containing the data
to make the input of the function visu_data


Input: 
    
    None
    
        
Output :
    
    None

"""




if __name__ == '__main__':
    
    fichiers=os.listdir('../data_sort_by_me/data_interpolate_sorted')
    
    for fich in fichiers:
        visu_data(f'../data_sort_by_me/data_interpolate_sorted/{fich}',fich)
    