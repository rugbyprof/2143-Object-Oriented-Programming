import random
import time

class BinarySearchTree(object):
    def __init__(self,size=16):
        self.tree = [-1 for x in range(size)]
        self.size = size
        self.root = 1
        self.items = 0
        self.values = []
    
    def loadList(self,numbers):
        self.optimize(numbers)
        for i in self.values:
            self.insert(i)
    
    def insert(self,val):
        
        # If list (tree) is empty, put value at root
        if self.tree[self.root] == -1:
            self.tree[self.root] = val
        # loop until you find the location to insert
        # even if you have to extend this list
        else:
            i = self.root
            loop = True
            while loop:
                if val > self.tree[i]:
                    i = self.rightChild(i)
                else:
                    i = self.leftChild(i)
                
                if i >= self.size:
                    self.extend()
                
                if self.tree[i] == -1:
                    self.tree[i] = val
                    self.items += 1
                    loop = False
                        
    def optimize(self,List):
        if len(List) == 0:
            return
        else:
            self.values.append(List[len(List)//2])
            self.optimize(List[:len(List)//2])
            self.optimize(List[len(List)//2+1:])
                    
    def extend(self):
        temp = [-1 for x in range(self.size)]
        self.tree.extend(temp)
        self.size *= 2
        print(self.items)
        
    def find(self,key):
    
        self.comparisons = 1

        if key == self.tree[self.root]:
            return True
        else:
            i = self.root
            while True:
                if key < self.tree[i]:
                    i = self.leftChild(i)
                else:
                    i = self.rightChild(i)
                    
                if i >= self.size:
                    return False
                
                if self.tree[i] == -1:
                    return False   
                    
                if self.tree[i] == key:
                    return True
                    
                self.comparisons += 1
                
                
    def leftChild(self,i):
        return 2 * i
        
    def rightChild(self,i):
        return 2 * i + 1

random.seed(time.time())

num = input("How many: ")

num = int(num)

# Create a list to hold unique integers
unique = []

# loop 1000 times
for x in range(num):

    # get a random number
    r = random.randint(0,999999)

    # if it's not already in the list, enter it.
    if r not in unique:
        unique.append(r)

# Sort the list
unique.sort()

bs = BinarySearchTree()
unique = [i for i in range(1,num)]


bs.loadList(unique)
print(bs.tree)
