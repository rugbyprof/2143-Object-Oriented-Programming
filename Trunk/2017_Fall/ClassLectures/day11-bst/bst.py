#!/usr/bin/python
# -*- coding: utf-8 -*-
import random
import graphviz as gv
import sys

class Node(object):

    def __init__(self, val):
        self.data = val
        self.left = None
        self.right = None
        self.parent = None
        self.node_id = None


    def __str__(self):
        try:
            left = str(self.left.data)
        except:
            left = '-1'

        try:
            right = str(self.right.data)
        except:
            right = '-1'
        return '[D:%s , L:%s , R:%s]' % (str(self.data), left, right)


class BST(object):
    """Represents a Binary Search Tree.

    - Attributes:
        - root (Node): A reference to the root node of the tree. 

    - Methods:
        - delete (None)  : Deletes a node from the tree. 
        - find (Node)    : Finds a node in the tree. 
        - insert (Mixed) : Inserts a value into the tree. 
        """
    def __init__(self):
        """Bst constructor

        - Public

        - Args:
            - None
        - Returns:
            - None
        """
        self.root = None

    def delete(self, key):
        """Calls private delete method with root of tree.
        """
        self.__delete(self.root, key)

    def find(self, key):
        """Calls private find method with root of the tree.
        """
        return self.__find(self.root, key)

    def insert(self, data):
        """Insert data into tree 

        - Public

        - Args:
            - key (int)  : Key value to insert into tree 
        - Returns:
            - None
        """
        # if no root exists
        if self.root == None:
            self.root = Node(data)
        else:
            # otherwise find location to insert
            parent = self.root
            temp = self.root
            direction = ''

            # Loop until we find a "null" child pointer then insert
            while not temp == None:
                parent = temp
                if temp.data > data:
                    direction = 'left'
                    temp = temp.left
                else:
                    direction = 'right'
                    temp = temp.right

            # Update parent pointer.
            if direction == 'left':
                parent.left = Node(data)
                parent.left.parent = parent

            else:
                parent.right = Node(data)
                parent.right.parent = parent


    def print_tree(self):
        """Call private print method with root of tree.  
        """
        self.__print_tree(self.root)

    def __delete(self, root, key):
        """Delete node from tree. 

        - Private

        - Args:
            - root (Node): Reference to current root 
            - key (int)  : Key value to find and delete 
        - Returns:
            - None
        """
        # Find the correct node to be deleted
        node = self.__find(root, key)

        # If the node IS A LEAF, we simply remove it 
        if self.__isleaf(node):
            if node.parent.left == node:
                node.parent.left = None
            else:
                node.parent.right = None
        elif node.left and node.right:
            # Node to be deleted has TWO CHILDREN

            # find the parent and predesessor of node to be deleted
            parent,pred = self.__predecessor(node)

            # check if predeccesor is a leaf and if so 
            # swap values and delete the leaf.
            if not pred.left and not pred.right:
                node.data = pred.data
                if parent.left == pred:
                    parent.left = None
                else:
                    parent.right = None
                return

        elif node.left:
            # Node to be deleted has SINGLE LEFT child 
            # so we bypass parent pointer to our left
            # child 
            if node.parent.left == node:
                node.parent.left = node.left
            else:
                node.parent.right = node.left
        else:
            # Node to be deleted has SINGLE RIGHT child 
            # so we bypass parent pointer to our left
            # child 
            if node.parent.left == node:
                node.parent.left = node.right
            else:
                node.parent.right = node.right

    def __find(self, root, key):
        """Find node in a tree and return reference to it.

        - Private

        - Args:
            - root (Node): Reference to current root 
            - key (int)  : Key value to find and delete 
        - Returns:
            - Node 
        """
        while True:
            if root == None:
                return None
            elif root.data == key:
                return root
            elif root.data > key:
                root = root.left
            else:
                root = root.right

    def __isleaf(self,node):
        """Boolean check to see if node is a leaf.

        - Private

        - Args:
            - node (Node): Reference to a node in tree
        - Returns:
            - Node 
        """
        return node.left is None and node.right is None

    def __predecessor(self, root):
        """Finds the predecessor of a node in the tree.

        - Private

        - Args:
            - node (Node): Reference to a node in tree
        - Returns:
            - Node 
        """
        if not root.left:
            return [root,None]

        parent = root
        root = root.left
        while root.right is not None:
            parent = root
            root = root.right
        return [parent,root]

    def __successor(self, root):
        """Finds the successor of a node in the tree.

        - Private

        - Args:
            - node (Node): Reference to a node in tree
        - Returns:
            - Node 
        """
        if not root.right:
            return [root,None]

        parent = root
        root = root.right

        while root.left is not None:
            parent = root
            root = root.left
        return [parent,root]


    def __print_tree(self, root,order="inorder"):
        """Prints out the nodes in a specified order. 

        - Private

        - Args:
            - node (Node): Reference to a node in tree
        - Returns:
            - Node 
        """
        if root == None:
            return
        else:
            if order=='preorder':
                print(root.data)
            self.__print_tree(root.left)
            if order=='inorder':
                print(root.data)
            self.__print_tree(root.right)
            if order=='postorder':
                print(root.data)

def bin_order(L):
    newL = []
    if len(L) == 0:
        return
    else:
        bin_order(leftside)
        bin_order(rightside)


if __name__=='__main__':
    #random.seed(97697)

    tree = BST()
    L = [int(10000 * random.random()) for i in xrange(1000)]

    tree.insert(5000)
    for i in L:
    tree.insert(i)
                