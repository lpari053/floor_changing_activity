import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from make_input import inputs as inputs

def scoring_cls(): 
    dict_cls=[]
    brute_norm=['brute_xyz']
    nb=['80','160','320','400']
    with open("cls_comparaison.txt", "w") as f:
        
        for n in nb:
            
            for bn in brute_norm:
            
                f.write(rf'    {os.linesep}')
                f.write(rf'{n} {os.linesep}')
            
                
                X=np.genfromtxt(f'data_input_feature_selector/{bn}/X_{bn}_{n}.txt',dtype=float,delimiter=';')
                y=np.genfromtxt(f'data_input_feature_selector/{bn}/y_{bn}_{n}.txt',dtype=int,delimiter=';')
                features=np.genfromtxt(f'data_input_feature_selector/{bn}/features_{bn}_{n}.txt',dtype=str,delimiter=';')
                
                X=pd.DataFrame(X,columns=features)
                X['mode_numero']=y
                
                corr_matrix = X.corr()
                corr_with_target = corr_matrix['mode_numero']
                
                k = 10
                top_k = corr_with_target.abs().sort_values()
                
                
                
                
                indices_sup=np.where(np.array(top_k)>0.3)[0]
                
                f.write(f" au dessus de 0.3 {len(indices_sup)} : {top_k.index[indices_sup]} \n {top_k[indices_sup].values}")
                
                selected_features=X.iloc[:,indices_sup]
                
                sns.set(style="whitegrid")
                sns.set(rc={'figure.figsize':(20,12)})
                sns.barplot(x=np.array(top_k), y=list(top_k.index))
                
                
                plt.title(f'CLS {n}')
                plt.xlabel('CLS')
                plt.ylabel('Feature Name')
                
                if not os.path.exists(f'../graphics_stat/CLS'):
                    os.makedirs(f'../graphics_stat/CLS')
                
                plt.savefig(f'../graphics_stat/CLS/CLS_{n}')
                plt.show()
                plt.close()
                
                f.write(rf' {os.linesep}')
                f.write(rf' {os.linesep}')
                
                dict_cls.append(top_k.to_dict())
        
    return dict_cls
                 