from sense_hat import SenseHat
from datetime import datetime
import time
import numpy as np
#import pandas as pd

sense = SenseHat()



def read_the_data():
    timeData = []
    acc = sense.get_accelerometer_raw()
    orientation = sense.get_orientation()
    gyro = sense.get_gyroscope_raw()

    while len(timeData) != 10:
        
        x = acc['x']
        y = acc['y']
        z = acc['z']

        a = orientation['yaw']
        b = orientation['pitch']
        c = orientation['roll']

        e = gyro['x']
        f = gyro['y']
        g = gyro['z']
        

        timeData.append(x)
        timeData.append(y)
        timeData.append(z)
        
        timeData.append(e)
        timeData.append(f)
        timeData.append(g)

        timeData.append(a)
        timeData.append(b)
        timeData.append(c)

        

        

    return np.asarray(timeData)





     