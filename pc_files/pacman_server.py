import mlsocket
import key_map


HOST = '192.168.43.79'
PORT = 1234

while True:
    
    with mlsocket.MLSocket() as s:
        s.bind((HOST, PORT))
       
        s.listen()# listen for the data to be sent over and accept the data
        conn, address = s.accept()

        with conn:
            data = conn.recv(1024) # receive the data
                
    print('received: ', data)

    # to map directions to keyboard
    if data == 0:
        key_map.pacman_down()
        
        
    elif data == 1:
        key_map.pacman_left()
        

    elif data == 4:
        key_map.pacman_right()
        

    elif data == 5:
        key_map.pacman_up()
    

