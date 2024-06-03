
import os
import pandas as pd
from tensorflow.keras.layers import Input,Conv1D, MaxPooling1D, GlobalAveragePooling1D, Dense, Dropout, BatchNormalization,Flatten,GlobalMaxPooling1D
from tensorflow.keras.callbacks import ModelCheckpoint
from keras.models import load_model
from tensorflow.keras.models import Model
import numpy as np
import pickle
from sklearn.model_selection import train_test_split
import warnings
warnings.filterwarnings('ignore')


def inputs():
    data=pd.read_csv(f'../../data_treat/df_output_cpp_concatenate.csv')

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

def create_model(filters,opti,acti):
    X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
    inpute = Input(shape=(X_train.shape[1], 1))

    conv1 = Conv1D(filters[0], 3, padding='valid', activation='relu')(inpute)
    conv2 = Conv1D(filters[1], 3, padding='valid', activation='relu')(conv1)
    conv3 = Conv1D(filters[2], 3, padding='valid', activation='relu')(conv2)
    conv4 = Conv1D(filters[3], 3, padding='valid', activation='relu')(conv3)
    conv5 = Conv1D(filters[4], 3, padding='valid', activation='relu')(conv4)

    flatten = Flatten()(conv5)

    batch_nor = BatchNormalization()(flatten)
    drop = Dropout(0.5)(batch_nor)

    dense1 = Dense(200, activation=acti)(drop)
    dense2 = Dense(100, activation=acti)(dense1)
    dense3 = Dense(50, activation=acti)(dense2)

    batch_nor2 = BatchNormalization()(dense3)
    drop2 = Dropout(0.5)(batch_nor2)

    dense4 = Dense(50, activation=acti)(drop2)
    dense5 = Dense(20, activation=acti)(dense4)
    dense6 = Dense(10, activation=acti)(dense5)

    output = Dense(5, activation='softmax')(dense6)

    model = Model(inputs=inpute, outputs=output)
    return model

# Define different filter configurations to test
filter_configs = [
    [500, 400, 300, 200, 100],
    [400, 300, 200, 100, 50],
    [300, 200, 150, 100, 50],
    [600, 500, 400, 300, 200]
]
import tensorflow as tf
optimizers = [
    tf.keras.optimizers.SGD(learning_rate=0.01),
    tf.keras.optimizers.RMSprop(learning_rate=0.001, rho=0.9),
    tf.keras.optimizers.Adam(learning_rate=0.001, beta_1=0.9, beta_2=0.999),
    tf.keras.optimizers.Adagrad(learning_rate=0.01),
    tf.keras.optimizers.Adadelta(learning_rate=1.0, rho=0.95),
    tf.keras.optimizers.Adamax(learning_rate=0.002, beta_1=0.9, beta_2=0.999),
    tf.keras.optimizers.Nadam(learning_rate=0.002, beta_1=0.9, beta_2=0.999),
    tf.keras.optimizers.Ftrl(learning_rate=0.001, learning_rate_power=-0.5, initial_accumulator_value=0.1, l1_regularization_strength=0.0, l2_regularization_strength=0.0)
]
activations = ['relu', 'tanh', 'softsign', 'selu', 'elu', 'linear']

with open("comparaison_dnn.txt", "w") as f:
    for filters in filter_configs:
        for acti in activations:
            for opti in optimizers:
                
        
                X_train, X_val, y_train, y_val, X_test, y_test=inputs()[0:6]
                model = create_model(filters,opti,acti)
                model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    
                #print(f'Testing model with filters: {filters} {opti} {acti}')
            
                model.fit(X_train, y_train, epochs=20, validation_data=(X_val, y_val),verbose=0)
            
                # Evaluate the model
                loss, accuracy = model.evaluate(X_test, y_test)
                print(f'Test Accuracy: {accuracy}')
                
                
                f.write(f"{accuracy} {filters} {opti} {acti}")


f.close()