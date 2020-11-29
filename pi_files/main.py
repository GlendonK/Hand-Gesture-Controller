import traceback
import time
import client
import pickle
import C_py_interface
import mlsocket
import client_thingsboard
import time

def open_model_file():
    filename = 'pac_man.pkl'  #change model to change demo
    with open(filename, 'rb') as file:
        model_loaded = pickle.load(file)
        return model_loaded


def predict(dataArray, model_loaded):
    pred = model_loaded.predict(dataArray)
    return pred
def take_Break():
    t1 = 0
    print("Take A Break...")
    #break for 5s
    C_py_interface.py_rest()

if __name__ == "__main__":
    model = open_model_file()
    t0 = time.time()
    t1 = 0
    while True:
        # timer interrupt
        if t1 >30:
            
            t1 = time.time() - t0
            print("TIMER:\n ",t1)
            take_Break()
            t0 = time.time()
        # read data from sensors
        data = C_py_interface.py_dataReader() 
        # classify the data from the sensors
        results = predict([data], model)
        
        try:
            # send data to pc
            client.send_data(results)
            # send data to thingsboard
            client_thingsboard.sendData(results[0])
            # display led
            C_py_interface.py_led(results[0])
            t1 = time.time() - t0
            
            
            
        except Exception as e:
            traceback.print_exc()
            
        











