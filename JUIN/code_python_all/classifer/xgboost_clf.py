import onnx
import onnxmltools
from onnxmltools.convert.common.data_types import FloatTensorType
from xgboost import XGBClassifier
import numpy as np
import pandas as pd
import os
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix
from sklearn.model_selection import train_test_split
from make_input import inputs as inputs


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


def xgboost():

    X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
    
    X,y=inputs()[-4:-2]
    dict_label_numero=inputs()[-1]
    
    
    clf_xgb = XGBClassifier().fit(X_train, y_train)
    
    y_pred = clf_xgb.predict(X_test)
    predictions = [round(value) for value in y_pred]
    accuracy = accuracy_score(y_test, predictions)
    print("Accuracy: %.2f%%" % (accuracy * 100.0))
    
    incorrect_indices = np.where(y_pred != y_test)[0]
    
    for idx in incorrect_indices:
        sample = X_test[idx]
        true_label = y_test[idx]
        predicted_label = y_pred[idx]
    
    f_score = f1_score(y_test, y_pred, average='weighted')
    print("F-score:", f_score)
    
    conf_matrix = confusion_matrix(y_test, y_pred)
    
    y_pred2 = clf_xgb.predict(X)
    conf_matrix2 = confusion_matrix(y, y_pred2)
    
    onnx_model_path = "model/xgboost.onnx"
    
    initial_type = [('float_input', FloatTensorType([None,X_train.shape[0]]))]
    
    onnx_model = onnxmltools.convert.convert_xgboost(clf_xgb, initial_types=initial_type, target_opset=8)
    onnx.save(onnx_model, onnx_model_path)


X_train, X_val, y_train, y_val, X_test, y_test = inputs()[0:6]
X, y = inputs()[-4:-2]
dict_label_numero = inputs()[-1]

# Définition des valeurs à tester pour chaque paramètre
max_depths = [3, 5, 7]
learning_rates = [0.1, 0.01, 0.001]
n_estimators_values = [50, 100, 150]

# Variables pour suivre les meilleures performances et les meilleurs paramètres
best_accuracy = 0.0
best_params = None
best_model = None

# Boucle pour tester chaque combinaison de paramètres
for max_depth in max_depths:
    for learning_rate in learning_rates:
        for n_estimators in n_estimators_values:
            # Création du modèle XGBoost avec les paramètres spécifiés
            clf_xgb = XGBClassifier(max_depth=max_depth, learning_rate=learning_rate, n_estimators=n_estimators)
            clf_xgb.fit(X_train, y_train)
            
            # Prédiction sur l'ensemble de test
            y_pred = clf_xgb.predict(X_test)
            
            # Calcul de l'accuracy
            accuracy = accuracy_score(y_test, y_pred)
            print(f"max_depth={max_depth}, learning_rate={learning_rate}, n_estimators={n_estimators}, Accuracy: {accuracy * 100:.2f}%")
            
            # Vérification si les performances sont meilleures que les meilleures performances actuelles
            if accuracy > best_accuracy:
                best_accuracy = accuracy
                best_params = {'max_depth': max_depth, 'learning_rate': learning_rate, 'n_estimators': n_estimators}
                best_model = clf_xgb
                
                onnx_model_path = "model/xgboost.onnx"
                
                initial_type = [('float_input', FloatTensorType([None,X_train.shape[1]]))]
                
                onnx_model = onnxmltools.convert.convert_xgboost(clf_xgb, initial_types=initial_type, target_opset=8)
                onnx.save(onnx_model, onnx_model_path)

# Afficher les meilleurs paramètres et performances
print("Best Parameters:", best_params)
print("Best Accuracy:", best_accuracy)