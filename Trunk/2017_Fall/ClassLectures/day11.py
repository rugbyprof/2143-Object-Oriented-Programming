#!/usr/bin/python
# -*- coding: utf-8 -*-
import random
import graphviz as gv

class Node(object):

    def __init__(self, val):
        self.data = val
        self.left_child = None
        self.right_child = None
        self.parent = None

    def setVal(self, val):
        self.data = val

    def setLeftChild(self, node):
        self.left_child = node
        self.left_child.parent = self

    def setRightChild(self, node):
        self.right_child = node
        self.right_child.parent = self

    def __str__(self):
        return '[D:%d , L:%s , R:%s]' % (self.data,self.left_child.data,self.right_child.data)


class BST(object):

    def __init__(self):
        self.root = None
        self.g1 = gv.Digraph(format='png')

    def print_tree(self):
        self.__print_tree(self.root)

    def find(self, key):
        return self.__find(self.root, key)

    def render(self):
        self.g1.render('g1.png')


    def insert(self, data):

        # if no root exists
        if self.root == None:
            self.root = Node(data)
            self.g1.node(str(data))
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
                    temp = temp.left_child
                else:
                    direction = 'right'
                    temp = temp.right_child

            # Update parent pointer.
            self.g1.node(str(data))
            if direction == 'left':
                parent.left_child = Node(data)
                parent.left_child.parent = parent
                self.g1.edge(str(parent.left_child.parent.data),str(parent.left_child.data))
            else:
                parent.right_child = Node(data)
                parent.right_child.parent = parent
                self.g1.edge(str(parent.right_child.parent.data),str(parent.right_child.data))

    def delete(self,key):
        self.__delete(self.root,key)

    def __delete(self,root,key):
        node = self.__find(root,key)
        print(self.__is_leaf(node))	
        print(node)

    def __is_leaf(self,node):
        return node.left_child is None and node.right_child is None

    def __find(self, root, key):
        while True:
            if root == None:
                return None
            elif root.data == key:
                return root
            elif root.data > key:
                root = root.left_child
            else:
                root = root.right_child


    def __print_tree(self, root):
        if root == None:
            return
        else:
            self.__print_tree(root.left_child)
            print root.data
            self.__print_tree(root.right_child)


      

random.seed(97697)

tree = BST()
L = [int(1000 * random.random()) for i in xrange(100)]

tree.insert(500)
tree.insert(50)
tree.insert(23)
for i in L:
    tree.insert(i)
#tree.print_tree()


print(tree.find(911))
tree.render()
tree.delete(911)

			
