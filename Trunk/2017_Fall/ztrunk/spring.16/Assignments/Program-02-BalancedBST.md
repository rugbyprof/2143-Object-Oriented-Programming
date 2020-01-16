# Program 2 - Binary Tree Balanced Loading
Due on github by ***Thursday March 10<sup>rd</sup>*** by class time. 

### Overview
Working by yourself, or with a partner, alter the `BinarySearch` class so that the resulting list based tree is perfectly balanced after loading a random set of integers of size _N_. Also, there should be __no__ duplicate key values in the tree. 

Remember the problems we had with inserting random values into this list based implementation of a binary search tree. LOTS of wasted space. We've already discovered that this is not the way to go. But lets try to solve the problem anyway. I guess there is a small chance that we build the balanced tree one time (aka one-time-cost) because all that would occur afterword would be searching the tree (never any inserts or deletes). Then it may be worth it.

Also remember that inserting ordered values into a tree creates a really really crappy BST (aka linked list). Our goal is to obtain O(lg N) search time, not stick with O(N). 

So how do you solve it? Think binary search on an ordered list, and reverse engineer that. 

Also start small. Like 7 values. Remember a `full` & `complete` tree holds 2<sup>h</sup> - 1 (where h = height of the tree). So any power of two minus one will get you a full complete tree.

### Requirements
- Create a folder called `BalancedBinaryTree` for all your files.
- Rename `binary_search_tree_list.py` to  `balanced_binary_tree.py`.
- Rename the `BinarySearch` class to `BalancedSearch`.
- Alter the BalancedSearch class so that it results in a balanced binary tree representation of a given set of integers.
- Ask the user "Number to insert: (1-100000) ", then load that amount of numbers into the tree.
- Add another insert method so that it receives a `list` instead of an `int`:

```python
"""
@Name: insertList
@Description:
    Receives a list of unordered integers and inserts them into the binary tree in such a manner that the resulting tree is balanced.
@Params:
    values (List) - unorderd list of integers
@Returns: None
"""
```

***Additional Helper Code***

```python
# Create a list to hold unique integers
unique = []

# loop 1000 times
for x in range(1000):

    # get a random number
    r = random.randint(0,99999)
    
    # if it's not already in the list, enter it.
    if r not in unique:
        unique.append(r)

# Sort the list
unique.sort()

```

## Starter Code:
Code can be found [here](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/blob/master/binary_search_tree_list.py).

### Deliverables

- Upload everything to gitHub this means the folder and all it's contents named correctly.
- The file should execute with no errors.
- If you worked with a partner, both people should have the code in thier repo.
- Your name (or both names) should be in all documents.
- Comment, Comment, Comment ....

