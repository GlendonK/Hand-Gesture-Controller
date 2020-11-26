from sklearn.ensemble import RandomForestClassifier
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

up_path = 'newtrainingdata/up1.csv'
down_path = 'newtrainingdata/down1.csv'
left_path = 'newtrainingdata/left1.csv'
right_path = 'newtrainingdata/right1.csv'
#rest_path = 'newtrainingdata/rest1.csv'
punch_path = 'newtrainingdata/punch1.csv'

up_df = pd.read_csv(up_path)
down_df = pd.read_csv(down_path)
left_df = pd.read_csv(left_path)
right_df = pd.read_csv(right_path)
#rest_df = pd.read_csv(rest_path)
punch_df = pd.read_csv(punch_path)

df = up_df
df = df.append(down_df, ignore_index=True)
df = df.append(left_df, ignore_index=True)
df = df.append(right_df, ignore_index=True)
#df = df.append(rest_df, ignore_index=True)
df = df.append(punch_df, ignore_index=True)

#df = df.dropna(axis=1)
#df = df[['gyro_x','gyro_y','gyro_z','direction']]

def incrementTen(df):
    count=1
    df['acc_x+1'] = df['acc_x'].shift(-1)
    df['acc_y+1'] = df['acc_y'].shift(-1)
    df['acc_z+1'] = df['acc_z'].shift(-1)
    
    df['gyro_x+1'] = df['gyro_x'].shift(-1)
    df['gyro_y+1'] = df['gyro_y'].shift(-1)
    df['gyro_z+1'] = df['gyro_z'].shift(-1)
    
    '''df['pitch+1'] = df['pitch'].shift(-1)
    df['roll+1'] = df['roll'].shift(-1)
    df['yaw+1'] = df['yaw'].shift(-1)'''
    
    for i in range(8):
        df['acc_x+{}'.format(count+1)] = df['acc_x+{}'.format(count)].shift(-1)
        df['acc_y+{}'.format(count+1)] = df['acc_y+{}'.format(count)].shift(-1)
        df['acc_z+{}'.format(count+1)] = df['acc_z+{}'.format(count)].shift(-1)
        
        df['gyro_x+{}'.format(count+1)] = df['gyro_x+{}'.format(count)].shift(-1)
        df['gyro_y+{}'.format(count+1)] = df['gyro_y+{}'.format(count)].shift(-1)
        df['gyro_z+{}'.format(count+1)] = df['gyro_z+{}'.format(count)].shift(-1)
        
        '''df['pitch+{}'.format(count+1)] = df['pitch+{}'.format(count)].shift(-1)
        df['roll+{}'.format(count+1)] = df['roll+{}'.format(count)].shift(-1)
        df['yaw+{}'.format(count+1)] = df['yaw+{}'.format(count)].shift(-1)'''
        count +=1
        
    return df
incrementTen(df)

# this loop is to drop the 8 rows of data that are shifted into columns
count = 0
num = 1
for i in range(4491):
    df = df.drop(df.index[num])
    count += 1
    if count >9:
        count = 0
        num +=1
df = df.dropna()

features= ['acc_x','acc_y','acc_z','gyro_x','gyro_y', 'gyro_z']

for i in range(9):
    features.append('acc_x+{}'.format(i+1))
    features.append('acc_y+{}'.format(i+1))
    features.append('acc_z+{}'.format(i+1))
    
    features.append('gyro_x+{}'.format(i+1))
    features.append('gyro_y+{}'.format(i+1))
    features.append('gyro_z+{}'.format(i+1))

X = df[features]
y = df['direction']


df['labels'] = df['direction'].astype('category').cat.codes # catergorize the labels into classes
y = df['labels']
X = X.to_numpy(dtype='float64')
y = y.to_numpy()

from sklearn.model_selection import train_test_split

train_X, test_X, train_y, test_y = train_test_split(X,y,shuffle=True, test_size=0.3, stratify=y)

# define model and train
model = RandomForestClassifier(random_state=1)
model.fit(train_X, np.ravel(train_y))


# save the model
import pickle 
filename = "pac_man.pkl"  

with open(filename, 'wb') as file:  
    pickle.dump(model, file)

print(model.score(test_X, test_y))