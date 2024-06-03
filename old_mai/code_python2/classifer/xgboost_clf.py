import onnx
import onnxmltools
from onnxmltools.convert.common.data_types import FloatTensorType
from xgboost import XGBClassifier
import numpy as np
import pandas as pd
import os
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix

from make_input import inputs as inputs


        
bn='brute_xyz'

n='80'
put=pd.read_csv(fr'..\feature_selector\data_input_feature_selector\brute_xyz\input_{bn}_{n}.txt',index_col=None)
feature_choisi=[' acc_y_mean',' acc_y_std','acc_arc','fcc_y_sma',' acc_y_aad',' acc_z_sma','nb_step ',' baro_sma ']

X=np.array(put[feature_choisi])
y=np.array(put['mode_numero'])

X_train_temp, X_test, y_train_temp, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

X_train, X_val, y_train, y_val = train_test_split(
    X_train_temp, y_train_temp, test_size=0.2, random_state=43
)


clf_xgb = XGBClassifier().fit(X_train, y_train)

y_pred = clf_xgb.predict(X_test)
predictions = [round(value) for value in y_pred]
# evaluate predictions
accuracy = accuracy_score(y_test, predictions)
print("Accuracy: %.2f%%" % (accuracy * 100.0))

incorrect_indices = np.where(y_pred != y_test)[0]

for idx in incorrect_indices:
    sample = X_test[idx]
    true_label = y_test[idx]
    predicted_label = y_pred[idx]
    # print(f" Prédiction: {predicted_label}, Vraie valeur: {true_label}")

# for i in range(10):
#     sample = X_test[i].reshape(1, -1)  # XGBoost nécessite une forme (n_samples, n_features)
#     prediction = clf_xgb.predict(sample)
#     print(f"Échantillon {i+1}: Données = {sample}, Prédiction = {prediction}, Vraie valeur = {y_test[i]}")

f_score = f1_score(y_test, y_pred, average='weighted')
print("F-score:", f_score)

# Matrice de confusion
conf_matrix = confusion_matrix(y_test, y_pred)


onnx_model_path = "model/activity.onnx"

initial_type = [('float_input', FloatTensorType([None, 63]))]

onnx_model = onnxmltools.convert.convert_xgboost(clf_xgb, initial_types=initial_type, target_opset=8)
onnx.save(onnx_model, onnx_model_path)
