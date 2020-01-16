import os
import subprocess

def resizer(size,input,output):
    size = str(size)
    params = ['convert', '-resize', size+'x', './500x/'+input, './'+size+'x/'+output]
    subprocess.check_call(params)

sizes = ['250','100','75','50']

for dirname, dirnames, filenames in os.walk('./500x'):
    # print path to all subdirectories first.
    # for subdirname in dirnames:
    #     print(os.path.join(dirname, subdirname))

    # print path to all filenames.
    for filename in filenames:
        outname = filename[:-3]+'gif'
        for size in sizes:
            resizer(size,filename,outname)
        
        print(os.path.join(dirname, filename))
        # print(os.path.join(dirname, outname))



