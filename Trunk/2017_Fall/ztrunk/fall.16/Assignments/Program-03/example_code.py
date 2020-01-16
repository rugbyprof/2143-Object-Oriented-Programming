from PIL import Image

# opens an image using PIL
img = Image.open(file_name)

# resizes an image to a new height and width
img = img.resize((new_width,new_height), Image.ANTIALIAS)

# one method to get all the pixel data from an image however
# you now have one long list of rgb values and no idea of 
# width and height
pixels = list(img.getdata())

size = img.size 
# size is now a tuple with width and height (e.g. (345,200)) where 345=width and 200=height
# you can also do the following:
width,height = img.size
# or
width = img.size[0]
height = img.size[1]

# open an image from a url
import urllib, cStringIO
file = cStringIO.StringIO(urllib.urlopen(URL).read())
img = Image.open(file)
