import mlsocket
import key_map

# Change the ip and port to your device ip and port
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
        #key_map.press_s()
        #key_map.snake_down_arrow()
        key_map.pacman_down()
        
        

    elif data == 1:
        #key_map.press_a()
        #key_map.snake_left_arrow()
        key_map.pacman_left()
        
        
    elif data == 2:
        #key_map.press_uppercut()
        print('1')
        
        

    elif data == 3:
        # resting, do nothing
        #key_map.press_r()
        print('0')
        

    elif data == 4:
       #key_map.press_d()
        #key_map.snake_right_arrow()
        key_map.pacman_right()
        

    elif data == 5:
        #key_map.press_w()
        #key_map.snake_up_arrow()
        key_map.pacman_up()
    

