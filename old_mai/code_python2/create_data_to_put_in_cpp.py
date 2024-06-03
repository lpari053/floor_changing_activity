import os
import pandas as pd
import numpy as np

fichier=os.listdir('data_trie')

for fich in fichier:


    data_acc=pd.read_csv(f'data_trie/{fich}/ACC.txt',header=None)
    data_gyr=pd.read_csv(f'data_trie/{fich}/GYR.txt',header=None)
    data_mag=pd.read_csv(f'data_trie/{fich}/MAG.txt',header=None)
    data_baro=pd.read_csv(f'data_trie/{fich}/BARO.txt',header=None)
    data=np.column_stack((data_acc.iloc[:,:-1],data_gyr.iloc[:,2:5],data_mag.iloc[:,2:5],data_baro.iloc[:,2:5]))
    data=pd.DataFrame(data)
    data.columns=['mode','temps','acc_x','acc_y','acc_z','gyr_x','gyr_y','gyr_z','mag_x','mag_y','mag_z','baro','step']
    
    if not os.path.exists('cpp/data_to_put_in_cpp'):
        os.makedirs('cpp/data_to_put_in_cpp')
        
    data.to_csv(f'cpp/data_to_put_in_cpp/{fich}.txt',index=False,header=False,sep=',')