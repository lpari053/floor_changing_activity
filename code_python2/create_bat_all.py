import os
import pandas as pd
import numpy as np


fichier=os.listdir('cpp/data_to_put_in_cpp')

nb=['80','160','320','400']

with open("cpp/bat_all.bat", "w") as f:
    
    f.write("@echo off")
    f.write(f"{os.linesep}")
    f.write('g++ -o mon_executable main.cpp Sensors.cpp FeaturesCalculator.cpp Features.cpp fft.cpp')
    f.write(f"{os.linesep}")
    
    for n in nb:
    
        for fich in fichier:
            nom_output=f"{fich[0:-4]}"+f"_{n}.txt"
            f.write(f"mon_executable data_to_put_in_cpp/{fich} output_cpp/{nom_output} {n}")
            f.write(f"{os.linesep}")