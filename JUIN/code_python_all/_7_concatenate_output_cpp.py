"Importing libraries"
import zipfile
import os
import shutil
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math


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