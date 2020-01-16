import sys

class ImageEdit(object):
    def __init__(self):
        pass
    
    def flip(self,image,imageout=None):
        print("flipping",image,imageout)
        
    def posterize(self,image,imageout=None):
        print("postering")
        
    def solarize(self,image,imageout=None):
        print("sostering")
        
    def polaroid(self,image,imageout=None):
        print("poslering")
        
print(sys.argv)

flags = ['-i','-o','-x','-h']

commands = {}

for i in range(1,len(sys.argv),2):
    commands[sys.argv[i]] = sys.argv[i+1]

commands['-x'] = commands['-x'].split(',')
print(commands)
ie = ImageEdit()

if '-i' in commands.keys():
    input_file = commands['-i']
    
if '-o' in commands.keys():
    output_file = commands['-o']
else:
    output_file = commands['-i']

if commands['-x'][0] == 'flip':
    ie.flip(input_file,output_file) 
