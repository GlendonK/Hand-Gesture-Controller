from sense_hat import SenseHat
from datetime import datetime
import time
import numpy as np
import pandas as pd

sense = SenseHat()



def get_data(acc, orientation, gyro):
    #acc = sense.get_accelerometer_raw()
    x = acc['x']
    y = acc['y']
    z = acc['z']
    #x= round(x, 4)
    #y= round(y, 4)
    #z= round(z, 4)
    #print('x: {} y: {} z: {}'.format(x,y,z))

    #orientation = sense.get_orientation()
    a = orientation['yaw']
    b = orientation['pitch']
    c = orientation['roll']
    #a= round(a, 4)
    #b= round(b, 4)
    #c= round(c, 4)
   #print('yaw: {} pitch: {} roll: {}'.format(a,b,c))

    #gyro = sense.get_gyroscope_raw()
    e = gyro['x']
    f = gyro['y']
    g = gyro['z']
    #print('e: {} f: {} g: {}'.format(e,f,g))
    #e= round(e, 4)
    #f= round(f, 4)
    #g= round(g, 4)


    arr =np.array([[x,y,z,e,f,g,a,b,c]])
    df = pd.DataFrame(arr,index=None,)
    df.to_csv('right.csv', mode='a', header=False, index=False)
    time.sleep(0.1)

data = []
acc = sense.get_accelerometer_raw()
orientation = sense.get_orientation()
gyro = sense.get_gyroscope_raw()


G = (0, 255, 0)
R = (255, 0, 0)
nothing = (0,0,0)


logo = [
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    R, R, R, R, R, R, R, R,
    ]

green = [
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    G, G, G, G, G, G, G, G,
    ]



sense.set_pixels(red)
time.sleep(3)
sense.set_pixels(green)
time.sleep(0.5)
count = 0
while(count < 10):
    get_data(acc, orientation, gyro)
    count = count+1
    print(count)