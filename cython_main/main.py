import client
#import data_reader
import pickle
#import threading
import C_py_interface

def open_model_file():
    filename = 'myModel.pkl'  #change model to change demo
    with open(filename, 'rb') as file:
        model_loaded = pickle.load(file)
        return model_loaded


def predict(dataArray, model_loaded):
    pred = model_loaded.predict(dataArray)
    return pred

if __name__ == "__main__":
    model = open_model_file()
    while True:
        #data = data_reader.read_the_data()
        data = C_py_interface.py_dataReader()
        #print("THE ARRAY IS: ", data)

        results = predict(data, model)

        client.send_data(results)












