import os
import pandas as pd
import numpy as np

def sort_data_by_step():
    for fich in os.listdir('../data_treat/data_interpolate'):
        data=pd.read_csv(f'../data_treat/data_interpolate/{fich}')
        
        data['time']=data['time']-data['time'][0]
        
        data['nb_step']=data['nb_step']-data['nb_step'][0]
        
        mode=str(data['mode'][0])
        
        if mode=='elevator' or mode=='still' or mode=='escalator':
            
            data_step=data[data['nb_step']>3].reset_index(drop=True)
            if len(data_step)>0:
                # print(len(data_step),fich)
                
                unique,count=np.unique(np.array(data_step['nb_step']),return_counts=True)
                
                indice=np.where(count==max(count))[0]
                c=count[indice][0]
                u=unique[indice][0]
                if c>1000:
                    print('change')
                    index=np.where(data['nb_step'].values==u)    
                    print(len(data))
                    data=data.iloc[index]
                    data.reset_index(drop=True, inplace=True)
                    data['time']=data['time']-data['time'][0]
                    data['nb_step']=data['nb_step']-data['nb_step'][0]
                    print(len(data))
                else:
                    print(c,fich)
        
                    
        if not os.path.exists('../data_treat/data_interpolate_sorted'):
            os.makedirs('../data_treat/data_interpolate_sorted')
        data.to_csv(f'../data_treat/data_interpolate_sorted/{fich[0:-1]}_sort.txt',header=True,index=False)
                