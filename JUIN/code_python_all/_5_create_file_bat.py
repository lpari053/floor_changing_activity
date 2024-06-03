"Importing libraries"
import zipfile
import os
import shutil
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math

# def rename_files_to_numbers(directory):
#     # Lister tous les fichiers dans le répertoire
#     files = os.listdir(directory)
    
#     # Trier les fichiers pour s'assurer qu'ils sont renommés dans un ordre spécifique
#     files.sort()
    
#     # Renommer chaque fichier en un numéro séquentiel
#     for i, filename in enumerate(files):
#         # Construire le nouveau nom de fichier
#         new_filename = f"{i + 1}{os.path.splitext(filename)[1]}"
        
#         # Chemin complet vers le fichier original et le nouveau fichier
#         src = os.path.join(directory, filename)
#         dst = os.path.join(directory, new_filename)
        
#         # Renommer le fichier
#         os.rename(src, dst)
        
#         print(f"Renamed {filename} to {new_filename}")

# # Utilisation de la fonction
# directory = 'cpp/data_to_put_in_cpp'
# rename_files_to_numbers(directory)


def create_bat():

    fichier=os.listdir(f'cpp/data_to_put_in_cpp')
    
    
    with open("cpp/bat_all.bat", "w") as f:
        
        f.write("@echo off")
        f.write(f"{os.linesep}")
        f.write('g++ -o mon_executable main.cpp Sensors.cpp FeaturesCalculator.cpp Features.cpp')
        f.write(f"{os.linesep}")
        
        # fich=fichier[0]
        # nom_output=f"{fich}"
        
        
        # f.write(f"mon_executable data_to_put_in_cpp/{fich} output_cpp/{nom_output}")
        # f.write(f"{os.linesep}")
        
        for fich in fichier:
            nom_output=f"{fich[0:-4]}.txt"
            f.write(f"mon_executable data_to_put_in_cpp/{fich} output_cpp/{nom_output}")
            f.write(f"{os.linesep}")
            
create_bat()