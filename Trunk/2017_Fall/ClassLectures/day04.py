import urllib2
import re
import pickle
import pprint, pickle
import os.path

req = urllib2.Request('https://www.gutenberg.org/files/2600/2600-0.txt')
response = urllib2.urlopen(req)
raw  = response.read()

raw = raw.split()

hist = {}

for word in raw:
    word = re.sub(r'[^\x00-\x7F]+','', word)
    word = re.sub("[.:,;?!(){}]",'',word)
    word = re.sub("[-]",' ',word)
    if not word.lower() in hist:
        hist[word.lower()] = 0
    hist[word.lower()] += 1

print(hist)

output = open('data.pkl', 'wb')

pickle.dump(hist, output)

pkl_file = open('data.pkl', 'rb')

data1 = pickle.load(pkl_file)
pprint.pprint(data1)

pkl_file.close()

os.path.isfile(fname) 
