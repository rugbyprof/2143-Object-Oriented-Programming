import cat
import os
import time
from PIL import Image
import sys

class RandomCat(object):

    def __init__(self):

        self.name = ''          # name of image
        self.path = '.'         # path on local file system
        self.format = 'png'
        self.width = 0          # width of image
        self.height = 0         # height of image        
        self.img = None         # Pillow var to hold image


    """
    @Description: 
    - Uses random cat to go get an amazing image from the internet
    - Names the image
    - Saves the image to some location
    @Returns: 
    """
    def getImage(self):
        self.name = self.getTimeStamp()
        cat.getCat(directory=self.path, filename=self.name, format=self.format)
        self.img = Image.open(self.name+'.'+self.format)
        
        self.width, self.heigth = self.img.size
        
    """
    Saves the image to the local file system given:
    - Names
    - Path
    """
    def saveImage(self):
        pass

    """

    """
    def nameImage(self):
        pass

    """
    Gets time stamp from local system
    """
    def getTimeStamp(self):
        seconds,milli = str(time.time()).split('.')
        return seconds 


""" 
The ascii character set we use to replace pixels. 
The grayscale pixel values are 0-255.
0 - 25 = '#' (darkest character)
250-255 = '.' (lightest character)
"""


class AsciiImage(RandomCat):

    def __init__(self,new_width="not_set"):
        super(AsciiImage, self).__init__()

        self.newWidth = new_width
        self.newHeight = 0
            
        self.asciiChars = [ '#', 'A', '@', '%', 'S', '+', '<', '*', ':', ',', '.']
        self.imageAsAscii = []
        self.matrix = None
        
        
    """
    Your comments here
    """
    def convertToAscii(self):
    
        if self.newWidth == "not_set":
            self.newWidth = self.width
            
        self.newHeight = int((self.heigth * self.newWidth) / self.width)
            
        if self.newWidth == None:
            self.newWidth = self.width
            self.newHeight = self.height
            
        self.newImage = self.img.resize((self.newWidth, self.newHeight))
        self.newImage = self.newImage.convert("L") # convert to grayscale
        all_pixels = list(self.newImage.getdata())
        self.matrix = listToMatrix(all_pixels,self.newWidth)
        

        for pixel_value in all_pixels:
            index = pixel_value / 25 # 0 - 10
            self.imageAsAscii.append(self.asciiChars[index])

    """
    Print the image to the screen
    """
    def printImage(self):
        self.imageAsAscii = ''.join(ch for ch in self.imageAsAscii)
        for c in range(0, len(self.imageAsAscii), self.newWidth):
            print (self.imageAsAscii[c:c+self.newWidth])

"""
Convert to 2D list of lists to help with manipulating the ascii image.
Example:
    
    L = [0,1,2,3,4,5,6,7,8]
    
    L = to_matrix(L,3)
    
    L becomes:
    
    [[0,1,2],
    [3,4,5],
    [6,7,8]]
"""
def listToMatrix(l, n):
    return [l[i:i+n] for i in xrange(0, len(l), n)]

if __name__=='__main__':
    awesomeCat = AsciiImage(150)
    awesomeCat.getImage()
    
    awesomeCat.convertToAscii()
    awesomeCat.printImage()
    
