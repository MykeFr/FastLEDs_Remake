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
 

from pySerialTransfer import pySerialTransfer as txfer

if __name__ == '__main__':
    try:
        link = txfer.SerialTransfer('/dev/ttyACM0')

        while True:
            link.txBuff[0] = 'h'
            link.txBuff[1] = 'i'
            link.txBuff[2] = '\n'
            
            link.send(3)
            print('hjxbasjxhg   scgvu')
            
            while not link.available():
                # print(link.available())
                if link.status < 0:
                    print('ERROR: {}'.format(link.status))
                
            print('Response received:')
            
            response = ''
            for index in range(link.bytesRead):
                response += chr(link.rxBuff[index])
            
            print(response)
        
    except KeyboardInterrupt:
        link.close()