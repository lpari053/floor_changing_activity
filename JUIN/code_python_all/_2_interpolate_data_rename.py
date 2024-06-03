"""
File: _2_interpolate_data_rename.py

by Laura Parisot 24/05/2024

Contains 1 function:
    
    interpolation_of_data_rename()

"""

"Importing libraries"
import os 
import numpy as np
import pandas as pd
import math





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



"""
Function interpolation_of_data_rename()

This function permit to take the data that has been rename and interpolate the sensor 
data on the same time acquisition and save it on a different folder
The time acquisition is the acc time acquisition

Input: None

Output : None

"""

def interpolation_of_data_rename(folder):
    
    if not os.path.exists(fr'../data_treat/data_interpolate'):
            os.makedirs(fr'../data_treat/data_interpolate/')
    
    
    data_acc,data_gyr,data_mag,data_baro=interpolate_gyrmag(f'../data_treat/rename/{folder}')
    modes=np.where(np.array(data_acc[:,0]) == None, 'none', np.array(data_acc[:,0]))
    
    if len(np.unique(modes))==1:
        
        df=pd.concat([data_acc.iloc[:,:],data_gyr.iloc[:,:],data_mag.iloc[:,:],data_baro.iloc[:,:]],axis=1)      
        df.to_csv(f'../data_treat/data_interpolate/{folder}_{modes[0]}.txt',header=False,index=False)
        
    else:
        
        df=None
        mode_now=modes[0]
        index_begin=0
        data_acc=pd.DataFrame(data_acc)
        data_gyr=pd.DataFrame(data_gyr)
        data_mag=pd.DataFrame(data_mag)
        data_baro=pd.DataFrame(data_baro)
        count=1
        for index,mode in enumerate(modes):
            if mode!=mode_now:
                df=pd.concat([data_acc.iloc[index_begin:index-1,:],data_gyr.iloc[index_begin:index-1,:],data_mag.iloc[index_begin:index-1,:],data_baro.iloc[index_begin:index-1,:]],axis=1)      
                df.to_csv(f'../data_treat/data_interpolate/{folder}_{mode_now}.txt',header=False,index=False)
                df=None
                index_begin=index
                mode_now=mode
                count+=1
    
    
if __name__ == '__main__':
    
    fichiers=os.listdir('../data_treat/rename')
    
    for folder in fichiers:
        print(rf'Begin to interpolate {folder}')
        interpolation_of_data_rename(f'{folder}')