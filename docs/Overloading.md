Need to organize into:
- Operator overloading vs method overloading
- Statically typed languages vs dynamically typed (aka c++ vs python)
    - Python would use type checking and / or \*args **kwargs.
    - C++ would simply define the same method with different parameters.

An overloaded declaration is a declaration that had been declared with the same name as a previously declared declaration in the same scope, except that both declarations have different arguments and obviously different definition (implementation).
Function and operator overloading is available in both Python and C++. Some languages, like Java, do not allow overloading, however. Opponents of operator overloading claim that it can make code less readable, as they may look at something like a plus sign and not be sure what exactly the programmer chose to do with his addition method.  
Source: \[[1](http://www.tutorialspoint.com/cplusplus/cpp_overloading.htm), [2](http://beust.com/weblog/2009/04/12/why-java-doesnt-need-operator-overloading-and-very-few-languages-do-really/)]

##Python
In Python, there are a variety of different operators which can be overloaded. Generally, one can "recode" one of these operators by defining a method with a specific name. These methods are named with two underscores, followed by a keyword, and then two more underscores. For example if someone wanted to add the elements of a tuple or a list together, they could overload the addition operator by defining the class \_\_add\_\_().  
    
    class TupleHandler(tuple):
        def __init__(self, tupleA):
            self.tupA = tupleA

    def __add__(self, tupleB):
        tupLength = max(len(self.tupA), len(tupleB))
        for i in range(tupLength):	#This loop will fill in the blank space of the tuple with the smaller length
            if not self.tupA[i]:
                self.tupA[i].append(0)
            elif not tupleB[i]:
            	tupleB[i].append(0)
        
        tupC = []
        for i in range(tupLength):	#Then this loop will add the elements of each tuple together
        	tupC.append(self.tupA[i] + tupleB[i])
        
        return tupC

Notice that we also defined the \_\_init\_\_ class. This is the constructor class which allows us to create custom in-class variables. If we then create a member variable using the above class, we can see how the addition method has changed.

    x = TupleHandler((10,5,2))
    y = (5,10,13)
    print(x+y) #prints [15,15,15]

The addition method in this code iterates through the tuples and adds each element together, rather than just tacking one tuple onto the other as the addition method would have done if we had not overloaded it. 

Sources: \[[3](http://www.python-course.eu/python3_magic_methods.php)\]

##Sources:
1. http://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
2. http://beust.com/weblog/2009/04/12/why-java-doesnt-need-operator-overloading-and-very-few-languages-do-really/
3. http://www.python-course.eu/python3_magic_methods.php