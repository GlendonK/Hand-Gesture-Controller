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
    if data == 0:
        key_press = 's'
        print('S')
    elif data == 1:
        key_press = 'a'
        print('A')
    elif data == 2:
        key_press = 'd'
        print('D')
    elif data == 3:
        key_press = 'w'
        print('W')
    elif data == 4:
        key_press = 'w, a, s, d'
        print('W, A, S, D')

























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