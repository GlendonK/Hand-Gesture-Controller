import mlsocket
import time


HOST = '192.168.43.79'
PORT = 1234

def send_data(data):
    
    
  # send the data to pc
    try:
        with mlsocket.MLSocket() as s:
            s.connect((HOST, PORT))
            s.send(data)

    except ConnectionRefusedError:
        print("reconnecting...")
        time.sleep(3)
        return
    except Exception as e:
        print("connection error...")
        print(e)
        return
         


