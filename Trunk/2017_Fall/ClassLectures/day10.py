class Node(object):
  def __init__(self,val):
    self.data = val
    self.left_child = None
    self.right_child = None
    self.parent = None
    
  def setVal(self,val):
    self.data = val
    
  def setLeftChild(self,node):
    self.left_child = node
    self.left_child.parent = self
  
  def setRightChild(self,node):
    self.right_child = node
    self.right_child.parent = self 

  def __str__(self):
    return "%d" % (self.data)
    
class BST(object):
  def __init__(self):
    self.root = None
    
  def __traverse(self,root):
    if root == None:
      return
    elif
  
  def print(self)
    self.__traverse(self.root)
    
  def insert(self,data):
    # if no root exists
    if self.root == None:
      self.root = Node(data)
      # otherwise find location to insert
    else:
      parent = self.root
      temp = self.root
      direction = ""
    
      while not temp == None:
        parent = temp
        if temp.data > data:
          direction = "left"
          temp = temp.left_child
        else:
          direction = "right"
          temp = temp.right_child
      
      if direction == "left":
        parent.left_child = Node(data)
        parent.left_child.parent = parent
      else:
        parent.right_child = Node(data)
        parent.right_child.parent = parent
      
        
    

tree = BST()
tree.insert(34)




