import os
import pandas as pd
import numpy as np

def separted_data_by_seconde_or_step(fich):
    
    data=pd.read_csv(f'../data_sort_by_me/data_interpolate_sorted/{fich}')
    
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
            data_cut.to_csv(f'../data_sort_by_me/data_cut/{fich[:-4]}_cut_{i}.txt')
            
        else:
            unique_step=np.unique(data_cut_pas)
            ranging=list(range(unique_step[0],unique_step[len(unique_step)-1],2))
            for debut in ranging:
                indices_double_step=np.where(data_cut_pas==debut)[0]
                indices_double_step2=np.where(data_cut_pas==debut+1)[0]
                indices_double_step=np.concatenate((indices_double_step,indices_double_step2))
                data_cut_according_step = data.iloc[indices_double_step, :]
                data_cut_according_step.to_csv(f'../data_sort_by_me/data_cut/{fich[:-4]}_cut_step_{debut}.txt')



if __name__ == '__main__':
    
    if not os.path.exists('../data_sort_by_me/data_cut'):
        os.makedirs('../data_sort_by_me/data_cut')
    
    print(rf'debut')
    fichiers = os.listdir('../data_sort_by_me/data_interpolate_sorted')
    for fich in fichiers:
        separted_data_by_seconde_or_step(fich)
        
                    
                    
        