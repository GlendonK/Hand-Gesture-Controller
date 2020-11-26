

import socket
import pickle
import mlsocket

HOST = '192.168.43.10'
PORT = 1234

# listen for the data to be sent over
with mlsocket.MLSocket() as s:
    s.bind((HOST, PORT))
    while True:
    
    
        
       
        s.listen()
        conn, address = s.accept()

        with conn:
            data = conn.recv(1024)
            print("TB REVEIVED: ", data)

