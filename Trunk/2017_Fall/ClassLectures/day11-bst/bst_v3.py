#!/usr/bin/python
# -*- coding: utf-8 -*-
import random
import graphviz as gv
import sys
import os
from subprocess import call
from PIL import Image
import time


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

        # self.node_style = {
        #     'fillcolor': 'lightblue2',
        #     'style': 'filled',
        #     'shape': 'box',
        #     'color': 'black'
        # }

class DrawTree(BST):
    def __init__(self):
        super(DrawTree, self).__init__()
        self.viz = []
        self.gif_frames = []
        self.node_id = 0
        self.node_style = {
            'fillcolor': 'lightblue2',
            'style': 'filled',
            'shape': 'box',
            'color': 'black'
        }
        os.system("rm ./images/*.png")
    
    def render(self, name=None,version=None):

        if name:
            if version is not None:
                name = name + "_" + str(version)
        else:
            name = 'bst'
        self.gif_frames.append(name+'.png')
        self.viz.append(gv.Digraph(name=name,format='png'))
        self.reset_nodes(self.root)
        self.__build_viz(self.root)
        self.viz[-1].render(name)



    def __build_viz(self, root, parent=None):
        if root == None and parent:
            self.viz[-1].node(str(self.node_id), '*', shape='point', color='gray')
            self.viz[-1].edge(str(parent.node_id), str(self.node_id),
                          arrowhead='box', arrowsize='.5')
            self.node_id += 1
        if root == None:
            return
        else:
            if not root.node_id:
                root.node_id = self.node_id
                self.node_id += 1
                if not hasattr(root, 'node_style'):
                    root.node_style = self.node_style
                self.viz[-1].node(str(root.node_id), str(root.data), **root.node_style)
            if parent:
                self.viz[-1].edge(str(parent.node_id), str(root.node_id))
            self.__build_viz(root.left, root)
            self.__build_viz(root.right, root)

    def style_node(self,key):
        node = super(DrawTree, self)._BST__find(self.root,key)
        print(node)
        node.node_style = {
            'fillcolor': 'lightblue2',
            'style': 'filled',
            'shape': 'box',
            'color': 'black'
        }
        node.node_style['fillcolor'] = 'red'

    def reset_nodes(self, root):
        if root == None:
            return
        else:
            self.reset_nodes(root.left)
            root.node_id = None
            self.reset_nodes(root.right)

    def create_gif(self):
        #convert in.png -gravity center -background white -extent 900x1500 out.png
        #convert -delay 120 -loop 0 *.png animated.gif

        max_width = 0
        max_height = 0
        images = []
        sizes = []
        print(self.gif_frames)
        for i in range(len(self.gif_frames)):
            images.append(Image.open(self.gif_frames[i]))
            width,height = images[i].size
            print(width,height)
            sizes.append([width,height])
            if width > max_width:
                max_width = width
            if height > max_height:
                max_height = height
        print(max_width,max_height)

        max_width *= 1.15
        max_height *= 1.15

        for i in range(len(sizes)):
            cmd = "convert %s -gravity center -background white -extent %dx%d %s" % (self.gif_frames[i],max_width,max_height,self.gif_frames[i])
            print(cmd)
            os.system(cmd)
        os.system("convert -delay 120 -loop 0 ./images/*.png ./images/animated.gif")

if __name__ == '__main__':
    # http://cs.mwsu.edu/~griffin/2143-ObjectOrientedProgramming/ClassLectures/day11-bst/

    if len(sys.argv) > 1:
        file_name = sys.argv[1]
    else:
        file_name = 'bst'

    random.seed(97697)

    tree = BST()
    num_nodes = 127
    L = [i for i in xrange(num_nodes)]


    random.shuffle(L)
    random.shuffle(L)

    print(L)

    #L = sorted(L)

    tree.insert(num_nodes // 2)
    for i in L:
        tree.insert(i)

    print(tree.find(37))
    # tree.delete(37)
    # tree.delete(6)
    # tree.delete(24)
    # tree.delete(41)

    version=1

    tree2 = DrawTree()
    tree2.insert(num_nodes // 2)
    for i in L:
        tree2.insert(i)
    #print(tree2.find(18))
    print(tree2.style_node(18))
    i = 1
    tree2.render('./images/bst',i)
    # delete = [3,5,7,9,13,16,20,24,26,29]
    # for d in delete:
    #     i += 1
    #     tree2.delete(d)
    #     tree2.render('./images/bst',i)
    #tree2.create_gif()
    # tree2.delete(6)
    # tree2.render('./images/bst',3)
    # tree2.delete(24)
    # tree2.render('./images/bst',4)
    # tree2.delete(41)
    # tree2.render('./images/bst',5)
    # tree2.create_gif()
    #call(["mv", file_name + '.png', file_name])
