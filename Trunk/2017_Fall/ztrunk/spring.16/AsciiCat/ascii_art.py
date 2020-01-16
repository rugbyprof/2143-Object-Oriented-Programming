"""
http://effbot.org/imagingbook/image.htm
http://www.textfiles.com/art/
http://www.tutorialspoint.com/python/python_files_io.htm
"""

from PIL import Image
import os
import sys



""" 
The ascii character set we use to replace pixels. 
The grayscale pixel values are 0-255.
0 - 25 = '#' (darkest character)
250-255 = '.' (lightest character)
"""
ascii_chars = [ '#', 'A', '@', '%', 'S', '+', '<', '*', ':', ',', '.']


def image_to_ascii(image):
    image_as_ascii = []
    all_pixels = list(image.getdata())

    for pixel_value in all_pixels:
        index = pixel_value / 25 # 0 - 10
        image_as_ascii.append(ascii_chars[index])
    return image_as_ascii	

if __name__=="__main__":
    img = Image.open("1457040446.png")
    width, heigth = img.size
    new_width = 80 
    new_heigth = int((heigth * new_width) / width)
    new_image = img.resize((new_width, new_heigth))
    new_image = new_image.convert("L") # convert to grayscale
        
    # now that we have a grayscale image with some fixed width we have to convert every pixel
    # to the appropriate ascii character from "ascii_chars"
    img_as_ascii = image_to_ascii(new_image)
    # print img_as_ascii
    # sys.exit()
    img_as_ascii = ''.join(ch for ch in img_as_ascii)
    for c in range(0, len(img_as_ascii), new_width):
        print img_as_ascii[c:c+new_width]