
import os
import time
import urllib3, uuid
from PIL import Image
import sys


url = 'http://thecatapi.com/api/images/get'

def getCat(directory=None, filename=None, format='png'):
    basename = '%s.%s' % (filename if filename else str(uuid.uuid4()), format)
    savefile =  os.path.sep.join([directory.rstrip(os.path.sep), basename]) if directory else basename
    downloadlink = url + '?type=%s' % format
    http = urllib3.PoolManager()
    r = http.request('GET', downloadlink)
    fp = open(savefile, 'wb')
    fp.write(r.data)
    fp.close()
    return savefile

class RandomCat(object):

    def __init__(self):

        self.name = ''          # name of image
        self.path = '.'         # path on local file system
        self.format = 'png'
        self.width = 0          # width of image
<<<<<<< HEAD
        self.height = 0         # height of image        
=======
        self.height = 0         # height of image
>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
        self.img = None         # Pillow var to hold image


    """
<<<<<<< HEAD
    @Description: 
    - Uses random cat to go get an amazing image from the internet
    - Names the image
    - Saves the image to some location
    @Returns: 
=======
    @Description:
    - Uses random cat to go get an amazing image from the internet
    - Names the image
    - Saves the image to some location
    @Returns:
>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
    """
    def getImage(self):
        self.name = self.getTimeStamp()
        getCat(directory=self.path, filename=self.name, format=self.format)
        self.img = Image.open(self.name+'.'+self.format)
<<<<<<< HEAD
        
        self.width, self.heigth = self.img.size
        
=======

        self.width, self.heigth = self.img.size

>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
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
<<<<<<< HEAD
        return seconds 


""" 
The ascii character set we use to replace pixels. 
=======
        return seconds


"""
The ascii character set we use to replace pixels.
>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
The grayscale pixel values are 0-255.
0 - 25 = '#' (darkest character)
250-255 = '.' (lightest character)
"""


class AsciiImage(RandomCat):

    def __init__(self,new_width="not_set"):
        super(AsciiImage, self).__init__()

        self.newWidth = new_width
        self.newHeight = 0
<<<<<<< HEAD
            
        self.asciiChars = [ '#', 'A', '@', '%', 'S', '+', '<', '*', ':', ',', '.']
        self.imageAsAscii = []
        self.matrix = None
        
        
=======

        self.asciiChars = [ '#', 'A', '@', '%', 'S', '+', '<', '*', ':', ',', '.']
        self.imageAsAscii = []
        self.matrix = None


>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
    """
    Your comments here
    """
    def convertToAscii(self):
<<<<<<< HEAD
    
        if self.newWidth == "not_set":
            self.newWidth = self.width
            
        self.newHeight = int((self.heigth * self.newWidth) / self.width)
            
        if self.newWidth == None:
            self.newWidth = self.width
            self.newHeight = self.height
            
        self.newImage = self.img.resize((self.newWidth, self.newHeight))
        self.newImage = self.newImage.convert("L") # convert to grayscale
        all_pixels = list(self.newImage.getdata())
        #print(all_pixels)
        self.matrix = listToMatrix(all_pixels,self.newWidth)
        
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[i])):
                self.matrix[i][j] = self.asciiChars[self.matrix[i][j] // 25] # 0 - 10
                


    
    """
    Print the image to the screen
    """
    # def printImage(self):
    #     self.imageAsAscii = ''.join(ch for ch in self.imageAsAscii)
    #     for c in range(0, len(self.imageAsAscii), self.newWidth):
    #         print (self.imageAsAscii[c:c+self.newWidth])
            
    def printImage(self):
=======

        if self.newWidth == "not_set":
            self.newWidth = self.width

        self.newHeight = int((self.heigth * self.newWidth) / self.width)

        if self.newWidth == None:
            self.newWidth = self.width
            self.newHeight = self.height

        self.newImage = self.img.resize((self.newWidth, self.newHeight))
        self.newImage = self.newImage.convert("L") # convert to grayscale
        all_pixels = list(self.newImage.getdata())

        # Put all pixels into an NxM matrix
        self.matrix = listToMatrix(all_pixels,self.newWidth)

        # Loop through matrix to convert to ascii
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[i])):
                self.matrix[i][j] = self.asciiChars[self.matrix[i][j] // 25]

    """
    Print the image to the screen
    """
    def printImage(self):
        # Using matrix to print out image
>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
        for row in self.matrix:
            print(''.join(row))

"""
Convert to 2D list of lists to help with manipulating the ascii image.
Example:
<<<<<<< HEAD
    
    L = [0,1,2,3,4,5,6,7,8]
    
    L = to_matrix(L,3)
    
    L becomes:
    
=======

    L = [0,1,2,3,4,5,6,7,8]

    L = to_matrix(L,3)

    L becomes:

>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
    [[0,1,2],
    [3,4,5],
    [6,7,8]]
"""
<<<<<<< HEAD

def listToMatrix(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]




if __name__=='__main__':
    awesomeCat = AsciiImage(100)
    awesomeCat.getImage()
    
    awesomeCat.convertToAscii()
    awesomeCat.printImage()
    
=======
def listToMatrix(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

if __name__=='__main__':
    awesomeCat = AsciiImage(150)
    awesomeCat.getImage()

    awesomeCat.convertToAscii()
    awesomeCat.printImage()
>>>>>>> a1e9d5c596183745a7d3f9d03b38ff19906c2900
