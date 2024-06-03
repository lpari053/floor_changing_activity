import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import os
import seaborn as sns
from sklearn.feature_selection import mutual_info_classif


for fich in os.listdir(f'../../data_treat/rename/'):
    print(fich.split('_')[0] , fich)
    data_acc=pd.read_csv(f'../../data_treat/rename/{fich}/ACC.txt').iloc[:,1].values
    
    f=[]
    
    for u in range(0,len(data_acc)-1):
        
    
        temps_0=data_acc[u]
        temps_fin=data_acc[u+1]
    
        frequence=1/((temps_fin-temps_0))
        f.append(frequence)
    print('Frequence ACC:',np.mean(f))
    
for fich in os.listdir(f'../../data_treat/rename/'):
    print(fich.split('_')[0])
    data_acc=pd.read_csv(f'../../data_treat/rename/{fich}/BARO.txt').iloc[:,1].values
    
    temps_0=data_acc[0]
    temps_fin=data_acc[-1]
    
    frequence=1/((temps_fin-temps_0)/len(data_acc))
    print('Frequence BARO:',frequence)