## Program 3 - Graphviz Class
#### Due: 03-09-2023 (Thursday @ 2:00 p.m.)


## Overview

Write a class that will generate graphviz "dot" syntax so you can visualize the output of your data structures. Graphviz is used for "graph visualization" and provides a simple way to visualize linked data structures. For example the following code:


```dot
digraph foo {
        rankdir=LR;
        node [shape=record]
        null [shape=circle,color=white];
        1 -> 2 
        2 -> 3
        3 -> null
}

```

Creates the following output: 

![](./images/LL1.png)

The example above is very simple which can make Graphviz really easy to use and learn. Having said that, Graphviz can get very very complex as well. If we were to attempt to implement all the features available, we would probably invest multiple semesters to get it done.  So we are only going to implement a small portion of the featqures that Graphviz offers. The example below is more on par with the features we want to utilize.

```dot
digraph linkedlist {
        rankdir=LR;
        node [shape=record,color=purple];
        1 [label="{ <data> 12 | <next>  }"]
        2 [label="{ <data> 99 | <next>  }"];
        3 [label="{ <data> 37 | <next>  }"];
        null [shape=circle,color=white];
        1:next:3 -> 2:data [arrowhead=vee, arrowtail=dot, color=orange, dir=both, tailclip=false];
        2:next:3 -> 3:data [arrowhead=vee, arrowtail=dot, color=orange, dir=both, tailclip=false];
        3:next:3 -> null  [arrowhead=vee, arrowtail=dot, color=orange, dir=both, tailclip=false];
}
```

Creates the following output: 

![](./images/LL2.png)

### Graphviz Online

How do we generate the images in this document? Take the code examples from above and paste them into the online Graphviz editor here: [GraphvizOnline](https://dreampuf.github.io/GraphvizOnline/)

Documentation for Graphviz is here: [Docs](https://graphviz.org/doc/info/lang.html)
Some good examples can be found here: [Examples](https://graphs.grevian.org/example)
More complex examples [here](https://graphviz.org/gallery/)


## Requirements

Your Graphviz class should be able to:

- Add nodes
- Add edges between nodes
  
The styles you need to implement are:

- Colored nodes
- Colored edges
- Edge direction includes: None, One, Both
- Node shapes: should include "record" plus at least 3 more from [here](http://www.graphviz.org/doc/info/shapes.html) 
- Edge shapes: choose at least 4 from [here](http://www.graphviz.org/doc/info/arrows.html)


## Tests

Run this code with your class and make sure you get the same output. The example below uses method names that I might use. You can use any method names you want, as long as they are descriptive and give same output. 

I want your test program to write to stdout AND a file called `test.out`. Your name, date and course (Fall 2143) should be written at top of output file (with your code):

**Example Output File (portion of)**
```
Name
Date
Fall 2143

digraph foo {
        rankdir=LR;
        node [shape=record];
        a [label="{ <data> 12 | <ref>  }", width=1.2]
        b [label="{ <data> 99 | <ref>  }"];
        c [label="{ <data> 37 | <ref>  }"];
        null [shape=plain];
        a:ref:n -> b:data [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=1.2];
        b:ref:n -> c:data [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];
        c:ref:n -> null   [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];
}

etc...
```

** Image Output **



**Example Code Run**
```cpp

List L;
L.addNode(5);
L.addNode(7);
L.addNode(9);
L.print();
```

### Deliverables

- Create a folder in your assignments folder called `P01`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.

```
2143 
P01
Name
```

- Print out your source code. Make sure it's **[commented](../../Resources/01-Comments/README.md)**.
- Print out your output file.
- Put your assignment on the lecture podium at the beginning of class.
- Staple everything in this order:
  - **1)** Banner (on top)
  - **2)** Source code (middle)
  - **3)** Output (bottom)
- Any hand writing on your assignment is reduction in 1 letter grade.
- Failure to follow instructions is a reduction in 1 letter grade.


## Helper Files

|   #   | Name                                               | Description                           |
| :---: | :------------------------------------------------- | :------------------------------------ |
|   1   | [bst.cpp](cpp_code/bst.cpp)                        | Binary search tree cpp code           |
|   2   | [linked.cpp](cpp_code/bst.cpp)                     | Linked list cpp code                  |
|   3   | [bst.dot](dot_Files/bst.dot)                       | Binary search tree graphviz example   |
|   4   | [bst2.dot](dot_Files/bst2.dot)                     | Binary search tree graphviz example 2 |
|   5   | [red_black_tree.dot](dot_Files/red_black_tree.dot) | Red black tree graphviz example       |


