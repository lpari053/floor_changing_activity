import information_gain
import cls
import tree_puning
import os
import numpy as np
import pandas as pd
import pickle
score_ig=information_gain.score_ig()

score_cls=cls.scoring_cls()

score_tp=tree_puning.scoring_tp()

def txt_comparaison(score_ig, score_cls, score_tp):
    
    nb=['80','160','320','400']
  
    
    df=pd.DataFrame(index=score_ig[0].keys(),columns=['IG_80','IG_160','IG_320','IG_400',\
                                                   'CLS_80','CLS_160','CLS_320','CLS_400',\
                                                       'DT_80','DT_160','DT_320','DT_400'])
        
    df_all=pd.DataFrame(index=score_ig[0].keys(),columns=['IG_80','IG_160','IG_320','IG_400',\
                                                   'CLS_80','CLS_160','CLS_320','CLS_400',\
                                                       'DT_80','DT_160','DT_320','DT_400'])
        
    for a,key in enumerate(list(sorted(score_ig[0].keys()))):
        for i,n in enumerate(nb):
            ig=score_ig[i]
            cls=score_cls[i]
            tp=score_tp[i]
            
            df_all[f'IG_{n}'].loc[key]=ig.get(key)
            df_all[f'DT_{n}'].loc[key]=tp.get(key)
            df_all[f'CLS_{n}'].loc[key]=cls.get(key)
            
            if ig.get(key)>0.5:
                df[f'IG_{n}'].loc[key]=ig.get(key)
            if tp.get(key)>0.020:
                df[f'DT_{n}'].loc[key]=tp.get(key)
            if cls.get(key)>0.3:
                df[f'CLS_{n}'].loc[key]=cls.get(key)
                
                
    l=[]
    p=[]
    great_indice=[]
    zero_chose=[]
    for indice in df.index:
        l.append(df.loc[indice].notnull().sum())
        if df.loc[indice].notnull().sum()==0:
            zero_chose.append(indice)
        
        if df.loc[indice].notnull().sum()>=5:
            p.append('Yes')
            great_indice.append(indice)
            
        else:
            p.append('')
        
    df['nombre_not_nan']=l
    df['yes or no']=p
    
    df.to_csv('comparaison_trie.csv',sep=';')
    df_all.to_csv('comparaison_all.txt',sep=';')
    
    print(f'Great features chosen : {great_indice}')
    print(f'Not to chose : {zero_chose}')
    
    with open('great_features.pkl', 'wb') as f1:
        pickle.dump(great_indice,f1)
        
    with open('not_to_chose.pkl', 'wb') as f2:
        pickle.dump(zero_chose,f2)
    
    
    return df,df_all,l

df,df_all,l=txt_comparaison(score_ig, score_cls, score_tp)
