# Args - Kwargs

### Functions

- Let me re-iterate to the class: Functions are chunks of code that (typically) do ONE thing and they do it well.
- Functions do not calculate the area under a curve just to print out the result. They would return the result. 
- I digress....

### Parameters vs Arguments
NOTE: This is just a side note!

These terms are used interchangeably, although probably not correctly. I catch myself doing it sometimes, so here 
is the clarification of parameter vs argument:

- A parameter is a variable in a function definition. 
- When a function is called, the arguments are the data you pass into the function's parameters. 
- Parameter is the variable (in the declaration of function). 
- Argument is the actual value (of this variable that gets passed to function).

### Function Parameters

A function is a chunk of code that does it's one thing. For example:

```python

def MySum(a,b):
    return a + b
```

This function adds the values passed into MySum, and returns the answer. Simple.

Now I want to sum 3 values:

```python

def MySum(a,b,c):
    return a + b
```
Simple enough. But now I want to sum N values:

```python

def MySum(L):
    if not type(L) is list:
        raise ValueError('This is not a list')
    total = 0
    for i in L:
       total += i
    return total
```

Wait! Bad example? Well no, this is an example of an arbitrary number of parameters .... of the same type. Yes I know lists hold mixed types, but the function name implies that it expects integers. 

There are time when you might need a variable set of parameters, so  here are the questions you could ask yourself to see if `*args` or `**kwargs` is necessary:

1. Do I know the names of every parameter before hand?
2. Am I willing to accept any key:value pair?
3. Am I going to need an unknown number of arguments?
3. Am I extending a method in a subclass and I simply want to pass all arguments to the superclass?
4. (Personal Opinion): Do I have so many parameters that it detracts from the printed code itself. Like if your parameter list is so long it starts line wrapping on the screen?

### Args and Kwars

The syntax for `args` and `kwargs` is the `*` and `**`. The names `*args` and `**kwargs` are only by convention but there's no hard requirement to use them.

You would use `*args` when you're not sure how many arguments might be passed to your function, i.e. it allows you pass an arbitrary number of arguments to your function. For example:

```
>>> def print_everything(*args):
        for count, thing in enumerate(args):
...         print '{0}. {1}'.format(count, thing)
...
>>> print_everything('apple', 'banana', 'cabbage')
0. apple
1. banana
2. cabbage
```

Similarly, `**kwargs` allows you to handle named arguments that you have not defined in advance:

```
>>> def table_things(**kwargs):
...     for name, value in kwargs.items():
...         print '{0} = {1}'.format(name, value)
...
>>> table_things(apple = 'fruit', cabbage = 'vegetable')
cabbage = vegetable
apple = fruit
```

You can use these along with named arguments too. The explicit arguments get values first and then everything else is passed to `*args` and `**kwargs`. The named arguments come first in the list. For example:

```python
def table_things(titlestring, **kwargs)
```

You can also use both in the same function definition but `*args` must occur before `**kwargs`.

You can also use the `*` and `**` syntax when calling a function. For example:

```
>>> def print_three_things(a, b, c):
...     print 'a = {0}, b = {1}, c = {2}'.format(a,b,c)
...
>>> mylist = ['aardvark', 'baboon', 'cat']
>>> print_three_things(*mylist)
a = aardvark, b = baboon, c = cat
```

As you can see in this case it takes the list (or tuple) of items and unpacks it. By this it matches them to the arguments in the function. Of course, you could have a `*` both in the function definition and in the function call.


<sup>Source: http://stackoverflow.com/questions/3394835/args-and-kwargs </sup>
