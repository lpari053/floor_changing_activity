import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from make_input import inputs as inputs
import seaborn as sns



def scoring_tp(): 
    
    dict_tp=[]
    brute_norm=['brute_xyz']
    
    nb=['80','160','320','400']
    with open("tree_puning_comparaison.txt", "w") as f:
        
        for n in nb:
            for bn in brute_norm:
            
                f.write(rf'  {os.linesep}  {os.linesep}')
                f.write(rf'{n} {os.linesep}')
            
                X=np.genfromtxt(f'data_input_feature_selector/{bn}/X_{bn}_{n}.txt',dtype=float,delimiter=';')
                y=np.genfromtxt(f'data_input_feature_selector/{bn}/y_{bn}_{n}.txt',dtype=int,delimiter=';')
                features=np.genfromtxt(f'data_input_feature_selector/{bn}/features_{bn}_{n}.txt',dtype=str,delimiter=';')
                
                clf = DecisionTreeClassifier(max_depth=16, random_state=8)
                clf.fit(X, y)
                
                importances = clf.feature_importances_
                
                tp_dict = {}
                for i in range(len(features)):
                    tp_dict[features[i]] = importances[i]
             
                threshold = 0.020  
                
                indice=np.where(importances > threshold)
                
                selected_features = features[indice]
                importances_p=importances[indice]
                f.write('au dessus de 0.020 \n :')
                f.write(rf' {bn} {len(list(selected_features))} : {list(selected_features)} \n {importances_p}')
                
                sns.set(style="whitegrid")
                sns.set(rc={'figure.figsize':(17,8)})
                sns.barplot(x=importances,y=features)
                
                
                plt.title(f'Tree Puning {n}')
                plt.xlabel('Tree Puning')
                plt.ylabel('Feature Name')
                
                if not os.path.exists(f'../graphics_stat/TP'):
                    os.makedirs(f'../graphics_stat/TP')
                
                plt.savefig(f'../graphics_stat/TP/TP_{bn}_{n}.png')
                plt.show()
                plt.close()
                
                f.write(rf' {os.linesep}')
                f.write(rf' {os.linesep}')
                
                dict_tp.append(tp_dict)
            
    return dict_tp
 