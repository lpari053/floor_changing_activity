"""
File: _1_rename_original_data

by Laura Parisot 24/05/2024

Contains 1 function:
    
    rename_original_data(string (with default))

"""

#Importing libraries
import os 
import numpy as np
import shutil
import matplotlib.pyplot as plt
import pandas as pd
from _bis_interpolation_data_on_acc import interpolate_gyrmag as interpolation



"""
Function rename_original_data(string)

This function renames the folder of the original data by including the name of the smartphone user,
the activity practiced, and the date of the acquisition.

This function creates a new folder alongside the original data.

Input:
    
    personne: Name of the user of the smartphone that collected the data, which is by default established to be 'no_name'
    
Output:
    
    None
"""

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
                    per='no_name'
                else:
                    per=personne
                
                name=f'{fich}_{per}_{day}-{hour}'
                print(name)
                
                if not os.path.exists(f'../data_treat/rename/{name}'):
                    os.makedirs(f'../data_treat/rename/{name}')
                    
                for sensor in os.listdir(path_all):
                    shutil.copy2(f'{path_all}/{sensor}',f'../data_treat/rename/{name}')
        
        
        
if __name__ == '__main__':
    base1='../data_treat/unzip'
    fichiers = os.listdir('../data_treat/unzip')

    for fich in fichiers:
        rename_original_data(fich)
                    
                
                
                
    
