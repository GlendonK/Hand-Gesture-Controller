import keyboard
import mouse
import timeit
#import loadModel

def map_w():
    keyboard.press_and_release('w') 

def map_a():
    keyboard.press_and_release('a')

def map_s():
    keyboard.press_and_release('s')

def map_d():
    keyboard.press_and_release('d')

def map_uppercut():
    keyboard.press_and_release('w, a, s, d')

def left_click():
    mouse.click('left')

def right_click():
    mouse.click('right')

def move_mouse(x,y):
    mouse.move(x, y, absolute=True, duration=0)





