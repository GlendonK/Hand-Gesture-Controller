import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras import layers
from tensorflow import keras

up_path = 'newtrainingdata/up2.csv'
down_path = 'newtrainingdata/down2.csv'
left_path = 'newtrainingdata/left2.csv'
right_path = 'newtrainingdata/right2.csv'
uppercut_path = 'newtrainingdata/rest2.csv'

up_df = pd.read_csv(up_path)
down_df = pd.read_csv(down_path)
left_df = pd.read_csv(left_path)
right_df = pd.read_csv(right_path)
uppercut_df = pd.read_csv(uppercut_path)

df = up_df
df = df.append(down_df, ignore_index=True)
df = df.append(left_df, ignore_index=True)
df = df.append(right_df, ignore_index=True)
df = df.append(uppercut_df, ignore_index=True)

def incrementTen(df):
    count=1
    df['acc_x+1'] = df['acc_x'].shift(-1)
    df['acc_y+1'] = df['acc_y'].shift(-1)
    df['acc_z+1'] = df['acc_z'].shift(-1)
    
    df['gy_x+1'] = df['gy_x'].shift(-1)
    df['gy_y+1'] = df['gy_y'].shift(-1)
    df['gy_z+1'] = df['gy_z'].shift(-1)
    
    df['pitch+1'] = df['pitch'].shift(-1)
    df['roll+1'] = df['roll'].shift(-1)
    df['yaw+1'] = df['yaw'].shift(-1)
    
    for i in range(8):
        df['acc_x+{}'.format(count+1)] = df['acc_x+{}'.format(count)].shift(-1)
        df['acc_y+{}'.format(count+1)] = df['acc_y+{}'.format(count)].shift(-1)
        df['acc_z+{}'.format(count+1)] = df['acc_z+{}'.format(count)].shift(-1)
        
        df['gy_x+{}'.format(count+1)] = df['gy_x+{}'.format(count)].shift(-1)
        df['gy_y+{}'.format(count+1)] = df['gy_y+{}'.format(count)].shift(-1)
        df['gy_z+{}'.format(count+1)] = df['gy_z+{}'.format(count)].shift(-1)
        
        df['pitch+{}'.format(count+1)] = df['pitch+{}'.format(count)].shift(-1)
        df['roll+{}'.format(count+1)] = df['roll+{}'.format(count)].shift(-1)
        df['yaw+{}'.format(count+1)] = df['yaw+{}'.format(count)].shift(-1)
        count +=1
        
    return df
incrementTen(df)


count = 0
num = 1
for i in range(4500):
    df = df.drop(df.index[num])
    count += 1
    if count >9:
        count = 0
        num +=1
df = df.dropna()

features= ['acc_x','acc_y','acc_z','gy_x','gy_y', 'gy_z', 'pitch', 'roll', 'yaw' ]

for i in range(9):
    features.append('acc_x+{}'.format(i+1))
    features.append('acc_y+{}'.format(i+1))
    features.append('acc_z+{}'.format(i+1))
    
    features.append('gy_x+{}'.format(i+1))
    features.append('gy_y+{}'.format(i+1))
    features.append('gy_z+{}'.format(i+1))
    
    features.append('pitch+{}'.format(i+1))
    features.append('roll+{}'.format(i+1))
    features.append('yaw+{}'.format(i+1))

#print(features)



df['pitch'] =df['pitch'].astype(float)
#df.dtypes
#import sys
#np.set_printoptions(threshold=sys.maxsize)


X = df[features]
y = df['direction']

df['labels'] = df['direction'].astype('category').cat.codes
y = df['labels']
X = X.to_numpy(dtype='float64')
y = y.to_numpy()
from sklearn.model_selection import train_test_split
from keras.utils import to_categorical
from keras.utils import np_utils

train_X, test_X, train_y, test_y = train_test_split(X,y,shuffle=True, test_size=0.2, stratify=y)
train_y = np_utils.to_categorical(train_y)
test_y1 = np_utils.to_categorical(test_y)

#train_X1 = X.to_numpy(dtype='float64')
#train_y1 = y.to_numpy()

from keras.utils import np_utils
train_X = train_X.reshape(392,90,1)
train_y = train_y.reshape(392,5)
test_X = test_X.reshape(99,90,1)
test_y1 = test_y1.reshape(99,5)
#train_y = np_utils.to_categorical(train_y, 4)

model = keras.Sequential()
model.add(layers.BatchNormalization())
model.add(layers.Conv1D(filters=32, kernel_size=3 ,strides=1,activation= 'relu', padding='SAME'))
model.add(layers.MaxPooling1D(pool_size=2))
model.add(layers.Flatten())
model.add(layers.Dense(32, activation='relu'))
model.add(layers.Dropout(rate=0.1))
model.add(layers.Dense(32, activation='relu'))
model.add(layers.Dense(16, activation='relu'))
#model.add(layers.MaxPooling1D(pool_size=2))
model.add(layers.Dense(5, activation='softmax'))

model.compile(optimizer='adam',
             loss='categorical_crossentropy',
             metrics=['accuracy'])

early_stopping = keras.callbacks.EarlyStopping(patience=50, min_delta= 0.001,
                                              restore_best_weights=True)

import tensorflow as tf
history=model.fit(train_X, train_y,
         validation_data = (test_X, test_y1),
         epochs=200,
         batch_size=100,
         callbacks=[early_stopping]
                 )


model.save('pac_man_cnn.h5')
    