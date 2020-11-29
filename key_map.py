#import keyboard
import mouse
import timeit
#import loadModel
import pyautogui as key
#from pynput.keyboard import Key, Controller
import pydirectinput as keyboard
#from pynput.keyboard import Key, Controller
#keyboard = Controller()
def fighting_w():
    #keyboard.press_and_release('w')
    keyboard.keyDown('w')

    
def fighting_a():
    #keyboard.press_and_release('a')
    keyboard.keyDown('a')


def fighting_s():
    # keyboard.press_and_release('s')
    keyboard.keyDown('s')


def fighting_d():
    # keyboard.press_and_release('d') 
    keyboard.keyDown('d')


def fighting_punch():  
    keyboard.keyDown('j')

def fighting_rest():
    # keyboard.press_and_release('d')
    keyboard.keyUp('w')
    keyboard.keyUp('a')
    keyboard.keyUp('s')
    keyboard.keyUp('d')
    keyboard.keyUp('j')    



def snake_up_arrow():
    # keyboard.press_and_release('up')
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('up')


def snake_left_arrow():
    # keyboard.press_and_release('left')
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('left')


def snake_right_arrow():
    # keyboard.press_and_release('right')
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('right')


def snake_down_arrow():
    # keyboard.press_and_release('down')
    key.keyUp('up')
    key.keyUp('down')
    key.keyUp('left')
    key.keyUp('right')
    key.keyDown('down')


def pacman_down():
    # keyboard.press_and_release('down')
    key.press('down')

def pacman_up():
    # keyboard.press_and_release('down')
    key.press('up')

def pacman_left():
    # keyboard.press_and_release('down')
    key.press('left')

def pacman_right():
    # keyboard.press_and_release('down')
    key.press('right')



