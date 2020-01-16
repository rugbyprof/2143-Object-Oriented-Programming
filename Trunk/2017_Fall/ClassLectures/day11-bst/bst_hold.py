#!/usr/bin/python
# -*- coding: utf-8 -*-
import random
import graphviz as gv
import sys
import os
from subprocess import call


class Node(object):

    def __init__(self, val):
        self.data = val
        self.left_child = None
        self.right_child = None
        self.parent = None
        self.node_id = None
        self.node_style = {
            'fillcolor': 'lightblue2',
            'style': 'filled',
            'shape': 'box',
            'color': 'black'
        }

    def setVal(self, val):
        self.data = val

    def setLeftChild(self, node):
        self.left_child = node
        self.left_child.parent = self

    def setRightChild(self, node):
        self.right_child = node
        self.right_child.parent = self

    def __str__(self):
        try:
            left = str(self.left_child.data)
        except:
            left = '-1'

        try:
            right = str(self.right_child.data)
        except:
            right = '-1'
        return '[D:%s , L:%s , R:%s]' % (str(self.data), left, right)


class BST(object):

    def __init__(self):
        self.root = None

    def print_tree(self):
        self.__print_tree(self.root)

    def find(self, key):
        node = self.__find(self.root, key)
        p,pred = self.__predecessor(node)
        p.node_style['fillcolor'] = 'deeppink2'
        p,succ = self.__successor(node)
        p.node_style['fillcolor'] = 'deeppink2'
        return node

    def render(self, name=None):
        if name is None:
            name = 'bst.png'
        self.viz = gv.Digraph(format='png')
        self.node_id = 0
        self.__build_viz(self.root)
        self.viz.render(name)
        # print(self.viz.source)

    def __build_viz(self, root, parent=None):
        if root == None and parent:
            self.viz.node(str(self.node_id), '*', shape='point', color='gray')
            self.viz.edge(str(parent.node_id), str(self.node_id),
                          arrowhead='box', arrowsize='.5')
            self.node_id += 1
        if root == None:
            return
        else:
            if not root.node_id:
                root.node_id = self.node_id
                self.node_id += 1
                self.viz.node(str(root.node_id), str(
                    root.data), **root.node_style)
            if parent:
                self.viz.edge(str(parent.node_id), str(root.node_id))
            self.__build_viz(root.left_child, root)
            self.__build_viz(root.right_child, root)

    def insert(self, data):

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
                    temp = temp.left_child
                else:
                    direction = 'right'
                    temp = temp.right_child

            # Update parent pointer.
            if direction == 'left':
                parent.left_child = Node(data)
                parent.left_child.parent = parent

            else:
                parent.right_child = Node(data)
                parent.right_child.parent = parent

    def delete(self, key):
        self.__delete(self.root, key)

    def __delete(self, root, key):
        node = self.__find(root, key)
        if self.__isleaf(node):
            if node.parent.left_child == node:
                node.parent.left_child = None
            else:
                node.parent.right_child = None
        elif node.left_child and node.right_child:
            parent,pred = self.__predecessor(node)

            # check if leaf
            if not pred.left_child and not pred.right_child:
                node.data = pred.data
                if parent.left_child == pred:
                    parent.left_child = None
                else:
                    parent.right_child = None

                return
        elif node.left_child:
            if node.parent.left_child == node:
                node.parent.left_child = node.left_child
            else:
                node.parent.right_child = node.left_child
        else:
            if node.parent.left_child == node:
                node.parent.left_child = node.right_child
            else:
                node.parent.right_child = node.right_child

    def __isleaf(self,node):
        return node.left_child is None and node.right_child is None

    def __predecessor(self, root):
        if not root.left_child:
            return [root,None]

        parent = root
        root = root.left_child
        while root.right_child is not None:
            parent = root
            root = root.right_child
        root.node_style['fillcolor'] = 'red'
        return [parent,root]

    def __successor(self, root):
        if not root.right_child:
            return [root,None]

        parent = root
        root = root.right_child

        while root.left_child is not None:
            parent = root
            root = root.left_child
        root.node_style['fillcolor'] = 'green'
        return [parent,root]

    def __single_child(self, node):
        if node.left_child and node.right_child:
            return None
        elif node.left_child:
            return node.left_child
        else:
            return node.right_child

    def __find(self, root, key):
        while True:
            if root == None:
                return None
            elif root.data == key:
                root.node_style['fillcolor'] = 'yellow'
                print(self.__single_child(root))
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


def bin_order(L):
    newL = []
    if len(L) == 0:
        return
    else:
        bin_order(leftside)
        bin_order(rightside)


if __name__ == '__main__':

    if len(sys.argv) > 1:
        file_name = sys.argv[1]
    else:
        file_name = 'bst.png'

    random.seed(97697)

    tree = BST()
    num_nodes = 50
    L = [i for i in xrange(num_nodes)]

    random.shuffle(L)
    random.shuffle(L)

    print(L)

    #L = sorted(L)

    tree.insert(num_nodes // 2)
    for i in L:
        tree.insert(i)

    print(tree.find(37))
    tree.delete(37)
    tree.delete(6)
    tree.delete(24)
    tree.delete(41)
    tree.render(file_name)
    call(["mv", file_name + '.png', file_name])
