"""
File: _0_unzip_original_file.py

by Laura Parisot 24/05/2024

Contains 3 function:
    
    unzip_file(string,string)

"""

"Importing libraries"
import zipfile
import os
import shutil

"""

Function unzip_file(string,string):
    
This function Unzips the specified .zip file to the specified directory.

Input :
    zip_path (string): Path to the .zip file.
    extract_to (string): Path to the directory where files should be extracted. Defaults to the current directory.
    path_treat (string) : path to copy of folder that will be use for calculation
    
"""

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
    


   
if __name__ == '__main__':
    fichiers = os.listdir('../data_original/zip')

    for fich in fichiers:
        if fich.endswith('.zip'):
            print(f'The file {fich} has been unzipped')
            unzip_file(fich)


