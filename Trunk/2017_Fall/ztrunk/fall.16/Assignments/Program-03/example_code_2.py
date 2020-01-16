from PIL import Image
# Imports image library stuff
import urllib, cStringIO
# Imports libs to read image from internet
import random

def random_color():
    return (random.randint(255),random.randint(255),random.randint(255))

# Image resource from internet
url = 'http://fyf.tac-cdn.net/images/products/large/FYF-870.jpg'

# Turn image url into something that can be read / opened by PIL
file = cStringIO.StringIO(urllib.urlopen(url).read())

# Actually open the image

img = Image.open(file)
#img = Image.open('fruit.jpg')

# Get width and height of image so we can loop through it
width = img.size[0]
height = img.size[1]

# Loop through the image and read every pixel
for x in range(width):
    for y in range(height):
        # Print rgb value to the screen
        print(img.getpixel((x,y)))

        # Get rgb value from pixel
        rgb = img.getpixel((x,y))

        # Divide each color channel in half. Why? Because
        # this is a basic example of how every function for
        # you program will manipulate the image

        rgb2 = (255-rgb[0],255-rgb[1],255-rgb[2])

        # Write the pixel back to the image. This actually
        # is the editing part
        img.putpixel((x,y),rgb2)
img.save('fruit.jpg')
img.show()
