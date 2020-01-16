from PIL import Image
# Imports image library stuff
import urllib, cStringIO
# Imports libs to read image from internet
import random
# Import sys so we can access argv for command line args
import sys

"""
Class: Negative

Negates an image as an example for the beginnings of a bigger image editing class. Example
of command line params. Real world would use a library to parse arguments. Better then this
example would be to have a command parser class that we could use instead of our huge init
method.
"""
class Negative(object):
    
    def __init__(self,argv):
        
        ## Parse argv that was passed in to our class
        parts = {}

        for i in range(1,len(argv),2):
            parts[sys.argv[i]] = sys.argv[i+1]
        
        if '-f' in parts.keys():
            self.input_file = parts['-f']
            self.save_file = self.input_file 
            self.img = Image.open(self.input_file)

        if '-u' in parts.keys():
            self.input_url = parts['-u']
            p = self.input_url.split('/')
            self.save_file = p[len(p)-1]
            self.img =  Image.open(cStringIO.StringIO(urllib.urlopen(self.input_url).read()))

        if '-s' in parts.keys():
            self.save_file = parts['-s']
            self.save = True
        else:
            self.save = False

        if '-show' in parts.keys():
            self.show = parts['-show']
            if self.show == "1" or self.show == "True":
                self.show = True
            else:
                self.show = False

        ## Parsing Done!

        # Get width and height of image so we can loop through it
        self.width = self.img.size[0]
        self.height = self.img.size[1]

        # Call local negate method
        self.negate()

        # Perform actions based on command line params set above
        if self.save:
            self.img.save(self.save_file)

        if self.show:
            self.img.show()


    # Negates an image by inverting each pixels color channel
    # If we use  this class as I have it setup now, the input param and return are not used. 
    #
    # Otherwise, we can allow an image to be passed in wich would be negated and returned. 
    # This is how the method would normally be used.

    def negate(self,img=None):
        if not img == None:
            self.img = img

         # Loop through the image and read every pixel
        for x in range(self.width):
            for y in range(self.height):

                # Get rgb value from pixel
                rgb = self.img.getpixel((x,y))

                # Negate each color channel by subtracting it from 255
                rgb2 = (255-rgb[0],255-rgb[1],255-rgb[2])

                # Write the pixel back to the image. This actually
                # is the editing part. Without calling 'putpixel'
                # the image would NOT be changed.
                self.img.putpixel((x,y),rgb2)

        return self.img

    # NOT USED but I left it here 
    def random_color(self):
        return (random.randint(255),random.randint(255),random.randint(255))


# Prints the usage as expected if we don't get enough params
# Remember, we are NOT error checking and in the real world, you MUST!
def print_usage():
    print("Error: \n   Url or filename needed")
    print("Usage: \n   python %s -u url [-o outputfile]\n   python %s -f filename [-s savefile, -show 1]" % (sys.argv[0],sys.argv[0]))
    print("Example: \n   python %s -u https://s-media-cache-ak0.pinimg.com/originals/05/b3/83/05b3831a2cefe769af2e9e5c877e6cc8.jpg -o negative.jpg -show 1" % (sys.argv[0]))
    print("   (this would open the url, process it, save it locally in 'negative.jpg' and also open the result")

# Ummmm run me if this file called directly.
if __name__=='__main__':
    if len(sys.argv) < 3:
        print_usage()
        sys.exit(0)
    else:
       neg = Negative(sys.argv)
