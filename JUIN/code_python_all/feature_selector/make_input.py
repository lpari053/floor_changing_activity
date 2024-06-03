import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import os
import seaborn as sns
from sklearn.feature_selection import mutual_info_classif
from sklearn.tree import DecisionTreeClassifier



def inputs():
    data=pd.read_csv('../data_treat/df_output_cpp_concatenate.csv')
    
    features=list(data.columns[1:])
    
    
    X = data.iloc[:,1:].values

    y , dict_label_numero=  pd.factorize(data['mode'])

    data['mode_numero']=y

    X_train_temp, X_test, y_train_temp, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    X_train, X_val, y_train, y_val = train_test_split(
        X_train_temp, y_train_temp, test_size=0.2, random_state=43
    )
    
    return X_train, X_val, y_train, y_val, X_test, y_test,X,y,features


def score_ig():
    
    dict_ig=[]
    with open("../data_treat/feature_selector/information_gain_comparaison.txt", "w") as f:

        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        X,y,features=inputs()[-3:]
        
        ig = mutual_info_classif(X, y)
        
        ig_dict = {}
        for i in range(len(features)):
            
            ig_dict[features[i]] = ig[i]
            
            
        ig_dict_sorted = dict(sorted(ig_dict.items(), key=lambda item: item[1], reverse=True))
    
        
        selected_features_index_05 = np.where(np.array(list(ig_dict_sorted.values())[:])>0.5)
        selected_features=np.array(list(ig_dict_sorted.keys()))[selected_features_index_05]
        selected_value=np.array(list(ig_dict_sorted.values()))[selected_features_index_05]
        
        f.write(rf'  au dessus de 0.5 {len(selected_features)}:   {selected_features} \n {selected_value}')
        f.write(rf' {os.linesep}')
        
        
        sns.set(style="whitegrid")
        sns.set(rc={'figure.figsize':(17,8)})
        sns.barplot(x=list(ig_dict_sorted.values()), y=list(ig_dict_sorted.keys()))
        
        
        plt.title(f'Information Gain of Features')
        plt.xlabel('Information Gain')
        plt.ylabel('Feature Name')
        
        if not os.path.exists(f'graphics_feature_selector'):
            os.makedirs(f'graphics_feature_selector')
        
        plt.savefig(f'graphics_feature_selector/IG.png')
        plt.show()
        plt.close()
        
        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        dict_ig.append(ig_dict_sorted)
            
    return dict_ig



def scoring_cls(): 
    dict_cls=[]
    with open("../data_treat/feature_selector/cls_comparaison.txt", "w") as f:
        
        f.write(rf'    {os.linesep}')
        f.write(rf' {os.linesep}')
    
        
        X,y,features=inputs()[-3:]

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
        
        
        plt.title(f'CLS')
        plt.xlabel('CLS')
        plt.ylabel('Feature Name')
        
        if not os.path.exists(f'graphics_feature_selector/CLS'):
            os.makedirs(f'graphics_feature_selector/CLS')
        
        plt.savefig(f'graphics_feature_selector/CLS.png')
        plt.show()
        plt.close()
        
        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        dict_cls.append(top_k.to_dict())
        
    return dict_cls



def scoring_tp(): 
    
    dict_tp=[]
    with open("../data_treat/feature_selector/tree_puning_comparaison.txt", "w") as f:
        
        f.write(rf'  {os.linesep}  {os.linesep}')
        f.write(rf' {os.linesep}')
        
        X,y,features=inputs()[-3:]
    
        clf = DecisionTreeClassifier(max_depth=16, random_state=8)
        clf.fit(X, y)
        
        importances = clf.feature_importances_
        
        tp_dict = {}
        for i in range(len(features)):
            tp_dict[features[i]] = importances[i]
     
        threshold = 0.020  
        
        indice=np.where(importances > threshold)
        features=np.array(features)
        selected_features = features[indice]
        importances_p=importances[indice]
        f.write('au dessus de 0.020 \n :')
        f.write(rf' {len(list(selected_features))} : {list(selected_features)} \n {importances_p}')
        
        sns.set(style="whitegrid")
        sns.set(rc={'figure.figsize':(17,8)})
        sns.barplot(x=importances,y=features)
        
        
        plt.title(f'Tree Puning ')
        plt.xlabel('Tree Puning')
        plt.ylabel('Feature Name')
        
        if not os.path.exists(f'graphics_feature_selector/TP'):
            os.makedirs(f'graphics_feature_selector/TP')
        
        plt.savefig(f'graphics_feature_selector/TP.png')
        plt.show()
        plt.close()
        
        f.write(rf' {os.linesep}')
        f.write(rf' {os.linesep}')
        
        dict_tp.append(tp_dict)
            
    return dict_tp


def feature_selector():
    
    if not os.path.exist('../data_treat/feature_selector'):
        os.makedirs('../data_treat/feature_selector')

    dict_ig=score_ig()
    dict_tp=scoring_tp()
    dict_cls=scoring_cls()
    
    keys=list(dict_tp[0].keys())
    
    
    df=pd.DataFrame(index=['Tree','CLS','IG','evaluation'],columns=keys)
    
    
    
    for col in keys:
        
        df.loc['Tree'][col]=dict_tp[0].get(col)
        df.loc['IG'][col]=dict_ig[0].get(col)
        df.loc['CLS'][col]=dict_cls[0].get(col)
        
    best=[]   
    for col in keys:
        
        if dict_tp[0].get(col)>np.mean(df.loc['Tree'].values) and dict_ig[0].get(col)>np.mean(df.loc['IG'].values) and dict_cls[0].get(col)>np.mean(df.loc['CLS'].values):
                
            df.loc['evaluation'][col]=True
            best.append(col)
        else:
            df.loc['evaluation'][col]=False
    
    df=df.T
    df=df.sort_index()
    
    
    
    df.to_csv('../data_treat/feature_selector/feature_selector_comparaison.txt',header=True,index=True)


