### this file runs on pc
### THIS SERVER IS FOR pac_man.pkl model



    




import socket
import pickle
import mlsocket
import key_map as press

HOST = '192.168.43.71'
PORT = 5000

HOST_TB = '192.168.43.10'
PORT_TB = 1234


# listen for the data to be sent over
while True:
    
    with mlsocket.MLSocket() as s:
        s.bind((HOST, PORT))
       
        s.listen()
        conn, address = s.accept()

        with conn:
            data = conn.recv(1024)
        
        with mlsocket.MLSocket() as s2:
            s2.connect((HOST_TB, PORT_TB))
      
            s2.send(data)

    print('received: ', data)
    if data == 0:
        #key_press = 's'
        #key_map.press_s()
        #key_map.move_mouse_down()
        press.down_arrow()
        
        print('S')

    elif data == 1:
        #key_press = 'a'
        #key_map.press_a()
        #key_map.move_mouse_left()
        press.left_arrow()
        print('A')
    elif data == 2:
        #key_press = 'd'
        #key_map.move_mouse_right()
        #key_map.press_d()
        press.right_arrow()
        print('D')
    elif data == 3:
        #key_press = 'w'
        #key_map.press_w()
        #key_map.move_mouse_up()
        #press.up_arrow()
        print('R(W)')
    elif data == 4:
        #key_press = 'w, a, s, d'
        #key_map.press_uppercut()
        press.up_arrow()
        print('W(R)')




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