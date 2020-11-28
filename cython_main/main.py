import traceback
import time
import client
#import data_reader
import pickle
#import threading
import C_py_interface
import mlsocket
import client_thingsboard

def open_model_file():
    filename = 'pac_man4.pkl'  #change model to change demo
    with open(filename, 'rb') as file:
        model_loaded = pickle.load(file)
        return model_loaded


def predict(dataArray, model_loaded):
    pred = model_loaded.predict(dataArray)
    return pred

if __name__ == "__main__":
    model = open_model_file()
    while True:
       # time.sleep(1)
        #data = data_reader.read_the_data()
        data = C_py_interface.py_dataReader()
        #print("THE ARRAY IS: ", data)
        #C_py_interface.py_led(data)

        results = predict([data], model)
        
        try:
            client.send_data(results)
            #client.send_TB(results)
           #client_thingsboard.sendData(results[0])
            C_py_interface.py_led(results[0])
        except Exception as e:
            traceback.print_exc()
            break











