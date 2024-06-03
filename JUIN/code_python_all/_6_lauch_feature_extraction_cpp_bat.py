"Importing libraries"
import zipfile
import os
import shutil
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import subprocess

def create_bat():
    
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
            
create_bat()
import subprocess

commands_to_run = [
    'cd cpp',
    'bat_all'
]

commands_concatenated = ' && '.join(commands_to_run)

cmd_command = f'start cmd /k "{commands_concatenated}"'

# Exécute la commande
subprocess.run(cmd_command, shell=True)