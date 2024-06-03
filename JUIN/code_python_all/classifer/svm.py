import os
import pandas as pd
from sklearn.svm import SVC
from make_input import inputs as inputs
from sklearn.model_selection import train_test_split
def inputs():
    data=pd.read_csv('../../data_treat/df_output_cpp_concatenate.csv')
    
    features=list(data.columns[1:])
    
    
    X = data.iloc[:,1:].values

    y , dict_label_numero=  pd.factorize(data['mode'])

    data['mode_numero']=y

    X_train_temp, X_test, y_train_temp, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    X_train, X_val, y_train, y_val = train_test_split(
        X_train_temp, y_train_temp, test_size=0.2, random_state=42
    )
    
    return X_train, X_val, y_train, y_val, X_test, y_test,X,y,features,dict_label_numero


def svm():
    best_acc=0
    with open("svm_comparaison.txt", "w") as f:
        df=None
        f.write(rf'  {os.linesep}  {os.linesep}')
        f.write(rf'{os.linesep}')
        
        
        
        X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
        
        params_grid = [{'kernel': ['rbf'], 'gamma': [1e-3, 1e-4],
                     'C': [1, 10, 100, 1000]},
                    {'kernel': ['linear'], 'C': [1, 10, 100, 1000]}]
        
        
        kernel = ['rbf', 'poly', 'sigmoid']
        gammas = [1e-3, 1e-4]
        cc = [1, 10, 100, 1000]
        degrees = [2, 3, 4] 
        coef0s = [0, 0.1, 0.5] 
        
        for ker in kernel:
            for gam in gammas:
                for c in cc:
                    if ker == 'poly':
                        for deg in degrees:
                            for coef in coef0s:
                                svm_model = SVC(kernel=ker, gamma=gam, C=c, degree=deg, coef0=coef)
                                svm_model.fit(X_train, y_train)
                                accuracy = svm_model.score(X_test, y_test)
                                print(f'Kernel: {ker}, Gamma: {gam}, C: {c}, Degree: {deg}, Coef0: {coef}, Accuracy: {accuracy}')
                                if accuracy>best_acc:
                                    best_acc=accuracy
                    elif ker == 'sigmoid':
                        for coef in coef0s:
                            svm_model = SVC(kernel=ker, gamma=gam, C=c, coef0=coef)
                            svm_model.fit(X_train, y_train)
                            accuracy = svm_model.score(X_test, y_test)
                            print(f'Kernel: {ker}, Gamma: {gam}, C: {c}, Coef0: {coef}, Accuracy: {accuracy}')
                            if accuracy>best_acc:
                                best_acc=accuracy
                    else:
                        svm_model = SVC(kernel=ker, gamma=gam, C=c)
                        svm_model.fit(X_train, y_train)
                        accuracy = svm_model.score(X_test, y_test)
                        print(f'Kernel: {ker}, Gamma: {gam}, C: {c}, Accuracy: {accuracy}')
                        if accuracy>best_acc:
                            best_acc=accuracy
    f.close()
    
    print(best_acc)
    
svm()