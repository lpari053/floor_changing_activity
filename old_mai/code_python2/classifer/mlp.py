import os
import pandas as pd
from tensorflow.keras.layers import Input,Conv1D, MaxPooling1D, GlobalAveragePooling1D, Dense, Dropout, BatchNormalization,Flatten,GlobalMaxPooling1D
from tensorflow.keras.callbacks import ModelCheckpoint
from keras.models import load_model
from tensorflow.keras.models import Model
import numpy as np
import pickle
from sklearn.model_selection import train_test_split
optimizers_choices = [
'SGD',
'RMSprop',
'Adagrad',
'Adadelta',
'Adam',
'Adamax',
'Nadam'
]
loss_choices = [
'sparse_categorical_crossentropy'
]

    
bn='brute_xyz'

n='80'
put=pd.read_csv(fr'..\feature_selector\data_input_feature_selector\brute_xyz\input_{bn}_{n}.txt',index_col=None)
feature_choisi=[' acc_y_mean',' acc_y_std','acc_arc','fcc_y_sma',' acc_y_aad',' acc_z_sma']

X=np.array(put[feature_choisi])
y=np.array(put['mode_numero'])

X_train_temp, X_test, y_train_temp, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

X_train, X_val, y_train, y_val = train_test_split(
    X_train_temp, y_train_temp, test_size=0.2, random_state=43
)


inpute = Input(shape=(X_train.shape[1],1))  

conv1 = Conv1D(300, 3, padding='valid', activation='relu')(inpute)
conv2 = Conv1D(200, 3, padding='same', activation='relu')(conv1)
conv3 = Conv1D(200, 3, padding='same', activation='relu')(conv2)
conv4 = Conv1D(200, 3, padding='same', activation='relu')(conv3)
conv5 = Conv1D(200, 3, padding='same', activation='relu')(conv4)

flatten = Flatten()(conv5)

batch_nor=BatchNormalization()(flatten)
drop=Dropout(0.5)(batch_nor)

dense1 = Dense(200, activation='relu')(drop)
dense2 = Dense(100, activation='relu')(dense1)
dense3 = Dense(50, activation='relu')(dense2)

batch_nor2=BatchNormalization()(dense3)
drop2=Dropout(0.5)(batch_nor2)

dense4 = Dense(50, activation='relu')(drop2)
dense5 = Dense(20, activation='relu')(dense4)
dense6 = Dense(10, activation='relu')(dense5)

output = Dense(5, activation='softmax')(dense6)

best_acc=0

for opti in optimizers_choices:  

    model = Model(inputs=inpute, outputs=output)

    checkpoint_callback = ModelCheckpoint(
        filepath=f'model/model.keras',
        monitor='val_accuracy',
        save_best_only=True,
        mode='max'
    )
     
    model.compile(optimizer=opti,  loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    
    history = model.fit(
        X_train, y_train,
        epochs=20, batch_size=250,
        validation_data=(X_val, y_val)
        
    )
    
    loss,acc=model.evaluate(X_test,y_test)
    
    print(fr'{acc} {opti}')
    
    if acc>best_acc:
        best_acc=acc
        model.save(rf'model/model_{acc}.keras')
        
        

from tensorflow.keras.models import load_model
best_model = load_model(rf'model/model_{best_acc}.keras')

import tensorflow as tf
import tf2onnx

onnx_model, _ = tf2onnx.convert.from_keras(best_model,opset=11)

with open(rf"Ce PC\Galaxy de Laura\Stockage interne\Android\data\fr.univeiffel.geolocimu\files\Geoloc\onnx\activity.onnx", "wb") as f:
    f.write(onnx_model.SerializeToString())


    

            