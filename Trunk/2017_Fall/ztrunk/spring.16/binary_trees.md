

## Tree Definitions

A graph is an ordered pair ___G = (V, E)___ comprising a set ___V___ of vertices, (aka: nodes or points) together with a set ___E___ of edges, (aka: arcs or lines).

A tree is an ___undirected graph___ in which any two vertices are connected by exactly one path. In other words, any acyclic connected graph is a tree.

### File System Tree
    
![](https://s3.amazonaws.com/f.cl.ly/items/2c3l1c3j113i3n3y343z/tree_file_system.png)

- ***Node***
    - A node is a fundamental part of a tree. It can have a name, which we call the “key.”
A node may also have additional information. We call this additional information the
“payload.” While the payload information is not central to many tree algorithms, it is
often critical in applications that make use of trees.
- ***Edge*** 
    - An edge is another fundamental part of a tree. An edge connects two nodes to show
that there is a relationship between them. Every node (except the root) is connected by
exactly one incoming edge from another node. Each node may have several outgoing
edges.
- ***Root*** 
    - The root of the tree is the only node in the tree that has no incoming edges. `/` is the root in the file system tree.
- ***Path*** 
    - A path is an ordered list of nodes that are connected by edges. For example, Mammal →
Carnivora → Felidae → Felis → Domestica is a path.
Children The set of nodes c that have incoming edges from the same node to are said to be the
children of that node. In the file system tree, nodes `log/`, `spool/`, and `yp/` are the children of node
`var/`.
- ***Parent*** 
    - A node is the parent of all the nodes it connects to with outgoing edges. In the tree above
the node `var/` is the parent of nodes `log/`, `spool/`, and `yp/`.

- ***Sibling*** 
    - Nodes in the tree that are children of the same parent are said to be siblings. The nodes
etc/ and usr/ are siblings in the filesystem tree.
- ***Subtree*** 
    - A subtree is a set of nodes and edges comprised of a parent and all the descendants of
that parent.
- ***Leaf Node*** 
    - A leaf node is a node that has no children. For example, node3, 4, 5 and node6 are leaf nodes.

![](https://s3.amazonaws.com/f.cl.ly/items/0t342r0q3g333E2r2p1h/tree_edges_nodes.png)

- ***Level*** 
    - The level of a node 𝑛 is the number of edges on the path from the root node to 𝑛. For
example, the level of the Felis node in Figure 6.1 is five. By definition, the level of the
root node is zero.
- ***Height*** 
    - The height of a tree is equal to the maximum level of any node in the tree. The height
of the tree in Figure 6.2 is two.

| Sources |        |
|:------:|---------|
|1        | [Problem Solving with Algorithms and DataStructures](https://www.cs.auckland.ac.nz/courses/compsci105ssc/resources/ProblemSolvingwithAlgorithmsandDataStructures.pdf) |
|2       |[Wikipedia: Undirected Graph]( https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)#Undirected_graph) |
