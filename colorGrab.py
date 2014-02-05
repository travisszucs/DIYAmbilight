import os
import serial
import struct
import time
from PIL import Image
from scipy.cluster import vq
import numpy

## intialize connection with Arduino Uno via serial
ser = serial.Serial('/dev/cu.usbmodem1421', 9600, timeout=0)

## Create a screen capture and returns a pixel access object after
## resizing image to heightxwidth
def getPixels():
    height,width = 169,300
    os.system('screencapture -x temp.png') # load a screen capture into PIL (150x150 size)
    im = Image.open('temp.png')
    im.thumbnail((height,width))
    pixels = list(im.getdata())  # convert PixelAccess Object to a list of tuples
    return numpy.asarray(pixels, dtype=numpy.int32) # convert list of tuples to an Array
                                                    #for k-means function and return

def kMeans(pixels):
    numberOfClusters = 3
    center,dist = vq.kmeans(pixels,numberOfClusters)
    return center[0]

def grabColor():
    # using scipy's implementation of kmeans, find an average color between
    # pixels displayed on screen and format it into an array mapped as
    # ['Red Value', 'Green Value', 'Blue Value']
    pixels = getPixels()
    colorData = kMeans(pixels)
    print colorData

    # encode color values and pin #s to be sent via serial
    # arduino is expecting to be sent something like '3255'
    # where 3 is pin # and 255 is color value, zeros must be
    # padded onto the color value to ensure it has length of 3

    ser.write(''.join(('2',str(colorData[0]).zfill(3))))
    ser.write(''.join(('1',str(colorData[1]).zfill(3))))
    ser.write(''.join(('0',str(colorData[2]).zfill(3))))
    time.sleep(2) # sleep to let arduino finish processing and help prevent crazy color changes


# loop to run program
while True:
    grabColor()
