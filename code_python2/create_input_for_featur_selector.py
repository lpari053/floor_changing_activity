import os
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def make_X_y(norm):

    nb=['80','160','320','400']
    for n in nb:
        df=None
        for fich in os.listdir(r'cpp\output_cpp'):
            if norm==False:
                if 'norm' in fich:
                    pass
                else:
                    if n in fich:
                        data=pd.read_csv(f'cpp\output_cpp\{fich}',sep=';')
                        data['mode'] = data['mode'].astype(str).str.strip()
                        data['mode'] = data['mode'].str.replace('\s+', ' ', regex=True)
                        data['mode'] = data['mode'].replace('lift', 'elevator')
                    
                        
                        if df is None:
                            df=data
                        else:
                            df=pd.concat([df,data],axis=0)
                            
            if norm==True:
                if 'norm' in fich:
                    if n in fich:
                        data=pd.read_csv(f'cpp\output_cpp\{fich}',sep=';')
                        data['mode'] = data['mode'].astype(str).str.strip()
                        data['mode'] = data['mode'].str.replace('\s+', ' ', regex=True)
                        data['mode'] = data['mode'].replace('lift', 'elevator')
                    
                        
                        if df is None:
                            df=data
                        else:
                            df=pd.concat([df,data],axis=0)
                else:
                    pass
                    
        
        y , _=  pd.factorize(df['mode'])
        
        df['mode_numero']=y
        
        if norm==False:
        
            df.to_csv(fr'feature_selector\data_input_feature_selector\brute_xyz\input_brute_xyz_{n}.txt',header=True,index=False)
            
            df_all=pd.read_csv(fr'feature_selector\data_input_feature_selector\brute_xyz\input_brute_xyz_{n}.txt',header=0)
            
            features = df_all.columns[1:-1].astype(str).values
            
            X = df_all.iloc[:,1:-1].astype(float).values
            
            rows_with_nan = np.isnan(X).any(axis=1)
            
            X = X[~rows_with_nan]
            
            y =df_all['mode_numero'].astype(str).values
            
            y=y[~rows_with_nan]
            
            
            np.savetxt(fr'feature_selector\data_input_feature_selector\brute_xyz\X_brute_xyz_{n}.txt',X,delimiter=';',fmt='%1.4e')
            np.savetxt(fr'feature_selector\data_input_feature_selector\brute_xyz\y_brute_xyz_{n}.txt',y,delimiter=';', fmt="%s")
            np.savetxt(fr'feature_selector\data_input_feature_selector\brute_xyz\features_brute_xyz_{n}.txt',features,delimiter=';', fmt="%s")
            
        if norm==True:
            
            df.to_csv(fr'feature_selector\data_input_feature_selector\norm\input_norm_{n}.txt',header=True,index=False)
            
            df_all=pd.read_csv(fr'feature_selector\data_input_feature_selector\norm\input_norm_{n}.txt',header=0)
            
            features = df_all.columns[1:-1].astype(str).values
            
            X = df_all.iloc[:,1:-1].astype(float).values
            
            rows_with_nan = np.isnan(X).any(axis=1)
            
            X = X[~rows_with_nan]
            
            y =df_all['mode_numero'].astype(str).values
            
            y=y[~rows_with_nan]
            
            
            np.savetxt(fr'feature_selector\data_input_feature_selector\norm\X_norm_{n}.txt',X,delimiter=';',fmt='%1.4e')
            np.savetxt(fr'feature_selector\data_input_feature_selector\norm\y_norm_{n}.txt',y,delimiter=';', fmt="%s")
            np.savetxt(fr'feature_selector\data_input_feature_selector\norm\features_norm_{n}.txt',features,delimiter=';', fmt="%s")

make_X_y(False)