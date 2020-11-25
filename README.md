# Hand-Gesture-Controller

#### Gradeuskindly

### Installation Guide
Make sure to have Raspberrypi 3B+ with sensehat, python3.5 installed on pi.

#### 1. Install necessary packages
  * pip3 install scikit-learn
  * (explain how install cython)

#### 2. git clone this repo on pi and pc
  * on the pi, cd to cython_main after cloning

#### 3. Train Machine Learning Model
  * run pacman_train.py with python3
  * wait until training is done. (might take awhile)

#### 4. Start the server and clients
  * on pc, run ``` python run pacman_server.py ``` on cmd
  * on pi, run ``` python3 main.py ```

#### 5. Play pac-man
  * attach pi to glove and wear glove.
  * tilt hand up to go up, tilt down to go down
  * rotate hand left to go left, rotate hand right to go right
