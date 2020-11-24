## this file runs on pi

import socket
import pickle
import mlsocket
import numpy as np



HOST = '192.168.43.71'
PORT = 5000

def send_data(data):
  # send the array to server
  with mlsocket.MLSocket() as s:
      s.connect((HOST, PORT))
      
      s.send(data)
    

   






















'''
host_ip = '127.0.0.1'
port = 5000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((host_ip, port))
s.sendall(b'2000')
#data = s.recv(1024)

#print('received: ', repr(data))
'''