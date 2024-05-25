import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.feature_selection import mutual_info_classif

def score_ig():
    
    dict_ig=[]
    
    nb=['80','160','320','400']
    brute_norm=['brute_xyz']
    with open("information_gain_comparaison.txt", "w") as f:
        for n in nb:
            for bn in brute_norm:

                f.write(rf' {os.linesep}')
                f.write(rf'{n}   {os.linesep}')
        
                
                X=np.genfromtxt(f'data_input_feature_selector/{bn}/X_{bn}_{n}.txt',dtype=float,delimiter=';')
                y=np.genfromtxt(f'data_input_feature_selector/{bn}/y_{bn}_{n}.txt',dtype=int,delimiter=';')
                features=np.genfromtxt(f'data_input_feature_selector/{bn}/features_{bn}_{n}.txt',dtype=str,delimiter=';')
                
                ig = mutual_info_classif(X, y)
                
                ig_dict = {}
                for i in range(len(features)):
                    
                    ig_dict[features[i]] = ig[i]
                    
                    
                ig_dict_sorted = dict(sorted(ig_dict.items(), key=lambda item: item[1], reverse=True))
            
                
                selected_features_index_05 = np.where(np.array(list(ig_dict_sorted.values())[:])>0.5)
                selected_features=np.array(list(ig_dict_sorted.keys()))[selected_features_index_05]
                selected_value=np.array(list(ig_dict_sorted.values()))[selected_features_index_05]
                
                f.write(rf'  au dessus de 0.5 {bn} {len(selected_features)}:   {selected_features} \n {selected_value}')
                f.write(rf' {os.linesep}')
                
                
                sns.set(style="whitegrid")
                sns.set(rc={'figure.figsize':(17,8)})
                sns.barplot(x=list(ig_dict_sorted.values()), y=list(ig_dict_sorted.keys()))
                
                
                plt.title(f'Information Gain of Features {n}')
                plt.xlabel('Information Gain')
                plt.ylabel('Feature Name')
                
                if not os.path.exists(f'../graphics_stat/IG'):
                    os.makedirs(f'../graphics_stat/IG')
                
                plt.savefig(f'../graphics_stat/IG/IG_{bn}_{n}.png')
                plt.show()
                plt.close()
                
                f.write(rf' {os.linesep}')
                f.write(rf' {os.linesep}')
                
                dict_ig.append(ig_dict_sorted)
            
    return dict_ig
            