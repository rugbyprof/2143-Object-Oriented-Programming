## Program 02 - Graphviz Class
#### Due: 03-25-2021 (Thursday @ 9:30 a.m.)

### Overview

`GraphViz` is a software library that takes a structured syntax and turns it into a visual representation of a "graph" (get it? "graph" "viz"). It allows a developer to visualize what may be happening with our data structures. Wouldn't you like to see your `linked list` printed as something more than: 

`head->10->20->30->null` ?? 

Ok, simple example, but what about a hash table? Or binary tree? Graphics in C++ suck (Just ask SFML!! :joy:). And no, we're not giving up on SFML, but I think graphviz gives us a good chance to work on our OOP skills and write a class to extend and use for other things.

[Graphviz Introduction](graphviz_intro.md)

### Documentation

- Online: https://www.graphviz.org/pdf/dotguide.pdf
- Or in this folder: [docs](./dotguide.pdf)

### Online Graphviz Viewer

Lets you live code the graphviz dot language to manipulate data structures:

https://dreampuf.github.io/GraphvizOnline/


### VSCode Extension

Search For: `@popular graphviz` and install top result to allow you to preview graphs right in VSCode. 

### Helper Links

There are more than just these, but these stuck out when I was preparing my tutorial:

- Simple but has c++ code to write a simple digraph:
  - https://devjeetr.wordpress.com/2012/04/30/visualising-a-binary-search-tree-using-graphviz/
- Decent examples of a few different data structures:
  - https://eddmann.com/posts/using-graphviz-with-svg-output-in-php/
- Spacing tricks (not necessary):
  - https://stackoverflow.com/questions/23429600/how-do-i-make-a-dot-graph-representing-a-binary-tree-more-symmetric
- Part of the graphviz docs:
  - https://graphviz.org/doc/info/shapes.html
  - http://www.graphviz.org/doc/info/attrs.html
  - https://graphviz.org/Gallery/directed/crazy.html

### Requirements

Write a c++ class or classes to implement a graphviz language "wrapper" or "facade". This means we will be implementing a (tiny) subset of the graphviz language capability so we can visualize some of the typical data structures that we have learned up to now (from 1063 and or 3013). If you haven't 3013, then let me tell you what you should be thinking about: 

#### Linked List

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_linked_list_lr_node_shape.png" height="40">

#### Plain Binary Tree

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_binary_tree_plain.png" width="400">

#### Not So Plain Binary Tree 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_binary_tree_w_records.png" width="400">

### Input File

The input file will be formatted like the following:

- First line
  - graph = undirected graph
  - digraph = directed graph
- Second line = number of nodes: N
- Lines 2 -> N 
  - node id then node label
- After the nodes will be an integer with number of edges: E
- Lines N+1 -> N+E
  - StartNode EndNode EdgeLabel

Example:
```txt
digraph
3
A Angola
B Bolivia
C Congo
5
A B 34
A C 746
B C 87
B A sd
C B Hello
```

Big example [HERE](example_input_file.txt)