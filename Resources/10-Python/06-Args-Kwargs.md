# Args - Kwargs

Let me give some background with functions in general and how we define parameters and arguemnts.  This will kind of motivate the whole `args` and `kwargs` idea. 

### Functions

- Remember a function is a logical chunk of code that receive a set of parameters that determine what value will be returned by the function. 
- Functions usually are chunks (blocks) of code that seem to be repeated over and over, so we remove them and turn them into their own logical component.

### Parameters vs Arguments

- I find myself using these terms as synonyms and they are not. 
- Here is the definition of each: 
  - A parameter is the variable in the declaration of function (function header). 
  - An argument is the actual value of this variable that gets passed to function (function call).

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
    """ Sum up the values in a list.
    """
    if not type(L) is list:
        raise ValueError('This is not a list')
    total = 0
    for i in L:
       total += i
    return total
```

Since python doesnt really "overload" function definitions, there needs to be a way to pass in different combinations of parameters to a function, so we can change its behavior based on our needs. In C++ we would create different function definitions for every one of our needs (just look at all the overloaded class constructors we wrote!). In python, if you want to pass in a variable set of arguments, you use `*args`, and if you want to pass in arguments that don't have an order, you use keyword arguments, or `**kwargs` 

How do you decide if you need `*args` or `**kwargs`

1. Do I know the names of every parameter before hand?
2. Am I willing to accept any key:value pair?
3. Am I going to need an unknown number of arguments?
4. Am I extending a method in a subclass and I simply want to pass all arguments to the superclass?
5. (Personal Opinion): Do I have so many parameters that it detracts from the printed code itself. Like if your parameter list is so long it starts line wrapping on the screen?

### Args and Kwargs

The syntax for `args` and `kwargs` is the `*` and `**`. The names `*args` and `**kwargs` are only by convention but there's no hard requirement to use those exact names. It's the `*` and `**` that tell the interpreter how to handle each.

You would use `*args` when you're not sure how many arguments might be passed to your function, i.e. it allows you pass an arbitrary number of arguments to your function. For example:

```python
def print_everything(*args):
    for count, thing in enumerate(args):
        print(f'{count}. {thing}')

print_everything('apple', 'banana', 'cabbage')

# OUTPUT:
# 0. apple
# 1. banana
# 2. cabbage
```

Similarly, `**kwargs` allows you to handle named arguments that you have not defined in advance:

```python
def table_things(**kwargs):
    for name, value in kwargs.items():
        print(f'{name}. {value}')

table_things(calculus = 'hard', trig = 'easy', chucknorris='awesome')

# OUTPUT:
# calculus = hard
# trig = easy
# chucknorris = awesome

```

You can use these along with named arguments too. The explicit (positional) arguments get values first and then everything else is passed to `*args` and `**kwargs`. The named arguments come first in the list. For example:

```python
def table_things(titlestring, **kwargs)
```

You can also use both in the same function definition but `*args` must occur before `**kwargs`.

You can also use the `*` and `**` syntax when calling a function. For example:

```python
def print_three_things(a, b, c):
    print(f'a = {a}, b = {b}, c = {c}')

mylist = ['aardvark', 'baboon', 'cat']
print_three_things(*mylist)
# OUTPUT:
# a = aardvark, b = baboon, c = cat
```

As you can see in this case it takes the list (or tuple) of items and unpacks it. By this it matches them to the arguments in the function. Of course, you could have a `*` both in the function definition and in the function call.


<sup>Source: http://stackoverflow.com/questions/3394835/args-and-kwargs </sup>
