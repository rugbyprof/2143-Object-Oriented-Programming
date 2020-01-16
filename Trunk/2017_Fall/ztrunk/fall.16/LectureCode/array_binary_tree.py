import urllib2
import time
import random

def loadWords():
    req = urllib2.Request(url='https://raw.githubusercontent.com/rugbyprof/2143-ObjectOrientedProgramming/master/words')

    f = urllib2.urlopen(req)

    words = []

    for word in f:
        words.append(word.strip())
    return words
    
 # left = i * 2
 # right = i * 2 + 1
class arrayBinaryTree(object):
    def __init__(self,initial_size=100):
        self.tree = [0 for x in range(initial_size)]
        self.size = len(self.tree)
        
    def insert(self,x):
        # empty tree
        if self.tree[1] == 0:
            self.tree[1] = x
        else:
            i = 1
            while not self.tree[i] == 0:
                if x > self.tree[i]:
                    i = self.right_child(i)
                else:
                    i = self.left_child(i)
            self.tree[i] = x     
    
    def delete(self,x):
        pass
        
    # in order traversal
    # post order traversal
    # pre order traversal
    def printme(self):
        print(self.tree)
         
    def left_child(self,i):
        return 2 * i
    
    def right_child(self,i):
        return 2 * i + 1
     
 
if __name__=='__main__':
    words = loadWords()
    
    myTree = arrayBinaryTree(100)
    for i in range(5):   
        myTree.insert(random.randint(1,25))
        myTree.printme()
