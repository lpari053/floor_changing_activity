import os
import numpy as np
import pandas as pd
from tensorflow.keras.layers import Input,Conv1D, MaxPooling1D, GlobalAveragePooling1D, Dense, Dropout, BatchNormalization,Flatten,GlobalMaxPooling1D
from tensorflow.keras.models import Model
from tensorflow.keras.callbacks import ModelCheckpoint


fichier=os.listdir(r'../cpp\data_to_put_in_cpp')

df=None

for fich in fichier:
    
    data=pd.read_csv(rf'../cpp\data_to_put_in_cpp\{fich}',header=None)

    
    data2=data.iloc[int(0.10*len(data)):int(0.90*len(data)),:]
    
    
    
    if df is None:
        
        df=data2
        
    else:
        
        df=pd.concat([df,data2],axis=0)
        
    
a,dict_numero=pd.factorize(df.iloc[:,0])


X=[]
y=[]
pas=range(0,len(df)-80,1)

for p in pas[:-1]:
    
    mode=np.array(a[p:p+80])
    
    if len(np.unique(mode))==1:
    
        d=np.array(df.iloc[p:p+80,2:],dtype=float)
        
        y.append(mode[0])
    
        X.append(d)
    

X=np.array(X)

from sklearn.model_selection import train_test_split
X_train_temp, X_test, y_train_temp, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

X_train, X_val, y_train, y_val = train_test_split(
    X_train_temp, y_train_temp, test_size=0.2, random_state=43
)
    
    
inpute = Input(shape=(X_train.shape))  

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

model = Model(inputs=inpute, outputs=output)

checkpoint_callback = ModelCheckpoint(
    filepath=f'model/model.keras',
    monitor='val_accuracy',
    save_best_only=True,
    mode='max'
)
 
model.compile(optimizer='SGD',  loss='sparse_categorical_crossentropy', metrics=['accuracy'])

history = model.fit(
    X_train, y_train,
    epochs=20, batch_size=250,
    validation_data=(X_val, y_val)
    
)

loss,acc=model.evaluate(X_test,y_test)









