"""
http://effbot.org/imagingbook/image.htm
http://www.textfiles.com/art/
http://www.tutorialspoint.com/python/python_files_io.htm
"""

from PIL import Image
import os
import sys
from PIL import Image, ImageDraw, ImageFont


class ImageAscii(object):
    """
    This class privides some methods to convert images to ascii characters and also convert
    ascii to an image (of ascii characters). 
    """
    
    def __init__(self,args={}):
        """
        Set up all necessary values to get us going.
        """
        self.args = args
        self.__process_file_names__(self.args)
        self.shrink_value = args.get('shrink_value','.10')
        self.ascii_width = args.get('ascii_width',500)
        self.font_name = args.get('font_name','Courier_New.ttf')
        self.font_size = args.get('font_size',10)
        self.font_gap = args.get('font_gap',.75)


    def img_to_ascii(self,image=None):
        """ 
        The ascii character set we use to replace pixels. 
        The grayscale pixel values are 0-255.
        0 - 25 = '#' (darkest character)
        250-255 = '.' (lightest character)
        """
        ascii_chars = [ '#', 'A', '@', '%', 'S', '+', '<', '*', ':', ',', '.']

        if image == None and not self.input_file:
            self.__print_error__("Please specify an input image file")
        else:
            self.args['file_name'] = image
            self.__process_file_names__(self.args)
        
        img = Image.open(self.input_file)

        img = self.__resize__(img)

        img = img.convert("L") # convert to grayscale

        # gets a list of 0-255 values
        all_pixels = list(img.getdata())

        # list to hold the ascii characters
        image_as_ascii = []
        for pixel_value in all_pixels:
            index = pixel_value / 25 # 0 - 10
            image_as_ascii.append(ascii_chars[index])

        # write the ascii chars to an output file
        raw_ascii_out = open(self.raw_ascii_name,"w")
        self.raw_ascii = ''
        image_as_ascii = ''.join(ch for ch in image_as_ascii)

        # this loops through the list a chunk (line) at a time where each
        # chunk is the width of the image
        for chunk in range(0, len(image_as_ascii), self.ascii_width):
            # if chunk = 0 and self.ascii_width = 500
            # the first loop would make line = [0:499]
            # the next loop would make line = [500:999]
            # and so on ...
            line = image_as_ascii[chunk:chunk+self.ascii_width]+"\n"

            # write data to a file
            raw_ascii_out.write(line)

            # keep copy of data within the object
            self.raw_ascii += line

        return self.raw_ascii



    def ascii_to_image(self,ascii=None):
        """
        Converts ascii characters from a file, or a list into an image of characters

        Params:

            ascii [list, string, None]
        """

        if ascii == None and not self.raw_ascii:
            self.__print_error__("Please specify an ascii input source")
        else:
            # This assumes a list of lists [[],[],[],[]] where each line is a sublist.
            if type(ascii) == list:
                self.raw_ascii_list = ascii

            # This assumes ascii is a path with a name on it to read from
            elif type(ascii) == str:
                self.__process_file_names__({'file_name':ascii})
                with open(ascii) as f:
                    self.raw_ascii=f.read()
                self.raw_ascii_list = self.__raw_to_list__(self.raw_ascii)

            # This assumes the raw ascii left from the image_to_ascii method
            else:
                self.raw_ascii_list = self.__raw_to_list__(self.raw_ascii)
                
        # Gets width and height based on len(list) = height and len(list[0]) = width 
        # [['0','0','0'],['1','1','1'],['1','1','1'],['0','0','0']] (has a height of 4 and a width of 3
        size = (int(len(self.raw_ascii_list[0])*self.font_size*self.font_gap),int(len(self.raw_ascii_list)*self.font_size*self.font_gap))

        # make a blank image for the text, initialized to transparent text color
        txtImg = Image.new('RGBA', size, (255,255,255,0))

        # get a font
        fnt = ImageFont.truetype(self.font_name, self.font_size)

        # get a drawing context
        d = ImageDraw.Draw(txtImg)

        # Write each ascii character onto our image at some x,y .
        # We space each character out using font-size * font-gap.
        # So to make characters closer together we set font-gap < 0
        # and obviously font-gap > 0 will spread characters apart.
        x = 0
        y = self.font_size
        for line in self.raw_ascii_list:
            for c in line:
                d.text((x,y), c, font=fnt, fill=(0,0,0,0))
                x += self.font_size * self.font_gap
            y += self.font_size * self.font_gap
            x = 0

        # Display the image
        txtImg.show()

        # Save the image (must be a jpg image).
        txtImg.save(self.img_ascii_name)


    def __process_file_names__(self,args):
        """
        This method uses the args dictionary to set up all the necessary
        file names and paths to write output to. It's not as robust as it 
        could be. For example I would like to pass in just a path name for
        the image-ascii-name and raw-ascii-name and have it use the original
        file name to write to those directorys.
        """
        
        self.input_file = args.get('file_name','')
        self.path_parts = self.__file_parts__(self.input_file)

        self.img_ascii_name = args.get('img_ascii_name',None)
        path_parts = self.__file_parts__(self.img_ascii_name)

        if not path_parts['full_path'] == '':
            self.img_ascii_name = path_parts['full_path']
        else:
            self.img_ascii_name = self.path_parts['path']+"/"+self.path_parts['name']+"-img-ascii"+'.jpg'

        self.raw_ascii_name = args.get('raw_ascii_name',None)
        path_parts = self.__file_parts__(self.raw_ascii_name)

        if not path_parts['full_path'] == '':
            self.raw_ascii_name = path_parts['full_path']
        else:
            self.raw_ascii_name = self.path_parts['path']+"/"+self.path_parts['name']+"-raw-ascii"+'.jpg'


    def __str__(self):
        return "[path: %s] , [name: %s] , [ext: %s] , [img ascii out: %s] , [raw ascii name: %s]" % (self.path_parts['path'] ,self.path_parts['name'] ,self.path_parts['ext'] ,self.img_ascii_name,self.raw_ascii_name)


    def __resize__(self,img):
        """
        This resizes the img while maintining aspect ratio. Keep in 
        mind that not all images scale to ascii perfectly because of the
        large discrepancy between line height line width (characters are 
        closer together horizontally then vertically)
        """
        
        wpercent = float(self.ascii_width / float(img.size[0]))
        hsize = int((float(img.size[1])*float(wpercent)))
        img = img.resize((self.ascii_width ,hsize), Image.ANTIALIAS)

        return img


    def __raw_to_list__(self,raw):
        """
        This takes a long string of ascii characters including 
        new line characters, and returns a list of lists splitting
        on the new lines.
        """
        raw = raw.split("\n")
        for i in range(len(raw)):
            raw[i] = list(raw[i])
        return raw


    def __print_error__(self,error):
        """
        Weak error method ... :(
        """
        print(error)
        sys.exit(0)


    def __file_parts__(self,file):
        """
        This is a helper method to split up a path and send back
        all of it's pieces.
        """
        parts = {
            'path':'',
            'name':'',
            'ext':'',
            'file':'',
            'full_name':'',
            'full_path':''
            }
        if not file == "" and not file == None:
            parts['path'],parts['full_name'] = os.path.split(file)
            parts['name'],parts['ext'] = parts['full_name'].split('.')
            if not parts['path']:
                parts['path'] = './'
            parts['full_path'] = parts['path']+'/'+parts['name']+'.'+parts['ext']
        else:
            parts['path'] = ''
            parts['name'] = ''
            parts['ext'] = ''
            parts['file'] = ''
            parts['full_path'] = ''

        return parts



if __name__=="__main__":
    args = {}

    args['input_file'] = ""
    args['raw_ascii_name'] = "./text_ascii_images/hp.txt"
    args['img_ascii_name'] = "./img_ascii_images/hp.jpg"
    ia = ImageAscii(args) 
    ascii = ia.img_to_ascii("./original_images/hp.jpg")
    ia.ascii_to_image()
    print(ia)
