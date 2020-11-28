### this file runs on pc
### THIS SERVER IS FOR pac_man.pkl model


import flask
from flask.json import jsonify
import requests
import socket
import pickle
import mlsocket
import time
import key_map

UP = 0x49
DOWN = 0x50
RIGHT = 0x4D
LEFT = 0x4B

W = 0x11
A = 0x1E
S = 0x1F
D = 0x20

HOST = '192.168.43.71'
PORT = 5000

HOST_TB = '192.168.43.10'
PORT_TB = 1234


# listen for the data to be sent over
counter = 0
while True:
    
    with mlsocket.MLSocket() as s:
        s.bind((HOST, PORT))
       
        s.listen()
        conn, address = s.accept()

        with conn:
            data = conn.recv(1024)
        
        '''with mlsocket.MLSocket() as s2:
            s2.connect((HOST_TB, PORT_TB))
        
            #s2.sendall(data)'''
            
                

    print('received: ', data)
    if data == 0:
        key_press = 's'
        key_map.press_s()
        #key_map.move_mouse_down()
        #key_map.down_arrow()
        #key_map.PressKey(S)
        #key_map.ReleaseKey(S)
        
        print('0')

    elif data == 1:
        key_press = 'a'
        key_map.press_a()
                #key_map.move_mouse_left()
        #key_map.left_arrow()
        #key_map.PressKey(A)
        #key_map.ReleaseKey(A)
        print('1')
        
    elif data == 2:
        key_press = 'd'
        #key_map.move_mouse_right()
        #key_map.press_d()
        key_map.press_uppercut()
        print('2')
        

    elif data == 3:
        #key_press = 'w'
        #key_map.press_w()
        #key_map.move_mouse_up()
        #key_map.up_arrow()
        print('3')
        #time.sleep(0.1)
    elif data == 4:
        #key_press = 'w'
        #key_map.press_uppercut()
        key_map.press_d()
        #key_map.PressKey(D)
        #key_map.ReleaseKey(D)

        print('4')
    elif data == 5:
        #key_press = 'w'
        #key_map.press_uppercut()
        #key_map.up_arrow()
        key_map.press_w()
        #key_map.PressKey(W)
        #time.sleep(0.1)
        #key_map.ReleaseKey(W)

        print('5')



'''
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

except socket.error as err:
    print('socket.socket() {}'.format(err))

port = 5000
host_ip = '127.0.0.1'
s.bind((host_ip, port))
s.listen()
print('socket is listening')

while True:

    connection, addr = s.accept()
    print('connection from', addr)

    data = connection.recv(1024)

    if not data:
        break
    print('received: ', data)
s.close()
'''