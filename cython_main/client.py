import socket
import pickle
import mlsocket
import numpy as np
import C_py_interface


HOST = '192.168.43.71'
PORT = 5000

def send_data(data):
    
  # send the data to pc
    with mlsocket.MLSocket() as s:
        s.connect((HOST, PORT))
        s.send(data)




