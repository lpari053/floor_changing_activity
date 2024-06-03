"""
File: _bis_interpolation_data_on_acc.py

by Laura Parisot 24/05/2024

Contains 1 function: interpolate_gyrmag(string)

"""

"Importing libraries"

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

"""
Function interpolate_gyrmag(path)

This function aligns all sensor data acquisitions to the same timeline, specifically the accelerometer timeline.
We use the interpolate function from the numpy package.
This function rearranges the columns for each sensor.

Input:

    String path: path to the data collected by the smartphone for the sensors ACC, GYR, MAG, and BARO
    
Output:

    data_acc_inter: data for the accelerometer, arranged to have columns like mode, time, acc_x, acc_y, acc_z, and the number of steps
    data_gyr_inter: data for the gyroscope, interpolated to the accelerometer time acquisition and rearranged to have columns like mode, time, gyr_x, gyr_y, gyr_z, and the number of steps
    data_mag_inter: data for the magnetometer, interpolated to the accelerometer time acquisition and rearranged to have columns like mode, time, mag_x, mag_y, mag_z, and the number of steps
    data_baro_inter: data for the barometer, interpolated to the accelerometer time acquisition and rearranged to have columns like mode, time, pressure, and the number of steps
"""



def interpolate_gyrmag(chemin):
    
    data_acc =pd.read_csv(rf'{chemin}\ACC.txt', delimiter=',', header=None, index_col=None,skiprows=1)
    data_gyr = pd.read_csv(rf'{chemin}\GYR.txt', delimiter=',', header=None, index_col=None,skiprows=1)
    data_mag = pd.read_csv(rf'{chemin}\MAG.txt', delimiter=',', header=None, index_col=None,skiprows=1)
    data_baro=pd.read_csv(rf'{chemin}\BARO.txt', delimiter=',', header=None, index_col=None,skiprows=1)
    
    t_acc = data_acc.iloc[:, 1].astype(float)
    t_mag = data_mag.iloc[:, 1].astype(float)
    t_gyr = data_gyr.iloc[:, 1].astype(float)
    t_baro = data_baro.iloc[:, 1].astype(float)
    
    nb_pas=data_acc.iloc[:, 8]
    
    
    modie=np.array(data_acc.iloc[:, 0])

    for i,m in enumerate(modie):
        if isinstance(m,float):
            modie[i]='none'
    modie=pd.DataFrame(modie)
    
    data_mag_inter = np.column_stack([
        np.interp(t_acc, t_mag, data_mag.iloc[:, i].astype(float)) for i in range(2, 5)
    ])
    data_mag_inter = np.column_stack((modie,t_acc,data_mag_inter,nb_pas))
    
    data_gyr_inter = np.column_stack([
        np.interp(t_acc, t_gyr, data_gyr.iloc[:, i].astype(float)) for i in range(2, 5)
    ])
    data_gyr_inter = np.column_stack((modie,t_acc,data_gyr_inter,nb_pas))
    
    data_baro_inter = np.column_stack([
        np.interp(t_acc, t_baro, data_baro.iloc[:, 2].astype(float))
    ])
    data_baro_inter = np.column_stack((modie,t_acc,data_baro_inter,nb_pas))
    
    data_acc_inter=np.column_stack((modie,t_acc,data_acc.iloc[:, 3:6],nb_pas))
    
    return data_acc_inter,data_gyr_inter,data_mag_inter,data_baro_inter


