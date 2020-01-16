import urllib2
import time
import time

def loadWords():
    req = urllib2.Request(url='https://raw.githubusercontent.com/rugbyprof/2143-ObjectOrientedProgramming/master/words')

    f = urllib2.urlopen(req)

    words = []

    for word in f:
        words.append(word.strip())
    return words

def binarySearch(words,key):

    first = 0
    last = len(words)-1
    Found = False
    
    
    while not Found:
        middle = (first + last) // 2
        if words[middle] == key:
            Found = True
            return middle
        else:
            if key > words[middle]:
                first = middle + 1
            else:
                last = middle - 1
    
    return None
    
def Search(words,key):
    Found = False
    for i in range(len(words)):
        if words[i] == key:
            Found = True
            return i
    return None



t0 = time.time()
words = loadWords()

words = ['zymoplastic', 'zymoscope', 'zymosimeter', 'zymosis', 'zymosterol', 'zymosthenic', 'zymotechnic', 'zymotechnical', 'zymotechnics', 'zymotechny', 'zymotic', 'zymotically', 'zymotize', 'zymotoxic', 'zymurgy', 'Zyrenian', 'Zyrian', 'Zyryan', 'zythem', 'Zythia', 'zythum', 'Zyzomys', 'Zyzzogeton']

t1 = time.time()
print("Words loaded ... ")
t2=time.time()
#print(binarySearch(words,'Zyzzogeton'))
t3=time.time()
print(Search(words,'Zyzzogeton'))
t4=time.time()

print(t3-t2)
print(t4-t3)


