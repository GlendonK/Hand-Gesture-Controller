## this file runs on pi

import socket
import pickle
import mlsocket
import numpy as np
import C_py_interface


HOST = '192.168.43.71'
PORT = 5000

HOST_TB = '192.168.43.10'
PORT_TB =1234


def send_data(data):
    
  # send the array to server
    with mlsocket.MLSocket() as s:
        s.connect((HOST, PORT))
        s.send(data)
     # C_py_interface.py_led(data)
    
def send_TB(data):
    with mlsocket.MLSocket() as s:
        s.connect((HOST_TB, PORT_TB))
      
        s.send(data)




