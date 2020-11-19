### this file runs on pc

import socket
import pickle
import mlsocket

HOST = '192.168.43.71'
PORT = 5000

# listen for the data to be sent over
while True:
    with mlsocket.MLSocket() as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, address = s.accept()

        with conn:
            data = conn.recv(1024)

    print('received: ', data)






















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