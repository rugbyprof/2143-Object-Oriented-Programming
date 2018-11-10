A destructor is the polar opposite to the constructor. It is a method that is, automatically if specified, called when an instance/object is about to be destroyed.While being executed it is recovering heap space that was used/allocated during the lifetime of an object. It also closes files and release network resources and resource locks. Destructors can not be overloaded nor can it be inherited. It is used in classes.  
Source: [ [1] ]  

##Destructor  
![](http://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Companion/cxx_crib/constr.gif)  
Source: [ [6] ]
###Syntax in different languages:
In C++, destructors have the same name as the class of which they are associated with, but prefixed with a tilde (~).  
In Python, the destructor method is named "__del__". 
In Java, there are no destructors   because java objects are all heap allocated and garbage collected. Instead Java doess support finalizers that are meant to safeguard objects that handle native resources like sockets,window handles, file handles, and etc.  
Source: [ [2] , [3] ]  

##Example Code:

###C++:
Destructors in c++ have the same name as the class.
```c++
#include <iostream>
 
using namespace std;
 
class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line();   // This is the constructor declaration
      ~Line();  // This is the destructor: declaration
 
   private:
      double length;
};
 
// Member functions definitions including constructor
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
```
Source: [ [4] ] 

###Python:
```python
class Point:
   def __init( self, x=0, y=0):
      self.x = x
      self.y = y
   def __del__(self):
      class_name = self.__class__.__name__
      print class_name, "destroyed"

pt1 = Point()

#Destructor __del__ is called by "del"
del pt1
```
Source: [ [5] ]  
##Sources:
1.https://www.techopedia.com/definition/24284/destructor  
2.https://docs.python.org/2/reference/datamodel.html#object.__del__  
3.http://stackoverflow.com/questions/171952/is-there-a-destructor-for-java  
4.http://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.htm  
5.http://code.runnable.com/UrvLAdnKp0A9AA3s/destructor-in-python-__del__-for-destructors  
6.http://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Companion/cxx_crib/constr.gif  

[1]:https://www.techopedia.com/definition/24284/destructor  
[2]:https://docs.python.org/2/reference/datamodel.html#object.__del__  
[3]:http://stackoverflow.com/questions/171952/is-there-a-destructor-for-java  
[4]:http://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.htm  
[5]:http://code.runnable.com/UrvLAdnKp0A9AA3s/destructor-in-python-__del__-for-destructors  
[6]:http://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Companion/cxx_crib/constr.gif