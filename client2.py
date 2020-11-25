
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


#data = s.recv(1024)

#print('received: ', repr(data))
