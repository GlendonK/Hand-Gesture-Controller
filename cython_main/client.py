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
    





