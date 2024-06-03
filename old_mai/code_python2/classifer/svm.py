import os
import pandas as pd
from sklearn.svm import SVC
from make_input import inputs as inputs


pasx=['50','75','25']
nbs=['80','160','320','400']
    
with open("../txt_comparaison/svm_comparaison.txt", "w") as f:
    for p in pasx:
        for n in nbs:
            df=None
            for fich in os.listdir(f'../input_selector/{p}/{n}/'):
        
        
                f.write(rf'  {os.linesep}  {os.linesep}')
                f.write(rf'{p} {n} {os.linesep}')
                data=pd.read_csv(f'../input_selector/{p}/{n}/all/df.txt',header=0)
                X_train, X_val, y_train, y_val, X_test, y_test=inputs(data)
                
                params_grid = [{'kernel': ['rbf'], 'gamma': [1e-3, 1e-4],
                             'C': [1, 10, 100, 1000]},
                            {'kernel': ['linear'], 'C': [1, 10, 100, 1000]}]
                
                svm_model = SVC(kernel='rbf',gamma=10**(-3),C=1)
                svm_model.fit(X_train, y_train)
                
                accuracy=svm_model.score(X_test,y_test)
                print(accuracy)