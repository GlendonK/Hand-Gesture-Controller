### This py file is to do ML with RandomForestClassifier training on the pi


from sklearn.ensemble import RandomForestClassifier
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split


# get path of data sets and combine them into 1 dataframe with pandas
up_path = 'newtrainingdata/up.csv'
down_path = 'newtrainingdata/down.csv'
left_path = 'newtrainingdata/left.csv'
right_path = 'newtrainingdata/right.csv'
uppercut_path = 'newtrainingdata/uppercut.csv'

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

# shift the next 8 rows of values into 1 row of 9 columns to represent a time series dataset.
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

# this loop is to drop the 8 rows of data that are shifted into columns
count = 0
num = 1
for i in range(4500):
    df = df.drop(df.index[num])
    count += 1
    if count >9:
        count = 0
        num +=1
df = df.dropna()
df.head(400)

# add headers of the newly created columns
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


# pitch data was not float, therefore change it to float like the rest of the data
df['pitch'] =df['pitch'].astype(float)
#df.dtypes
#import sys
#np.set_printoptions(threshold=sys.maxsize)

# features and label
X = df[features]
y = df['direction']


df['labels'] = df['direction'].astype('category').cat.codes # catergorize the labels into classes
y = df['labels']
X = X.to_numpy(dtype='float64')
y = y.to_numpy()

#split the dataset into training and test
from sklearn.model_selection import train_test_split

train_X, test_X, train_y, test_y = train_test_split(X,y,shuffle=True, test_size=0.2, stratify=y)

# define model and train
model = RandomForestClassifier(random_state=1)
model.fit(train_X, np.ravel(train_y))

# save the model
import pickle 
filename = "myModel.pkl"  

with open(filename, 'wb') as file:  
    pickle.dump(model, file)

