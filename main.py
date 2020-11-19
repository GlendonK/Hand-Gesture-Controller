## this file runs on the pi
## main program to run to start demo
import loadRandomForest
import client
import data_reader
import pickle

def open_model_file():
        filename = 'myModel.pkl'
        with open(filename, 'rb') as file:  
            model_loaded = pickle.load(file)
            return model_loaded

def predict(dataArray, model_loaded):
     pred = model_loaded.predict(dataArray)
     return pred
    
if __name__ == "__main__":
    while True:
        data = data_reader.read_the_data()
        model = open_model_file()

        results = predict(data, model)

        client.send_data(results)



    
    