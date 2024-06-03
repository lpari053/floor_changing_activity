from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import GridSearchCV
import numpy as np
import pandas as pd
import os
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

X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
# Définir les paramètres à tester
param_grid = {
    'hidden_layer_sizes': [(50,), (100,), (50, 50)],
    'activation': ['tanh', 'relu'],
    'solver': ['sgd', 'adam'],
    'alpha': [0.0001, 0.001, 0.01],
    'learning_rate': ['constant', 'adaptive'],
    'learning_rate_init': [0.001, 0.01],
    'max_iter': [200, 400]
}

# Créer le classifieur MLP
mlp_model = MLPClassifier(random_state=42)

# Configuration de la recherche en grille
grid_search = GridSearchCV(estimator=mlp_model, param_grid=param_grid, cv=3, scoring='accuracy', verbose=1, n_jobs=-1)

# Entraînement avec recherche en grille
grid_search.fit(X_train, y_train)

# Meilleurs paramètres trouvés par la recherche en grille
print(f"Best parameters found: {grid_search.best_params_}")
print(f"Best accuracy: {grid_search.best_score_}")

# Utiliser les meilleurs paramètres pour faire des prédictions
best_mlp_model = grid_search.best_estimator_
accuracy = best_mlp_model.score(X_test, y_test)
print(f"Test accuracy: {accuracy}")