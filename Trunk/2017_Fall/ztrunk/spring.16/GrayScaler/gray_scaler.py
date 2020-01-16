from PIL import Image
import numpy as np


# class Color(object):
#     def __init__(self,**kwargs):
#         if 'R' in kwargs:
#             self.R = kwargs['R']
            
        
def Lightness(color=None):
    v =  int((max(color[0], color[1], color[2]) + min(color[0], color[1], color[2])) / 2)
    return (v,v,v)

def Average(c=None):
    v = int((c[0] + c[1] + c[2]) / 3)
    return (v,v,v)

def Luminosity(color=None):
    v = int(0.21 * color[0] + 0.72 * color[1] + 0.07 * color[2])
    return (v,v,v)

def Custom(w,color=None):
    v = int(w[0] * color[0] + w[1] * color[1] + w[2] * color[2])
    return (v,v,v)

img = Image.open("green_leaves.jpg")
#p = np.array(im)
pixels = img.load()

width,height = img.size

for i in range(width):    # for every pixel:
    for j in range(height):
        #pixels[i,j] = (i, j, 100) # set the colour accordingly
        #print(pixels[i,j])
        pixels[i,j] = Luminosity(pixels[i,j])


img.show()

# im = Image.open('image.gif')
# rgb_im = im.convert('RGB')
# r, g, b = rgb_im.getpixel((1, 1))