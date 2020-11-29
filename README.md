# Hand Gesture Controller
### Gradeuskindly
---
### Requirements
1. i2c 3.1.2 on pi (compile with -li2c if undefined reference to smbus functions)
2. python 3.5.3 on pi
3. numpy 1.17 , pip3 install==1.17 on pi
4. pandas 0.25.3 , pip3 install=0.25.3 on pi
5. cython , pip3 install cython on pi
6. pickle , pip3 install pickle on pi and pc
7. mlsocket , pip3 install mlsocket on pi and pc
8. sci-kit learn 0.22.2.post1 , pip3 install -U scikit-learn on pi
9. pydirectinput , pip3 install pydirectinput on pc
10. pyautogui , pip3 install pyautogui on pc
11. paho , pip3 install paho
---
### Installation Guide
1. git clone this repo into pi and pc
2. run game server file on pc, make sure host ip and port number is same for pi client.py and game server.
3. run main.py on pi
4. play game