#import keyboard
import mouse
import timeit
#import loadModel
#import pyautogui as key
#from pynput.keyboard import Key, Controller
#import pydirectinput as key
from pynput.keyboard import Key, Controller
keyboard = Controller()
def press_w():
    #keyboard.press_and_release('w')
    keyboard.press('w')


def press_a():
    #keyboard.press_and_release('a')
    keyboard.press('a')


def press_s():
    # keyboard.press_and_release('s')
    keyboard.press('s')


def press_d():
    # keyboard.press_and_release('d')
    keyboard.press('d')


def press_uppercut():
    keyboard.press_and_release('w, a, s, d')


def up_arrow():
    # keyboard.press_and_release('up')
    key.press('up', _pause=False)


def left_arrow():
    # keyboard.press_and_release('left')
    key.press('left', _pause=False)


def right_arrow():
    # keyboard.press_and_release('right')
    key.press('right', _pause=False)


def down_arrow():
    # keyboard.press_and_release('down')
    key.press('down', _pause=False)


def left_click():
    mouse.click('left')


def right_click():
    mouse.click('right')


def move_mouse(x, y):
    mouse.move(x, y, absolute=False, duration=0)


def move_mouse_left():
    move_mouse(-20, 0)


def move_mouse_right():
    move_mouse(20, 0)


def move_mouse_up():
    move_mouse(0, -20)


def move_mouse_down():
    move_mouse(0, 20)


'''import ctypes
import time

SendInput = ctypes.windll.user32.SendInput


W = 0x11
A = 0x1E
S = 0x1F
D = 0x20

UP = 0xC8
DOWN = 0xD0
RIGHT = 0xCD
LEFT = 0xCB

# C struct redefinitions 
PUL = ctypes.POINTER(ctypes.c_ulong)
class KeyBdInput(ctypes.Structure):
    _fields_ = [("wVk", ctypes.c_ushort),
                ("wScan", ctypes.c_ushort),
                ("dwFlags", ctypes.c_ulong),
                ("time", ctypes.c_ulong),
                ("dwExtraInfo", PUL)]

class HardwareInput(ctypes.Structure):
    _fields_ = [("uMsg", ctypes.c_ulong),
                ("wParamL", ctypes.c_short),
                ("wParamH", ctypes.c_ushort)]

class MouseInput(ctypes.Structure):
    _fields_ = [("dx", ctypes.c_long),
                ("dy", ctypes.c_long),
                ("mouseData", ctypes.c_ulong),
                ("dwFlags", ctypes.c_ulong),
                ("time",ctypes.c_ulong),
                ("dwExtraInfo", PUL)]

class Input_I(ctypes.Union):
    _fields_ = [("ki", KeyBdInput),
                 ("mi", MouseInput),
                 ("hi", HardwareInput)]

class Input(ctypes.Structure):
    _fields_ = [("type", ctypes.c_ulong),
                ("ii", Input_I)]

# Actuals Functions

def PressKey(hexKeyCode):
    extra = ctypes.c_ulong(0)
    ii_ = Input_I()
    ii_.ki = KeyBdInput( 0, hexKeyCode, 0x0008, 0, ctypes.pointer(extra) )
    x = Input( ctypes.c_ulong(1), ii_ )
    ctypes.windll.user32.SendInput(1, ctypes.pointer(x), ctypes.sizeof(x))

def ReleaseKey(hexKeyCode):
    extra = ctypes.c_ulong(0)
    ii_ = Input_I()
    ii_.ki = KeyBdInput( 0, hexKeyCode, 0x0008 | 0x0002, 0, ctypes.pointer(extra) )
    x = Input( ctypes.c_ulong(1), ii_ )
    ctypes.windll.user32.SendInput(1, ctypes.pointer(x), ctypes.sizeof(x))
'''