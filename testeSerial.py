import sys
from pynput import keyboard
import numpy as np
from time import sleep

from pySerialTransfer import pySerialTransfer as txfer
from PIL import Image

COLS = 14
ROWS = 10


link = None





def epahya2(data):
    print("Sending", data, "... size:", len(data))
    size = link.tx_obj(data, 0)
    link.send(size)

def on_release2(key):
    if (key == keyboard.KeyCode.from_char('1')):
        epahya2("1")
    if (key == keyboard.KeyCode.from_char('2')):
        epahya2("2")
    if (key == keyboard.KeyCode.from_char('3')):
        epahya2("3")
    
#for laters
def imageSendingMachine():
    size = COLS, ROWS
    img = Image.open("rainbow.png")
    img_resized = im.resize(size, Image.ANTIALIAS)
    
def intToByte(num):
    return num.to_bytes(1, sys.byteorder)

def intToChar(num):
    b = intToByte(num)
    return bytes(b, 'ascii')

def mainTest1():
    global link

    
    try:
        keyboard_listener = keyboard.Listener(on_release=on_release2)
        keyboard_listener.start()
        link = txfer.SerialTransfer('/dev/ttyACM0')

        while True:
            print('hjxbasjxhg   scgvu')
            
            while not link.available():
                # print(link.available())
                if link.status < 0:
                    print('ERROR: {}'.format(link.status))
                
            print('Response received:')
            
            response = ''
            for index in range(link.bytesRead):
                response += str(link.rxBuff[index])
  
            epahya2(chr(0)+chr(127)+chr(0))
            print(response)
                   
        
    except KeyboardInterrupt:
        link.close()

def sendData(data):
    for attemps in range(5):
        for i in range(len(data)):
            link.txBuff[i] = data[i]
        print("Sending ", data)
        link.send(len(data))

def on_release(key):
    print("Wrote: ", key)    
    if (key == keyboard.KeyCode.from_char('1')):
        sendData('1\n')
        
    if (key == keyboard.KeyCode.from_char('2')):
        sendData('2\n')
    
    if (key == keyboard.KeyCode.from_char('3')):
        sendData('3\n')

def mainTest2():
    global link

    link = txfer.SerialTransfer('/dev/ttyACM0')
    keyboard_listener = keyboard.Listener(on_release=on_release)
    keyboard_listener.start()

    try:
        print("yyoyo")
        while True:
            pass

    except KeyboardInterrupt:
        link.close()

if __name__ == '__main__':
    mainTest1()