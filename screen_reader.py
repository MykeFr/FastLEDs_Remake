import serial
import gi
import sys
gi.require_version('Gdk', '3.0')
from gi.repository import Gdk, GdkPixbuf
from pynput import keyboard
from screeninfo import get_monitors
import numpy as np

SCREEN_WIDTH = get_monitors()[0].width
SCREEN_HEIGHT = get_monitors()[0].height
buffer_width = SCREEN_WIDTH
buffer_height = SCREEN_HEIGHT
 
ser = None

# simpler but slower way to get a single RGB value from the screen
def PixelColor(pos):
    w = Gdk.get_default_root_window()
    pb = Gdk.pixbuf_get_from_window(w, pos[0], pos[1], 1, 1)
    return tuple(pb.get_pixels())

# take a screenshot from the screen and save it to a 1D buffer
def ScreenColorBuffer():
    w = Gdk.get_default_root_window()
    pb = Gdk.pixbuf_get_from_window(w, 39, 854, buffer_width, buffer_height)
    return (pb.get_rowstride(), tuple(pb.get_pixels()))

# convert from screen coordinates to buffer index and return the RGB value
def GetColorFromBuffer(x, y, rowstride, buf):
    return (buf[x * 3 + y * 3 * buffer_width + y * (rowstride % 3)], \
            buf[x * 3 + y * 3 * buffer_width + y * (rowstride % 3) + 1], \
            buf[x * 3 + y * 3 * buffer_width + y * (rowstride % 3) + 2])

def on_release(key):
    print("Wrote: ", key)
    ser.write(bytearray(str(key).encode()))

def main(argv):
    global ser
    ser = serial.Serial('/dev/ttyACM0',9600)

    keyboard_listener = keyboard.Listener(on_release=on_release)
    keyboard_listener.start()
    while True:
        pass
    # rowstride, buf = ScreenColorBuffer()

COLS = 14
ROWS = 10
USELESS_PER_ROW = 5

def matrixToIndex(x, y):
    # if LED strip starts from right to left from the top. 0 or 1
    STARTS_FROM_R_TO_L = (y % 2 == 0)
  
    # either this row is from left to right, or right to left
    # right to left
    if(STARTS_FROM_R_TO_L):
        return (COLS - x - 1) + y * COLS + USELESS_PER_ROW * y
  
    # left to right
    if(not STARTS_FROM_R_TO_L):
        return x + y * COLS + USELESS_PER_ROW * y



if __name__ == "__main__":
    # for y in range(ROWS):
        # for x in range(COLS):
            # print(x, ", ", y, " index: ", matrixToIndex(x, y));
    main(sys.argv[1:])