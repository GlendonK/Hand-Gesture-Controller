'''
import socket



client_ip = '192.168.43.10'
client_port = 3000
s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


s1.bind((client_ip, client_port))
s1.listen()
while True:

    connection, addr = s1.accept()
    print('connection from', addr)

    hostdata = connection.recv(1024)
    
    
    print('received: ', hostdata)
s1.close()
'''

import socket
import pickle
import mlsocket
import key_map as press

HOST = '192.168.43.10'
PORT = 3000

# listen for the data to be sent over
while True:
    
    with mlsocket.MLSocket() as s:
        s.bind((HOST, PORT))
       
        s.listen()
        conn, address = s.accept()

        with conn:
            data = conn.recv(1024)
            print("thingsboard received: ",data)
        
        