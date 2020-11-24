# this file runs on the pi
# main program to run to start demo
import client
import data_reader
import pickle
import threading
import thingsboard_client as tbc

def open_model_file():
    filename = 'myModel.pkl'  #change model to change demo
    with open(filename, 'rb') as file:
        model_loaded = pickle.load(file)
        return model_loaded


def predict(dataArray, model_loaded):
    pred = model_loaded.predict(dataArray)
    return pred

thingsboard_client = threading.Thread(tbc.send_data(),target=None,daemon=True)

if __name__ == "__main__":
    model = open_model_file()
    while True:
        data = data_reader.read_the_data()

        results = predict(data, model)

        client.send_data(results)
