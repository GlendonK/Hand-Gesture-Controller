import traceback
import time
import client
import pickle
import C_py_interface
import mlsocket
import client_thingsboard

def open_model_file():
    filename = 'pac_man.pkl'  #change model to change demo
    with open(filename, 'rb') as file:
        model_loaded = pickle.load(file)
        return model_loaded


def predict(dataArray, model_loaded):
    pred = model_loaded.predict(dataArray)
    return pred

if __name__ == "__main__":
    model = open_model_file()
    while True:
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
        except Exception as e:
            print(e)











