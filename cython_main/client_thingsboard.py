import os
import time
import sys
import paho.mqtt.client as mqtt
import json
import mlsocket

HOST = '192.168.43.10'
PORT = 1234
THINGSBOARD_HOST = '129.126.163.157'
ACCESS_TOKEN = 'JioordtwqlLbge2BvNTZ'
topic = "v1/devices/me/telemetry"



next_reading = time.time() 

client = mqtt.Client()

# Set access token
client.username_pw_set(ACCESS_TOKEN)

# Connect to ThingsBoard using default MQTT port and 60 seconds keepalive interval
client.connect(THINGSBOARD_HOST, 1883, 60)

client.loop_start()

def sendData(dataReceived):
    data=dict()
    if dataReceived == 4:
        data["direction"] = "up"
        data["up"] = 1
        data_out=json.dumps(data) # create JSON object
        print("publish topic",topic, "data out= ", data_out)
        client.publish(topic,data_out,0)
        
    elif dataReceived == 0:
        data["direction"] = "down"
        data["down"] = 1
        data_out=json.dumps(data) # create JSON object
        print("publish topic",topic, "data out= ", data_out)
        client.publish(topic,data_out,0)
        
    elif dataReceived == 1:
        data["direction"] = "left"
        data["left"] = 1
        data_out=json.dumps(data) # create JSON object
        print("publish topic",topic, "data out= ", data_out)
        client.publish(topic,data_out,0)
        
    elif dataReceived == 2:
        data["direction"] = "right"
        data["right"] = 1
        data_out=json.dumps(data) # create JSON object
        print("publish topic",topic, "data out= ", data_out)
        client.publish(topic,data_out,0)
        
    elif dataReceived == 3:
        data["direction"] = "rest"
        data["rest"] = 1
        data_out=json.dumps(data) # create JSON object
        print("publish topic",topic, "data out= ", data_out)
        client.publish(topic,data_out,0)
        



