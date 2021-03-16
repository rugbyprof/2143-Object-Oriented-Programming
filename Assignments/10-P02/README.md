## Program 02 - Graphviz Class
#### Due: 03-25-2021 (Thursday @ 9:30 a.m.)

### Overview

`GraphViz` is a software library that takes a structured syntax and turns it into a visual representation of a "graph" (get it? "graph" "viz"). So it is meant for graph data structures, but it is also decent for other visual representations of arrays or structs. However, let us introduce ourselves to the bare bones basics. 

For our first example, lets create a `node` with the value `A` Notice the `A` is wrapped in two curly braces with the keyword `graph`. This defines it as an "undirected" graph (more in a minute about that):

**Code:**
```dot
graph {
    A
}
```
**Result:** 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_single_node.png" width="50">

Whoa! Simple right? 


Lets add another node `B`: 

**Code:**
```dot
graph {
    A
    B
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_two_nodes.png" width="100">

Easy enough! Let's add a relationship between `A` and `B`:

**Code:**
```dot
graph {
    A -- B
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_single_neighbor.png" width="50">

Can I add a relationship between `B` and `A`??

**Code:**
```dot
graph {
    A -- B
    B -- A
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_two_nodes_two_edges.png" width="50">

Yes I can, but this isn't always what we want. We need to show **direction**! We also need to change the keyword `graph` to `digraph` so `GraphViz` knows it's a directed graph.

**Code:**
```dot
digraph {
    A -> B
    B -> A
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_two_nodes_two_edges_directed.png" width="50">

Graphviz is also pretty smart about positioning your data structures so that they look as you would expect. Check out this "mini" binary tree: 

**Code:**
```dot
digraph {
    A -> B
    A -> C
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_binary_tree_small.png" width="125">


That is the "bare bones" basics of how to add "nodes" and then add "edges" between nodes. What if I wanted to print out a linked list of numbers? Here is my linked list: `Head->3->5->2->11->21->NULL`. This will be easy. 

**Code:**
```dot
digraph {
    Head -> 3
    3 -> 5
    5 -> 2 
    2 -> 11
    11 -> 21
    21 -> NULL
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_linked_list_ud.png" width="50">

Wait!?! Who draws linked lists like that? Lets fix it:

**Code:**
```dot
digraph {
    rankdir="LR";
    Head -> 3
    3 -> 5
    5 -> 2 
    2 -> 11
    11 -> 21
    21 -> NULL
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_linked_list_lr.png" height="40">

By now you should be realizing that even though this isn't photo shop, we still have a lot of potential. We haven't scratched the surface of the capabilities of `GraphViz` but we don't need to. I have a specific (sub)set of requirements for you to implement using `GraphViz`. That subset of requirements has (mostly) to do with with defining "nodes" seperately and then connecting them with styled edges as well. When we do this, we can "style" each node different (if we want), as well as each edge (again, if we want). Let us redraw the linked list using different styles for the head and null pointer nodes:

```dot
digraph {
    rankdir="LR";
    Head [shape=cds, margin=0,fontname="helvetica-bold"]
    NULL [shape=none, margin=0,fontname="helvetica-bold"]
    Head->3 
    3 -> 5
    5->2 
    2->11 
    11->21
    21->NULL 
}
```
**Result:**

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_linked_list_lr_styled.png" height="40">

    

You should notice that we start to define the nodes at the top of the graph, and then we connect them afterwords. We can add generic definitions that account for all of them:

```dot
digraph {
    rankdir="LR";           // make graph go left to right
    node [shape=record];    // applies to all nodes (unless specifically changed)
    Head [shape=cds, margin=0,fontname="helvetica-bold"]    // only for Head node
    NULL [shape=none, margin=0,fontname="helvetica-bold"]   // only for NULL node
    Head->3 
    3 -> 5
    5->2 
    2->11 
    11->21
    21->NULL 
}
```
**Result:**

Each node is now shaped like a "record", except the nodes labeled with "Head" and "NULL". They keep their unique styling. 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/gz_linked_list_lr_node_shape.png" height="40">

    

For example, here is an array: 


```dot
digraph {

    node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];
    values [label="<f0> 66 | <f1>16 | <f2> 32 | <f3> 45 | <f4> 77 | <f5> 66"];

}
```

Which results in: 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/graphviz_array.png" width="500">

### Documentation

- Here Online: https://www.graphviz.org/pdf/dotguide.pdf
- Or in this folder: [docs](./dotguide.pdf)

### Online Graphviz Viewer

https://dreampuf.github.io/GraphvizOnline/


### VSCode Extension

Search For: `@popular graphviz` and install top result to allow you to preview graphs right in VSCode. 




#### Binary Tree Example
```dot
digraph mygraph {
   8 -> 4
   8 -> 12
   4 -> 2
   4-> 6
   12 -> 10
   12 ->14
   2 -> 1
   2 -> 3
   6 -> 5
   6-> 7
   10 -> 9
   10 -> 11
   14 -> 13
   14-> 15
}
```