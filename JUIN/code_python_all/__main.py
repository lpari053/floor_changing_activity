
"Importing libraries"
import zipfile
import os
import shutil
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import subprocess
from sklearn.model_selection import train_test_split
import seaborn as sns
from sklearn.feature_selection import mutual_info_classif
from sklearn.tree import DecisionTreeClassifier
import warnings
warnings.filterwarnings('ignore')
from sklearn.metrics import accuracy_score
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix
import onnx
import onnxmltools
from onnxmltools.convert.common.data_types import FloatTensorType
from xgboost import XGBClassifier
from tensorflow.keras.layers import Input,Conv1D, MaxPooling1D, GlobalAveragePooling1D, Dense, Dropout, BatchNormalization,Flatten,GlobalMaxPooling1D
from tensorflow.keras.callbacks import ModelCheckpoint
from keras.models import load_model
from tensorflow.keras.models import Model
import tensorflow as tf
import tf2onnx
import keras

"Step 1 UNZIP the original file "

def unzip_file(name_file_zip):
    fich=name_file_zip
    path_original_zip='../data_original/zip'
    path_original_unzip='../data_original/unzip'
    
    if os.path.exists(f'{path_original_unzip}/{fich}'):
        os.makedirs(f'{path_original_unzip}/{fich[0:-4]}')
        
    with zipfile.ZipFile(f'{path_original_zip}/{fich}', 'r') as zip_ref:
        zip_ref.extractall(f'{path_original_unzip}/{fich[0:-4]}')
        
    if not os.path.exists(f'../data_treat/unzip'):
        os.makedirs(f'../data_treat/unzip')
        
    if not os.path.exists(f'../data_treat/unzip/{fich[0:-4]}'):
        shutil.copytree(f'../data_original/unzip/{fich[0:-4]}', f'../data_treat/unzip/{fich[0:-4]}')
        
    if not os.path.exists(f'../data_treat/zip'):
        os.makedirs(f'../data_treat/zip')
        
    if not os.path.exists(f'../data_treat/zip/{fich}'):
        shutil.copy2(f'../data_original/zip/{fich}', f'../data_treat/zip/{fich}')
        
    if not os.path.exists(f'../data_treat/zip'):
        os.makedirs(f'../data_treat/zip')
        
    if not os.path.exists(f'../data_treat/zip/{fich}'):
        shutil.copy2(f'../data_original/zip/{fich}', f'../data_treat/zip/{fich}')
    

"Step 2 rename the file "

def rename_original_data(fich):
    
    base1='../data_treat/unzip'
    personnes=os.listdir(f'{base1}/{fich}')  
    for personne in personnes:
        days=os.listdir(f'{base1}/{fich}/{personne}')
        for day in days:
            hours=os.listdir(f'{base1}/{fich}/{personne}/{day}')
            for hour in hours:
                path_all=f'{base1}/{fich}/{personne}/{day}/{hour}'
    
    
                if personne=='no name':
                    per='none'
                else:
                    per=personne
                name=f'{per}_{day}-{hour}'
                print(f'Begin renamig {name}')
                name2=f'{per}_{day.replace("-","")}-{hour}'
                if not os.path.exists(f'../data_treat/rename/{name2}'):
                    os.makedirs(f'../data_treat/rename/{name2}')
                    
                if not os.path.exists(f'../data_original/data_before/{name2}'):
                    os.makedirs(f'../data_original/data_before/{name2}')
                    
                for sensor in os.listdir(path_all):
                    shutil.copy2(f'{path_all}/{sensor}',f'../data_original/data_before/{name2}')
                    shutil.copy2(f'{path_all}/{sensor}',f'../data_treat/rename/{name2}')
                    
                    
    for fich in os.listdir('../data_original/data_before'):
        if len(fich.split('_'))==3:
            per=fich.split('_')[0]
            date=fich.split('_')[1]
            name_new=f'{per}_{date}'
            os.rename(f'../data_original/data_before/{fich}', f'../data_original/data_before/{name_new}')  
            fich=name_new
        if not os.path.exists(f'../data_treat/rename/{fich}'):
            shutil.copytree(f'../data_original/data_before/{fich}',f'../data_treat/rename/{fich}')
        
        
"Step 3 interpolate the file "        

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
    nb_pas=pd.DataFrame(nb_pas,dtype=float)
    
    
    modie=np.array(data_acc.iloc[:, 0])

    for i,m in enumerate(modie):
        if isinstance(m,float):
            modie[i]='unknown'
        if m=='lift':
            modie[i]='elevator'
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
    
    
    data_acc=pd.DataFrame(data_acc,columns=['mode','time','acc_x','acc_y','acc_z','nb_step'])
    data_gyr=pd.DataFrame(data_gyr,columns=['mode','time','gyr_x','gyr_y','gyr_z','nb_step'])
    data_mag=pd.DataFrame(data_mag,columns=['mode','time','mag_x','mag_y','mag_z','nb_step'])
    data_baro=pd.DataFrame(data_baro,columns=['mode','time','pressure','nb_step'])
    
    data_acc=data_acc.loc[data_acc['mode'] != 'unknown']
    data_gyr=data_gyr.loc[data_gyr['mode'] != 'unknown']
    data_mag=data_mag.loc[data_mag['mode'] != 'unknown']
    data_baro=data_baro.loc[data_baro['mode'] != 'unknown']
    
    data_acc.reset_index(drop=True, inplace=True)
    data_mag.reset_index(drop=True, inplace=True)
    data_baro.reset_index(drop=True, inplace=True)
    data_gyr.reset_index(drop=True, inplace=True)
    
    modes=np.where(np.array(data_acc.iloc[:,0])  == 'lift', 'elevator', np.array(data_acc.iloc[:,0]) )
    

    if len(np.unique(modes))==1:
        
        
        
        df=pd.concat([data_acc.iloc[:,:-1],data_gyr.iloc[:,2:-1],data_mag.iloc[:,2:-1],data_baro.iloc[:,2:]],axis=1)      
        df.to_csv(f'../data_treat/data_interpolate/{folder}_{modes[0]}.txt',header=True,index=False)
        mode=modes[0]
        if not os.path.exists(f'../data_treat/data_interpolate_base/{folder}_{mode}'):
            os.makedirs(f'../data_treat/data_interpolate_base/{folder}_{mode}')        
        data_acc.to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}/ACC.txt',header=True,index=False)
        data_gyr.to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}/GYR.txt',header=True,index=False)
        data_mag.to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}/MAG.txt',header=True,index=False)
        data_baro.to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}/BARO.txt',header=True,index=False)
                    
        
    else:
        
        df=None
        mode_now=modes[0]
        index_begin=0
        count=1
        
        for index,mode in enumerate(modes):
            if mode!=mode_now:
                data_baro.iloc[index_begin:index-1,-1]=data_baro.iloc[index_begin:index-1,-1]-data_baro.iloc[index_begin,-1]
            
                df=pd.concat([data_acc.iloc[index_begin:index-1,:-1],data_gyr.iloc[index_begin:index-1,2:-1],data_mag.iloc[index_begin:index-1,2:-1],data_baro.iloc[index_begin:index-1,2:]],axis=1)      
                df.to_csv(f'../data_treat/data_interpolate/{folder}_{mode_now}_{count}.txt',header=True,index=False)
               
                
                
                if not os.path.exists(f'../data_treat/data_interpolate_base/{folder}_{mode}_{count}'):
                    os.makedirs(f'../data_treat/data_interpolate_base/{folder}_{mode}_{count}')        
                data_acc.iloc[index_begin:index-1,:].to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}_{count}/ACC.txt',header=True,index=False)
                data_gyr.iloc[index_begin:index-1,:].to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}_{count}/GYR.txt',header=True,index=False)
                data_mag.iloc[index_begin:index-1,:].to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}_{count}/MAG.txt',header=True,index=False)
                data_baro.iloc[index_begin:index-1,:].to_csv(f'../data_treat/data_interpolate_base/{folder}_{mode}_{count}/BARO.txt',header=True,index=False)
                            
                df=None
                index_begin=index
                mode_now=mode
                count+=1
                
"Step bis : visualize data"
        
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


def visu_data(chemin,file):
    
    data_acc=pd.read_csv(f'{chemin}/ACC.txt',header=0)
    data_gyr=pd.read_csv(f'{chemin}/GYR.txt',header=0)
    data_mag=pd.read_csv(f'{chemin}/MAG.txt',header=0)
    data_baro=pd.read_csv(f'{chemin}/BARO.txt',header=0)
    

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
    type_activite =parties[2] 
    print("Chemin:", chemin)
    print("Personne:", personne)
    print("Date:", date)
    print("Type d'activité:", type_activite)
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
    
    if not os.path.exists(f'../graphics/{str(type_activite)}/'):
            os.makedirs(f'../graphics/{str(type_activite)}/')
    
    plt.savefig(f'../graphics/{str(type_activite)}/{file}.png')
    plt.show()
    
        

"Step 4  Sort data according by step" 


def sort_data_by_step():
    print(f'Begin of the sort')
    save=False
    
    for fich in os.listdir('../data_treat/data_interpolate'):
        data=pd.read_csv(f'../data_treat/data_interpolate/{fich}')
        
        data['time']=data['time']-data['time'][0]
        
        data['nb_step']=data['nb_step']-data['nb_step'][0]
        
        mode=str(data['mode'][0])
        
        if mode=='elevator' or mode=='still' or mode=='escalator':
            
            data_step=data[data['nb_step']>3].reset_index(drop=True)
            if len(data_step)>0:
                unique,count=np.unique(np.array(data_step['nb_step']),return_counts=True)
                
                indice=np.where(count==max(count))[0]
                c=count[indice][0]
                u=unique[indice][0]
                if c>1000:
                    index=np.where(data['nb_step'].values==u)    
                    data=data.iloc[index]
                    data.reset_index(drop=True, inplace=True)
                    data['time']=data['time']-data['time'][0]
                    data['nb_step']=data['nb_step']-data['nb_step'][0]
             
                else:
                    print('')
                    
                save=True
        
        if mode=='stair' or mode=='walk':
            
            steps=list(data['nb_step'].astype(int).values)
            if steps[-1]==0 or steps[-1]==1 :
                save=False
            else:
                save=True
                
        if save ==True:
            if not os.path.exists('../data_treat/data_interpolate_sorted'):
                os.makedirs('../data_treat/data_interpolate_sorted')
            data.to_csv(f'../data_treat/data_interpolate_sorted/{fich.split(".")[0]}_sort.txt',header=True,index=False)
            
        
def visu_data_sorted(chemin,file):
    
    data=pd.read_csv(chemin)
    
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
    
"Step 5 separeted data by step or second"

def separted_data_by_seconde_or_step(fich):
    
    print(f'Begin cut by step or time for {fich}')
    name=fich.split('/')[-1]
    
    if not os.path.exists(f'../data_treat/data_cut'):
            os.makedirs(f'../data_treat/data_cut')
    if not os.path.exists(f'../data_sort_by_me/data_cut'):
            os.makedirs(f'../data_sort_by_me/data_cut')

    data=pd.read_csv(f'{fich}')
    
    time=data['time']
    
    indexes=range(0,int(max(time)),3)
    
    for i in range(0,len(indexes)-1):
        i_0=np.where(time.values>indexes[i])  
        i_1=np.where(time.values<indexes[i+1])
        
        indice_commun = np.intersect1d(i_0, i_1)
        
        data_cut = data.iloc[indice_commun, :]
        
        data_cut_pas=data_cut['nb_step'].astype(int).values
        
        nb_step_did=data_cut_pas[-1]-data_cut_pas[0]
        
        if nb_step_did<3:
            print(f'Cut by time')
            data_cut.to_csv(f'../data_treat/data_cut/{name.split(".")[0]}_cut_{i}.txt',index=False,header=False)
            data_cut.to_csv(f'../data_sort_by_me/data_cut/{name.split(".")[0]}_cut_{i}.txt',index=False,header=False)
            
        else:
            print(f'Cut by Step')
            unique_step=np.unique(data_cut_pas)
            ranging=list(range(unique_step[0],unique_step[len(unique_step)-1],2))
            for debut in ranging:
                indices_double_step=np.where(data_cut_pas==debut)[0]
                indices_double_step2=np.where(data_cut_pas==debut+1)[0]
                indices_double_step=np.concatenate((indices_double_step,indices_double_step2))
                data_cut_according_step = data.iloc[indices_double_step, :]
                data_cut_according_step.to_csv(f'../data_treat/data_cut/{name.split(".")[0]}_cut_step_{debut}.txt',index=False,header=False)
                data_cut_according_step.to_csv(f'../data_sort_by_me/data_cut/{name.split(".")[0]}_cut_step_{debut}.txt',index=False,header=False)
               
"Step 6 create the bat file thaht will lauch the feature extrcation with the cpp files"
def create_bat():
    print('Creation of the bat file')
    if os.path.exists(f'cpp/data_to_put_in_cpp'):
        shutil.rmtree(f'cpp/data_to_put_in_cpp')
    
    shutil.copytree(f'../data_sort_by_me/data_cut', f'cpp/data_to_put_in_cpp')
        

    fichier=os.listdir(f'cpp/data_to_put_in_cpp')
    
    with open("cpp/bat_all.bat", "w") as f:
        
        f.write("@echo off")
        f.write(f"{os.linesep}")
        f.write('g++ -o mon_executable main.cpp Sensors.cpp FeaturesCalculator.cpp Features.cpp')
        f.write(f"{os.linesep}")
        
        for fich in fichier:
            nom_output=f"{fich[0:-4]}.txt"
            f.write(f"mon_executable data_to_put_in_cpp/{fich} output_cpp/{nom_output}")
            f.write(f"{os.linesep}")

    print('Bat file created')



"Step 7 Lauch the bat file , (feature extraction)"

def lauch_bat_file():
    
    print('Begin feature extrcation, a cmd console will be open close it to continue')
    
    if os.path.exists(f'cpp/output_cpp'):
        shutil.rmtree(f'cpp/output_cpp')
        
    os.makedirs(f'cpp/output_cpp')
        
    
    commands_to_run = [
        'cd cpp',
        'bat_all'
    ]
    
    commands_concatenated = ' && '.join(commands_to_run)
    
    cmd_command = f'start cmd /k "{commands_concatenated}"'
    
    # subprocess.run(cmd_command, shell=True)
    import time
    process = subprocess.Popen(cmd_command, shell=True)
    while process.poll() is None:
        time.sleep(0.5)
    
def concetenate_outpu_cpp():
    fichiers=os.listdir('cpp/output_cpp')
    
    df=None
    
    for fich in fichiers:
        
        data=pd.read_csv(f'cpp/output_cpp/{fich}',delimiter=';')
        data=data.dropna(axis=1)
        
        df=pd.concat([df,data])
            
            
    df_stair=df[df['mode']=='stair']
    df_escalator=df[df['mode']=='escalator']
    df_still=df[df['mode']=='still']
    df_elevator=df[df['mode']=='elevator']
    df_walk=df[df['mode']=='walk']
    
    
    for i, col in enumerate(data.columns[1:]): 
        fig, axs = plt.subplots(5, 1, figsize=(10, 15))  
        fig.suptitle(f'Histograms for {col}', fontsize=16)
        x_max=max(df[col].values)+0.05*max(df[col].values)
        x_min=min(df[col].values)-0.05*min(df[col].values)
        if x_min==0:
            x_min=-5
        hist, bins = np.histogram(df[col].values, bins=30)
        y_max = hist.max()
    
    
        for j, label in enumerate(['stair', 'escalator', 'elevator', 'still', 'walk']):  # Loop through each mode
            df2 = df[df['mode'] == label] 
            axs[j].hist(df2[col].values, bins=30, label=label, alpha=0.7) 
            axs[j].set_title(f'Mode: {label}')  
            axs[j].set_xlabel(col) 
            axs[j].set_ylabel('Frequency')  
            axs[j].legend() 
            axs[j].set_xlim(x_min,x_max)
            axs[j].set_ylim(0,y_max)
            
        plt.tight_layout(rect=[0, 0, 1, 0.96]) 
        plt.show()  
        
        
    df.to_csv('../data_treat/df_output_cpp_concatenate.csv',header=True,index=False)
    
"Step 8 Feature selector"

def inputs():
    data=pd.read_csv('../data_treat/df_output_cpp_concatenate.csv')
    
    features=list(data.columns[1:])
    
    
    X = data.drop(columns=['mode'])
    
    X = X.values

    y , dict_label_numero=  pd.factorize(data['mode'])

    data['mode_numero']=y

    X_train_temp, X_test, y_train_temp, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    X_train, X_val, y_train, y_val = train_test_split(
        X_train_temp, y_train_temp, test_size=0.2, random_state=43
    )
    
    return X_train, X_val, y_train, y_val, X_test, y_test,X,y,features


def inputs_best(best_feature):
    data=pd.read_csv('../data_treat/df_output_cpp_concatenate.csv')
    
    features=best_feature
    best_feature.append('mode')
    
    data=data[best_feature]
    
    X = data.drop(columns=['mode'])
    X = X.values

    y , dict_label_numero=  pd.factorize(data['mode'])

    data['mode_numero']=y

    X_train_temp, X_test, y_train_temp, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    X_train, X_val, y_train, y_val = train_test_split(
        X_train_temp, y_train_temp, test_size=0.2, random_state=43
    )
    
    return X_train, X_val, y_train, y_val, X_test, y_test, X ,y,features

def score_ig():
    
    dict_ig=[]
    with open("../data_treat/feature_selector/information_gain_comparaison.txt", "w") as f:

        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        X,y,features=inputs()[-3:]
        
        ig = mutual_info_classif(X, y)
        
        ig_dict = {}
        for i in range(len(features)):
            
            ig_dict[features[i]] = ig[i]
            
            
        ig_dict_sorted = dict(sorted(ig_dict.items(), key=lambda item: item[1], reverse=True))
    
        
        selected_features_index_05 = np.where(np.array(list(ig_dict_sorted.values())[:])>0.5)
        selected_features=np.array(list(ig_dict_sorted.keys()))[selected_features_index_05]
        selected_value=np.array(list(ig_dict_sorted.values()))[selected_features_index_05]
        
        f.write(rf'  au dessus de 0.5 {len(selected_features)}:   {selected_features} \n {selected_value}')
        f.write(rf' {os.linesep}')
        
        
        sns.set(style="whitegrid")
        sns.set(rc={'figure.figsize':(17,8)})
        sns.barplot(x=list(ig_dict_sorted.values()), y=list(ig_dict_sorted.keys()))
        
        
        plt.title(f'Information Gain of Features')
        plt.xlabel('Information Gain')
        plt.ylabel('Feature Name')
        
        if not os.path.exists(f'graphics_feature_selector'):
            os.makedirs(f'graphics_feature_selector')
        
        plt.savefig(f'graphics_feature_selector/IG.png')
        plt.show()
        plt.close()
        
        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        dict_ig.append(ig_dict_sorted)
            
    return dict_ig



def scoring_cls(): 
    dict_cls=[]
    with open("../data_treat/feature_selector/cls_comparaison.txt", "w") as f:
        
        f.write(rf'    {os.linesep}')
        f.write(rf' {os.linesep}')
    
        
        X,y,features=inputs()[-3:]

        X=pd.DataFrame(X,columns=features)
        X['mode_numero']=y
        
        corr_matrix = X.corr()
        corr_with_target = corr_matrix['mode_numero']
        
        k = 10
        top_k = corr_with_target.abs().sort_values()
        
        indices_sup=np.where(np.array(top_k)>0.3)[0]
        
        f.write(f" au dessus de 0.3 {len(indices_sup)} : {top_k.index[indices_sup]} \n {top_k[indices_sup].values}")
        
        selected_features=X.iloc[:,indices_sup]
        
        sns.set(style="whitegrid")
        sns.set(rc={'figure.figsize':(20,12)})
        sns.barplot(x=np.array(top_k), y=list(top_k.index))
        
        
        plt.title(f'CLS')
        plt.xlabel('CLS')
        plt.ylabel('Feature Name')
        
        if not os.path.exists(f'graphics_feature_selector/CLS'):
            os.makedirs(f'graphics_feature_selector/CLS')
        
        plt.savefig(f'graphics_feature_selector/CLS.png')
        plt.show()
        plt.close()
        
        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        dict_cls.append(top_k.to_dict())
        
    return dict_cls



def scoring_tp(): 
    
    dict_tp=[]
    with open("../data_treat/feature_selector/tree_puning_comparaison.txt", "w") as f:
        
        f.write(rf'  {os.linesep}  {os.linesep}')
        f.write(rf' {os.linesep}')
        
        X,y,features=inputs()[-3:]
    
        clf = DecisionTreeClassifier(max_depth=16, random_state=8)
        clf.fit(X, y)
        
        importances = clf.feature_importances_
        
        tp_dict = {}
        for i in range(len(features)):
            tp_dict[features[i]] = importances[i]
     
        threshold = 0.020  
        
        indice=np.where(importances > threshold)
        features=np.array(features)
        selected_features = features[indice]
        importances_p=importances[indice]
        f.write('au dessus de 0.020 \n :')
        f.write(rf' {len(list(selected_features))} : {list(selected_features)} \n {importances_p}')
        
        sns.set(style="whitegrid")
        sns.set(rc={'figure.figsize':(17,8)})
        sns.barplot(x=importances,y=features)
        
        
        plt.title(f'Tree Puning ')
        plt.xlabel('Tree Puning')
        plt.ylabel('Feature Name')
        
        if not os.path.exists(f'graphics_feature_selector/TP'):
            os.makedirs(f'graphics_feature_selector/TP')
        
        plt.savefig(f'graphics_feature_selector/TP.png')
        plt.show()
        plt.close()
        
        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        dict_tp.append(tp_dict)
            
    return dict_tp


def feature_selector():
    
    if not os.path.exists('../data_treat/feature_selector'):
        os.makedirs('../data_treat/feature_selector')

    dict_ig=score_ig()
    dict_tp=scoring_tp()
    dict_cls=scoring_cls()
    
    keys=list(dict_tp[0].keys())
    
    
    df=pd.DataFrame(index=['Tree','CLS','IG','evaluation'],columns=keys)
    
    
    
    for col in keys:
        
        df.loc['Tree'][col]=dict_tp[0].get(col)
        df.loc['IG'][col]=dict_ig[0].get(col)
        df.loc['CLS'][col]=dict_cls[0].get(col)
        
    best=[]   
    for col in keys:
        
        if dict_tp[0].get(col)>np.mean(df.loc['Tree'].values) and dict_ig[0].get(col)>np.mean(df.loc['IG'].values) and dict_cls[0].get(col)>np.mean(df.loc['CLS'].values):
                
            df.loc['evaluation'][col]=True
            best.append(col)
        else:
            df.loc['evaluation'][col]=False
    
    
    print(f'The best feature are : {best}')
    df=df.T
    df=df.sort_index()
    
    
    
    df.to_csv('../data_treat/feature_selector/feature_selector_comparaison.txt',header=True,index=True)
    
    return best


"Step 9 Classifieur"

"Decision Tree"


def decision_tree_gini(data,criter,split,maxi_features,maxi_depth):
    
    X_train, X_val, y_train, y_val, X_test, y_test=data
    
    clf_gini = DecisionTreeClassifier(criterion=criter,splitter=split,max_depth=maxi_depth,max_features=maxi_features)
    
    clf_gini.fit(X_train, y_train)
    
    y_pred_gini = clf_gini.predict(X_test)
    
    
    model=clf_gini
    
    return accuracy_score(y_test, y_pred_gini)*100,clf_gini,X_train.shape[0]


def write_best_model(model,best_acc,t):
    if not os.path.exists('../data_treat/result_classifier/model'):
        os.makedirs('../data_treat/result_classifier/model')
    onnxfile = f'../data_treat/result_classifier/model/decisiontree_{"{0:.2f}".format(best_acc)}.onnx'
    print('Accuracy best Decision Tree: ',best_acc)
    initial_type = [('float_input', FloatTensorType([None,t]))]
    onnx_model = convert_sklearn(model, initial_types=initial_type, target_opset=12)
    with open(onnxfile, "wb") as f2:
        f2.write( onnx_model.SerializeToString())
    f2.close()
    
    
def decision_tree():
    
    if not os.path.exists('../data_treat/result_classifier'):
        os.makedirs('../data_treat/result_classifier')
 
    critere=['gini','entropy','log_loss']
    splitter=['best','random']
    max_depth=[None,5]
    max_features=[None,'sqrt','log2']
    
    best_acc=0
    
    with open("../data_treat/result_classifier/decision_tree_comparaison.txt", "w") as f:
        df=None
        f.write(rf'  {os.linesep}  {os.linesep}')
        f.write(rf'{os.linesep}')
        input=inputs()[0:6]
        
        
        best_para=[0,None]
        
        
        for criterion in critere:
            for split in splitter:
                for maxi_cara in max_features:
                    for depth in max_depth:
                        acc,model,t=decision_tree_gini(input,criterion,split,maxi_cara,depth)
                        
                        
                        if best_acc<acc:
                            best_criterion=criterion
                            best_split=split
                            best_maxi_cara=maxi_cara
                            best_dept=depth
                            best_acc=acc
                            best_para=[acc,best_criterion,best_split,best_maxi_cara,best_dept]
                            best_model=model
                            
    f.close()
                        
                            
    write_best_model(best_model,best_acc,t)



"XGboost"

def xgboost():

    X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
    
    X,y=inputs()[-4:-2]
    dict_label_numero=inputs()[-1]
    
    
    clf_xgb = XGBClassifier().fit(X_train, y_train)
    
    y_pred = clf_xgb.predict(X_test)
    predictions = [round(value) for value in y_pred]
    accuracy = accuracy_score(y_test, predictions)
    print("Accuracy: %.2f%%" % (accuracy * 100.0))
    
    incorrect_indices = np.where(y_pred != y_test)[0]
    
    for idx in incorrect_indices:
        sample = X_test[idx]
        true_label = y_test[idx]
        predicted_label = y_pred[idx]
    
    f_score = f1_score(y_test, y_pred, average='weighted')
    print("F-score:", f_score)
    
    conf_matrix = confusion_matrix(y_test, y_pred)
    
    onnx_model_path = f"../data_treat/result_classifier/model/xgboost_{'{0:.2f}'.format(accuracy)}.onnx"
    
    initial_type = [('float_input', FloatTensorType([None,X_train.shape[0]]))]
    
    onnx_model = onnxmltools.convert.convert_xgboost(clf_xgb, initial_types=initial_type, target_opset=8)
    onnx.save(onnx_model, onnx_model_path)


"DNN"
def dnn():
    
    import os
    os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
    
    #pip install tensorflow==2.15.0 tf2onnx==1.16.1 keras==2.15.0

    X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
    
    
    inpute = Input(shape=(X_train.shape[1],1))
    
    conv1 = Conv1D(300, 3, padding='valid', activation='relu')(inpute)
    conv2 = Conv1D(200, 3, padding='same', activation='relu')(conv1)
    conv3 = Conv1D(200, 3, padding='same', activation='relu')(conv2)
    conv4 = Conv1D(200, 3, padding='same', activation='relu')(conv3)
    conv5 = Conv1D(200, 3, padding='same', activation='relu')(conv4)
    
    flatten = Flatten()(conv5)
    
    batch_nor=BatchNormalization()(flatten)
    drop=Dropout(0.5)(batch_nor)
    
    dense1 = Dense(200, activation='relu')(drop)
    dense2 = Dense(100, activation='relu')(dense1)
    dense3 = Dense(50, activation='relu')(dense2)
    
    batch_nor2=BatchNormalization()(dense3)
    drop2=Dropout(0.5)(batch_nor2)
    
    dense4 = Dense(50, activation='relu')(drop2)
    dense5 = Dense(20, activation='relu')(dense4)
    dense6 = Dense(10, activation='relu')(dense5)
    
    output = Dense(5, activation='softmax')(dense6)
    
    model = Model(inputs=inpute, outputs=output)
    
    checkpoint = ModelCheckpoint(f"../data_treat/result_classifier/model/dnn_inter_model.keras", monitor='val_accuracy', save_best_only=True, mode='max', verbose=1)
    
    model.compile(optimizer='SGD',  loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    
    
    history = model.fit(
        X_train, y_train,
        epochs=100, batch_size=25,
        validation_data=(X_val, y_val),
        callbacks=[checkpoint]
    
    )
    
    loss = history.history['loss']
    val_loss = history.history['val_loss']
    acc = history.history['accuracy']
    val_acc = history.history['val_accuracy']
    
    plt.plot(loss, label='Training Loss')
    plt.plot(val_loss, label='Validation Loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.title('Training and Validation Loss')
    plt.legend()
    plt.show()
    
    plt.plot(acc, label='Training Accuracy')
    plt.plot(val_acc, label='Validation Accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.title('Training and Validation Accuracy DNN')
    plt.legend()
    plt.show()
    
    
    
    print("DNN accuracy : ",acc)
    
    # model.save('activity2.keras')
    
    best_model=load_model(f"../data_treat/result_classifier/model/dnn_inter_model.keras")
    
    loss,acc=best_model.evaluate(X_test,y_test)

    # print(tf.__version__)
    # print(tf2onnx.__version__)
    # print(keras.__version__)
    # import sys
    # print(sys.version)
    
    # best_model=model
    
    
    onnx_model, _ = tf2onnx.convert.from_keras(best_model,opset=11)
    
    with open(f"../data_treat/result_classifier/model/dnn_{'{0:.2f}'.format(acc)}.onnx", "wb") as f:
        f.write(onnx_model.SerializeToString())




if __name__ == '__main__':
    
    print(rf'{os.linesep}')
    fichiers = os.listdir('../data_original/zip')

    for fich in fichiers:
        if fich.endswith('.zip'):
            print(f'The file {fich} has been unzipped')
            unzip_file(fich)
            
    fichiers = os.listdir('../data_treat/unzip')
    
    print(rf'{os.linesep}')

    for fich in fichiers:
        print(f'Begin rename {fich}')
        rename_original_data(fich)
    
    
    print(rf'{os.linesep}')
    fichiers=os.listdir('../data_treat/rename')
    
    for folder in fichiers:
        print(rf'Begin to interpolate {folder}')
        interpolation_of_data_rename(f'{folder}')
    
    print(rf'{os.linesep}')
    
    fichiers=os.listdir('../data_treat/data_interpolate_base')
    
    input_visu_data=input('Do you want to see the data Y/N -> ')
    if input_visu_data.lower()=='y':
        for fich in fichiers:
            visu_data(f'../data_treat/data_interpolate_base/{fich}',fich)
        
    sort_data_by_step()
    
    print(rf'{os.linesep}')
    
    input_visu_data_sort=input('Do you want to see the data sorted Y/N -> ')
    if input_visu_data_sort.lower()=='y':
    
        fichiers=os.listdir('../data_treat/data_interpolate_sorted')
        
        for fich in fichiers:
            visu_data_sorted(f'../data_treat/data_interpolate_sorted/{fich}',fich)
            
            
    fichiers=os.listdir('../data_treat/data_interpolate_sorted')
    print(rf'{os.linesep}')
    
    for fich in fichiers:
        separted_data_by_seconde_or_step(f'../data_treat/data_interpolate_sorted/{fich}')
            
    print(rf'{os.linesep}')
    create_bat()
    print(rf'{os.linesep}')
    
    
    lauch_bat_file()
    
    print(rf'{os.linesep}')
    
    
    input_bat=input("Write ok when the cmd is over -> ")
    
    while input_bat.lower()!='ok':
        input_bat=input("Write ok when the cmd is over")
    
    print(rf'{os.linesep}')
    print('Concatenation des fichier de output cpp')
    
    print('visualisation histogramm feature')
    concetenate_outpu_cpp()
    
    
    
    print(rf'{os.linesep}')
    if os.path.exists(f'../data_treat/data_output_cpp'):
        shutil.rmtree(f'../data_treat/data_output_cpp')
        
        
    shutil.copytree(f'cpp/output_cpp', f'../data_treat/data_output_cpp')
    
    
    print(rf'{os.linesep}')
    print('Begin Feature Selector')
    best_features=feature_selector()
    
    input_best=inputs_best(best_features)
    
    if os.path.exists(f'../data_treat/result_classifier/model'):
        shutil.rmtree(f'../data_treat/result_classifier/model')
        
    os.makedirs('../data_treat/result_classifier/model')  
    
    print(rf'{os.linesep}')
    print('Begin Decision Tree')
    decision_tree()
    print(rf'{os.linesep}')
    print('Begin XGboost')
    xgboost()
    
    if not os.path.exists(f'../data_treat/result_classifier/model_save'):
        os.makedirs(f'../data_treat/result_classifier/model_save')
    
    for fich in os.listdir('../data_treat/result_classifier/model'):
        shutil.copy2(f'../data_treat/result_classifier/model/{fich}',f'../data_treat/result_classifier/model_save/{fich}')

