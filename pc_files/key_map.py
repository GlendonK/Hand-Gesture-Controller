import timeit
import pyautogui as key
import pydirectinput as keyboard

#function to execute directions for specific games
def fighting_w():
    keyboard.keyDown('w') #keydown holds down the key

    
def fighting_a():
    keyboard.keyDown('a')


def fighting_s():
    keyboard.keyDown('s')


def fighting_d():
    keyboard.keyDown('d')


def fighting_punch():  
    keyboard.keyDown('j')

def fighting_rest():
    keyboard.keyUp('w') # keyup release the down key
    keyboard.keyUp('a')
    keyboard.keyUp('s')
    keyboard.keyUp('d')
    keyboard.keyUp('j')    


#function for snake game movement
def snake_up_arrow():
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('up')


def snake_left_arrow():
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('left')


def snake_right_arrow():
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('right')


def snake_down_arrow():
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('down')


#function for pacman movement
def pacman_down():
    key.press('down')

def pacman_up():
    key.press('up')

def pacman_left():
    key.press('left')

def pacman_right():
    key.press('right')



