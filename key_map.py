import keyboard
import mouse
import timeit
#import loadModel

def press_w():
    keyboard.press_and_release('w') 

def press_a():
    keyboard.press_and_release('a')

def press_s():
    keyboard.press_and_release('s')

def press_d():
    keyboard.press_and_release('d')

def press_uppercut():
    keyboard.press_and_release('w, a, s, d')

def up_arrow():
    keyboard.press_and_release('up')

def left_arrow():
    keyboard.press_and_release('left')

def right_arrow():
    keyboard.press_and_release('right')

def down_arrow():
    keyboard.press_and_release('down')

def left_click():
    mouse.click('left')

def right_click():
    mouse.click('right')

def move_mouse(x,y):
    mouse.move(x, y, absolute=False, duration=0)

def move_mouse_left():
    move_mouse(-20,0)

def move_mouse_right():
    move_mouse(20,0)

def move_mouse_up():
    move_mouse(0,-20)

def move_mouse_down():
    move_mouse(0,20)






