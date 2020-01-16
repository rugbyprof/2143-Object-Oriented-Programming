import random

def alphanumeric(num):
    num = list(num)
    if len(num) != 9:
        return None
    
    alpha = ['','ABC', 'DEF', 'GHI', 'JKL', 'MNO', 'PQRS', 'TUV', 'WXYZ']
    
    phone = ""
    
    for i in num:
        for chunk in alpha:
            if i in chunk:
                print(alpha.index(chunk))
                phone += str(alpha.index(chunk))
    
    return phone
              
  
def alphanumeric(num):
    num = list(num)
    if len(num) != 9:
        return None
    
    alpha = ['','ABC', 'DEF', 'GHI', 'JKL', 'MNO', 'PQRS', 'TUV', 'WXYZ']
    
    phone = []
    
    for i in num:
        for chunk in alpha:
            if i in chunk:
                print(alpha.index(chunk))
                phone.append(alpha.index(chunk))
    
    return ''.join([str(i) for i in phone])
    
def guessAnswer(low,high,answer):
    guesses = 0
    for i in range(low,high+1):
        if answer == i:
            return guesses + 1
        guesses += 1

def guessAnswer2(low,high,answer):
    
    guesses = 1
    found = False
    
    while not found:

        start = (low + high) // 2
        
        print(start,low,high)
        
        if answer == start:
            return guesses
        elif answer > start:
            low = start + 1
        else:
            high = start - 1 
        
        guesses += 1
            
    return None
  
def guessAnswer3(low,high,answer):
    
    start = (low + high) // 2
    
    print(start,low,high)
    if answer == start:
        return 1
    elif answer > start:
        return 1 + guessAnswer2(start+1,high,answer)
    else:
        return 1 + guessAnswer2(low,start-1,answer)
        
def uniqueDictionary(n,largest=1000000):
    uniqueDict = {}
    count = n
    
    while count > 0:
        uniqueDict[random.randint(0,largest)] = None
        count -= 1
    
    vals =  uniqueDict.keys()
    vals.sort()
    return vals
    

class wordDictonary(object):
    def __init__(self):
        self.words = {}
        
    def loadWords(self,filename):
        f = open(filename, 'r')
        for line in f:
            word,definition = line.split(':')
            definition = definition.strip("\n")
            
            if not word in self.words:
                self.words[word] = []
            
            self.words[word].append(definition)

    def updateDictionary(self,word,definition):
        self.words[word].append(definition)
    
    def findWord(self,word):
        return self.words[word]
    
    def removeWord(self,word):
        del self.words[word]
        
    def printDictionary(self):
        for k in self.words:
            print(k,self.words[k])
            
  
if __name__=='__main__':
    #print(alphanumeric('ABCFFGZMX'))

    # L = ['a','b','c','d','e']
    # print(L.index('c'))
    
    print(guessAnswer(1,1048576,500000))
    print(guessAnswer2(1,1048576,500000)) 
    print(guessAnswer3(1,1048576,499))     
    #d = wordDictonary()
    #d.printDictionary()
    #print uniqueDictionary(1000)
