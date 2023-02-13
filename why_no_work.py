import sys
from pynput import keyboard
import numpy as np
from time import sleep

from pySerialTransfer import pySerialTransfer as txfer
from PIL import Image

COLS = 14
ROWS = 10


colors = []
link = None

def epahya2(data):
    
    size_data = len(data) 
    size_shifted = int(size_data/3)
    remainder = bool(size_data%3)


    shifted_array = [0 for i in range(size_shifted+int(remainder))]

    for i in range(size_shifted):
        shifted_array[i] = data[i*3]
        for o in range(1, 3):
            # print(shifted_array, i*3+o)
            shifted_array[i] = int(shifted_array[i] << 8)
            shifted_array[i] += data[i*3+o]
        # print(shifted_array)
    
    if(size_data%3):
        shifted_array[size_shifted] = data[size_shifted*3]
        
        for i in range(1, size_data%3):
            shifted_array[size_shifted] = shifted_array[size_shifted] << 8
            shifted_array[size_shifted] += data[i+((size_shifted*3))]

    print(shifted_array)
    
    size = link.tx_obj(shifted_array, 0)
    
    print("Sending", data, "... size:", size)
    link.send(size)

   # awaitResponse()
    # print('Response received:')
    # response = link.rx_obj(obj_type=list, obj_byte_size=link.bytesRead, list_format='B')
    


    # print(response[0:size_data])

def on_release(key):
    global colors
    if (key == keyboard.KeyCode.from_char('1')):
        colors += [255]
        colors += [0]
        colors += [0]
        epahya2(colors)
    if (key == keyboard.KeyCode.from_char('2')):
        colors += [0]
        colors += [255]
        colors += [0]
        epahya2(colors)
    if (key == keyboard.KeyCode.from_char('3')):
        colors += [0]
        colors += [0]
        colors += [255]
        epahya2(colors)
    
def imageSendingMachine():
    size = COLS, ROWS
    img = Image.open("rainbow.png")
    img_resized = im.resize(size, Image.ANTIALIAS)

def awaitResponse():
    while not link.available():
        if link.status < 0:
            print('ERROR: {}'.format(link.status))

def mainTest1():
    global link

    
    try:
        # keyboard_listener = keyboard.Listener(on_release=on_release)
        # keyboard_listener.start()
        link = txfer.SerialTransfer('/dev/ttyACM0')
        awaitResponse()

        cool = [0]*60
        for i in range(0,60,2):
            cool[i] = 100
        epahya2(cool)
        while True:
            
            pass
            # for index in range(link.bytesRead):
                # response += str(link.rxBuff[index])
      
    except KeyboardInterrupt:
        link.close()
        # quit()

if __name__ == '__main__':
    mainTest1()