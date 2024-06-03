import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split

def inputs(data):
    X = data.iloc[:,0:-1].values
    
    rows_with_nan = np.isnan(X).any(axis=1)
    
    X = X[~rows_with_nan]
    
    y , _=  pd.factorize(data['mode'])
    
    y=y[~rows_with_nan]
    
    X_train_temp, X_test, y_train_temp, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )
    
    X_train, X_val, y_train, y_val = train_test_split(
        X_train_temp, y_train_temp, test_size=0.2, random_state=43
    )
    
    return X_train, X_val, y_train, y_val, X_test, y_test