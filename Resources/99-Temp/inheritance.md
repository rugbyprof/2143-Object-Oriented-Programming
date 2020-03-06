# Inheritance in C++



The capability of a class to derive properties and characteristics from another class is called
**Inheritance** . Inheritance is one of the most important feature of Object Oriented Programming.  
**Sub Class:** The class that inherits properties from another class is called Sub class or Derived
Class.  
**Super Class:** The class whose properties are inherited by sub class is called Base Class or Super
class.

**The article is divided into following subtopics:**

1.  [Why and when to use inheritance?](#Why%20and%20when%20to%20use%20inheritance?)
2.  [Modes of Inheritance](#Modes%20of%20Inheritance)
3.  [Types of Inheritance](#Types%20of%20Inheritance)

**\[\]{\#Why and when to use inheritance?} Why and when to use inheritance?**

Consider a group of vehicles. You need to create classes for Bus, Car and Truck. The methods
fuelAmount(), capacity(), applyBrakes() will be same for all of the three classes. If we create
these classes avoiding inheritance then we have to write all of these functions in each of the three
classes as shown in below figure:  
<https://media.geeksforgeeks.org/wp-content/uploads/inheritance.png>

  

  

You can clearly see that above process results in duplication of same code 3 times. This increases
the chances of error and data redundancy. To avoid this type of situation, inheritance is used. If
we create a class Vehicle and write these three functions in it and inherit the rest of the classes
from the vehicle class, then we can simply avoid the duplication of data and increase re-usability.
Look at the below diagram in which the three classes are inherited from vehicle class:
<https://media.geeksforgeeks.org/wp-content/uploads/inheritance2.png>  
Using inheritance, we have to write the functions only one time instead of three times as we have
inherited rest of the three classes from base class(Vehicle).

**Implementing inheritance in C++** : For creating a sub-class which is inherited from the base
class we have to follow the below syntax.  
**Syntax** :

    class subclass_name : access_mode base_class_name
    {
    //body of subclass
    };

Here, **subclass\_name** is the name of the sub class, **access\_mode** is the mode in which you
want to inherit this sub class for example: public, private etc. and **base\_class\_name** is the
name of the base class from which you want to inherit the sub class.  
**Note** : A derived class doesn’t inherit ***access*** to private data members. However, it does
inherit a full parent object, which contains any private members which that class declares.



```cpp
// C++ program to demonstrate implementation
// of Inheritance

#include <bits/stdc++.h>
using namespace std;

//Base class
class
    Parent {

public
    :
    int
        id_p;
};

// Sub class inheriting from Base Class(Parent)
class
    Child : public Parent {

public
    :
    int
        id_c;
};

//main function
int main()

{

    Child obj1;

    // An object of class child has all data members

    // and member functions of class parent

    obj1.id_c = 7;

    obj1.id_p = 91;

    cout << "Child id is "
          <<  obj1.id_c << endl;

    cout << "Parent id is "
          <<  obj1.id_p << endl;

    return 0;
}

```

<div class="code-editor-container">

</div>

</div>

<div class="code-output-container">

<div class="output-block">

*chevron\_right*

``` output-pre
```

</div>

<div class="ide-link-div">

*filter\_none*

``` 
```

</div>

</div>

Output:

    Child id is 7
    Parent id is 91

In the above program the ‘Child’ class is publicly inherited from the ‘Parent’ class so the public
data members of the class ‘Parent’ will also be inherited by the class ‘Child’.

**\[\]{\#Modes of Inheritance} Modes of Inheritance**

1.  **Public mode** : If we derive a sub class from a public base class. Then the public member of
    the base class will become public in the derived class and protected members of the base class
    will become protected in derived class.
2.  **Protected mode** : If we derive a sub class from a Protected base class. Then both public
    member and protected members of the base class will become protected in derived class.
3.  **Private mode** : If we derive a sub class from a Private base class. Then both public member
    and protected members of the base class will become Private in derived class.

**Note :** The private members in the base class cannot be directly accessed in the derived class,
while protected members can be directly accessed. For example, Classes B, C and D all contain the
variables x, y and z in below example. It is just question of access.

<div class="noIdeBtnDiv">

<div class="code-block">

<div class="code-gutter">

<div class="editor-buttons-container">

<div class="editor-buttons">

<div class="editor-buttons-div" title="Run and Edit">

*filter\_none*

<div id="run-and-edit-loader" class="ring-load">

</div>

*edit*  
*close*

<div id="run-code-loader" class="ring-load">

</div>

*play\_arrow*

<div id="generate-url-loader" class="ring-load">

</div>

*link*  
*brightness\_5*  
*code*

</div>

</div>

</div>

</div>

    ```cpp
    // C++ Implementation to show that a derived class
    // doesn’t inherit access to private data members.
    // However, it does inherit a full parent object
    class
        A {
    public
        :
        int
            x;
    
    protected
        :
        int
            y;
    
    private
        :
        int
            z;
    };
    
    class
        B : public A {
    
        // x is public
    
        // y is protected
    
        // z is not accessible from B
    };
    
    class
        C : protected A {
    
        // x is protected
    
        // y is protected
    
        // z is not accessible from C
    };
    
    class
        D : private A
    // 'private' is default for classes
    {
    
        // x is private
    
        // y is private
    
        // z is not accessible from D
    };
    
    ```

<div class="code-editor-container">

</div>

</div>

<div class="code-output-container">

<div class="output-block">

*chevron\_right*

``` output-pre
```

</div>

<div class="ide-link-div">

*filter\_none*

``` 
```

</div>

</div>

</div>

The below table summarizes the above three modes and shows the access specifier of the members of
base class in the sub class when derived in public, protected and private modes:  
![](https://media.geeksforgeeks.org/wp-content/cdn-uploads/table-class.png)

**\[\]{\#Types of Inheritance} Types of Inheritance in C++**

1.  **Single Inheritance** : In single inheritance, a class is allowed to inherit from only one
    class. i.e. one sub class is inherited by one base class only.
    ![](https://media.geeksforgeeks.org/wp-content/uploads/single-inheritance.png)  
    **Syntax** :
    
        class subclass_name : access_mode base_class
        {
        //body of subclass
        };
    
    <div class="code-block">
    
    <div class="code-gutter">
    
    <div class="editor-buttons-container">
    
    <div class="editor-buttons">
    
    <div class="editor-buttons-div" title="Run and Edit">
    
    *filter\_none* ::: {\#run-and-edit-loader .ring-load}
    
    </div>
    
    *edit*  
    *close*
    
    <div id="run-code-loader" class="ring-load">
    
    </div>
    
    *play\_arrow*
    
    <div id="generate-url-loader" class="ring-load">
    
    </div>
    
    *link*  
    *brightness\_5*  
    *code*
    
    </div>
    
    </div>
    
    </div>
    
    </div>
    
        ```cpp
        // C++ program to explain
        // Single inheritance
        #include <iostream>
        using namespace std;
        
        // base class
        class
            Vehicle {
        
        public
            :
            Vehicle()
        
            {
        
                cout << "This is a Vehicle"
                     << endl;
            }
        };
        
        // sub class derived from two base classes
        class
            Car : public Vehicle {
        };
        
        // main function
        int main() {
        
            // creating object of sub class will
        
            // invoke the constructor of base classes
        
            Car obj;
        
            return 0;
        }
        
        ```
    
    <div class="code-editor-container">
    
    </div>
    
    :::
    
    <div class="code-output-container">
    
    <div class="output-block">
    
    *chevron\_right*
    
    ``` output-pre
    ```
    
    </div>
    
    <div class="ide-link-div">
    
    *filter\_none*
    
    ``` 
    ```
    
    </div>
    
    </div>
    
    Output:
    
        This is a vehicle

2.  **Multiple Inheritance:** Multiple Inheritance is a feature of C++ where a class can inherit
    from more than one classes. i.e one **sub class** is inherited from more than one **base
    classes** . ![](https://media.geeksforgeeks.org/wp-content/uploads/multiple-inheritance.png)  
    **Syntax** :
    
        class subclass_name : access_mode base_class1, access_mode base_class2, ....
        {
        //body of subclass
        };
    
    Here, the number of base classes will be separated by a comma (‘,’) and access mode for every
    base class must be specified.
    
    <div class="code-block">
    
    <div class="code-gutter">
    
    <div class="editor-buttons-container">
    
    <div class="editor-buttons">
    
    <div class="editor-buttons-div" title="Run and Edit">
    
    *filter\_none* ::: {\#run-and-edit-loader .ring-load}
    
    </div>
    
    *edit*  
    *close*
    
    <div id="run-code-loader" class="ring-load">
    
    </div>
    
    *play\_arrow*
    
    <div id="generate-url-loader" class="ring-load">
    
    </div>
    
    *link*  
    *brightness\_5*  
    *code*
    
    </div>
    
    </div>
    
    </div>
    
    </div>
    
        ```cpp
        // C++ program to explain
        // multiple inheritance
        #include <iostream>
        using namespace std;
        
        // first base class
        class
            Vehicle {
        
        public
            :
            Vehicle()
        
            {
        
                cout << "This is a Vehicle"
                     << endl;
            }
        };
        
        // second base class
        class
            FourWheeler {
        
        public
            :
            FourWheeler()
        
            {
        
                cout << "This is a 4 wheeler Vehicle"
                     << endl;
            }
        };
        
        // sub class derived from two base classes
        class
            Car : public Vehicle,
                  public FourWheeler {
        };
        
        // main function
        int main() {
        
            // creating object of sub class will
        
            // invoke the constructor of base classes
        
            Car obj;
        
            return 0;
        }
        
        ```
    
    <div class="code-editor-container">
    
    </div>
    
    :::
    
    <div class="code-output-container">
    
    <div class="output-block">
    
    *chevron\_right*
    
    ``` output-pre
    ```
    
    </div>
    
    <div class="ide-link-div">
    
    *filter\_none*
    
    ``` 
    ```
    
    </div>
    
    </div>
    
    Output:
    
        This is a Vehicle
        This is a 4 wheeler Vehicle
    
    Please visit [this](https://www.geeksforgeeks.org/multiple-inheritance-in-c/) link to learn
    multiple inheritance in details.

3.  **Multilevel Inheritance** : In this type of inheritance, a derived class is created from
    another derived class.
    ![](https://media.geeksforgeeks.org/wp-content/uploads/multilevel-inheritance.png)
    
    <div class="code-block">
    
    <div class="code-gutter">
    
    <div class="editor-buttons-container">
    
    <div class="editor-buttons">
    
    <div class="editor-buttons-div" title="Run and Edit">
    
    *filter\_none* ::: {\#run-and-edit-loader .ring-load}
    
    </div>
    
    *edit*  
    *close*
    
    <div id="run-code-loader" class="ring-load">
    
    </div>
    
    *play\_arrow*
    
    <div id="generate-url-loader" class="ring-load">
    
    </div>
    
    *link*  
    *brightness\_5*  
    *code*
    
    </div>
    
    </div>
    
    </div>
    
    </div>
    
        ```cpp
        // C++ program to implement
        // Multilevel Inheritance
        #include <iostream>
        using namespace std;
        
        // base class
        class
            Vehicle {
        
        public
            :
            Vehicle()
        
            {
        
                cout << "This is a Vehicle"
                     << endl;
            }
        };
        class
            fourWheeler : public Vehicle {
        public
            :
            fourWheeler()
        
            {
        
                cout << "Objects with 4 wheels are vehicles"
                     << endl;
            }
        };
        // sub class derived from two base classes
        class
            Car : public fourWheeler {
        
        public
            :
            car()
        
            {
        
                cout << "Car has 4 Wheels"
                     << endl;
            }
        };
        
        // main function
        int main() {
        
            //creating object of sub class will
        
            //invoke the constructor of base classes
        
            Car obj;
        
            return 0;
        }
        
        ```
    
    <div class="code-editor-container">
    
    </div>
    
    :::
    
    <div class="code-output-container">
    
    <div class="output-block">
    
    *chevron\_right*
    
    ``` output-pre
    ```
    
    </div>
    
    <div class="ide-link-div">
    
    *filter\_none*
    
    ``` 
    ```
    
    </div>
    
    </div>
    
    output:
    
        This is a Vehicle
        Objects with 4 wheels are vehicles
        Car has 4 Wheels

4.  **Hierarchical Inheritance** : In this type of inheritance, more than one sub class is inherited
    from a single base class. i.e. more than one derived class is created from a single base class.
    ![](https://media.geeksforgeeks.org/wp-content/uploads/hierarchical-inheritance.png)
    
    <div class="code-block">
    
    <div class="code-gutter">
    
    <div class="editor-buttons-container">
    
    <div class="editor-buttons">
    
    <div class="editor-buttons-div" title="Run and Edit">
    
    *filter\_none* ::: {\#run-and-edit-loader .ring-load}
    
    </div>
    
    *edit*  
    *close*
    
    <div id="run-code-loader" class="ring-load">
    
    </div>
    
    *play\_arrow*
    
    <div id="generate-url-loader" class="ring-load">
    
    </div>
    
    *link*  
    *brightness\_5*  
    *code*
    
    </div>
    
    </div>
    
    </div>
    
    </div>
    
        ```cpp
        // C++ program to implement
        // Hierarchical Inheritance
        #include <iostream>
        using namespace std;
        
        // base class
        class
            Vehicle {
        
        public
            :
            Vehicle()
        
            {
        
                cout << "This is a Vehicle"
                     << endl;
            }
        };
        
        // first sub class
        class
            Car : public Vehicle {
        };
        
        // second sub class
        class
            Bus : public Vehicle {
        };
        
        // main function
        int main() {
        
            // creating object of sub class will
        
            // invoke the constructor of base class
        
            Car obj1;
        
            Bus obj2;
        
            return 0;
        }
        
        ```
    
    <div class="code-editor-container">
    
    </div>
    
    :::
    
    <div class="code-output-container">
    
    <div class="output-block">
    
    *chevron\_right*
    
    ``` output-pre
    ```
    
    </div>
    
    <div class="ide-link-div">
    
    *filter\_none*
    
    ``` 
    ```
    
    </div>
    
    </div>
    
    Output:
    
        This is a Vehicle
        This is a Vehicle

5.  **Hybrid (Virtual) Inheritance** : Hybrid Inheritance is implemented by combining more than one
    type of inheritance. For example: Combining Hierarchical inheritance and Multiple Inheritance.  
    Below image shows the combination of hierarchical and multiple inheritance:
    ![](https://media.geeksforgeeks.org/wp-content/uploads/Hybrid-Inheritance.png)
    
    <div class="code-block">
    
    <div class="code-gutter">
    
    <div class="editor-buttons-container">
    
    <div class="editor-buttons">
    
    <div class="editor-buttons-div" title="Run and Edit">
    
    *filter\_none* ::: {\#run-and-edit-loader .ring-load}
    
    </div>
    
    *edit*  
    *close*
    
    <div id="run-code-loader" class="ring-load">
    
    </div>
    
    *play\_arrow*
    
    <div id="generate-url-loader" class="ring-load">
    
    </div>
    
    *link*  
    *brightness\_5*  
    *code*
    
    </div>
    
    </div>
    
    </div>
    
    </div>
    
        ```cpp
        // C++ program for Hybrid Inheritance
        
        #include <iostream>
        using namespace std;
        
        // base class
        class
            Vehicle {
        
        public
            :
            Vehicle()
        
            {
        
                cout << "This is a Vehicle"
                     << endl;
            }
        };
        
        //base class
        class
            Fare {
        
        public
            :
            Fare()
        
            {
        
                cout << "Fare of Vehicle\n";
            }
        };
        
        // first sub class
        class
            Car : public Vehicle {
        };
        
        // second sub class
        class
            Bus : public Vehicle,
                  public Fare {
        };
        
        // main function
        int main() {
        
            // creating object of sub class will
        
            // invoke the constructor of base class
        
            Bus obj2;
        
            return 0;
        }
        
        ```
    
    <div class="code-editor-container">
    
    </div>
    
    :::
    
    <div class="code-output-container">
    
    <div class="output-block">
    
    *chevron\_right*
    
    ``` output-pre
    ```
    
    </div>
    
    <div class="ide-link-div">
    
    *filter\_none*
    
    ``` 
    ```
    
    </div>
    
    </div>
    
    Output:
    
        This is a Vehicle
        Fare of Vehicle

This article is contributed by [**Harsh Agarwal**](https://www.facebook.com/harsh.agarwal.16752) .
If you like GeeksforGeeks and would like to contribute, you can also write an article using
[contribute.geeksforgeeks.org](http://www.contribute.geeksforgeeks.org) or mail your article to
contribute@geeksforgeeks.org. See your article appearing on the GeeksforGeeks main page and help
other Geeks.

  
  

<div id="AP_G4GR_6">

::: {\#76621e0b-1fac-4840-ba08-8ec48d007bc6 .\_ap\_apex\_ad render-time=“1583432204438”
section=“76621e0b-1fac-4840-ba08-8ec48d007bc6” section-id="" xpath=“\#AP\_G4GR\_6:eq(0)”
style=“display: block; clear: both; text-align: center; margin: 10px auto;”} :::
{\#ADP\_40792\_728X280\_76621e0b-1fac-4840-ba08-8ec48d007bc6
google-query-id=“CLjD97\_4g-gCFU90wQodVhgC-Q” style=“margin: 0 auto”} :::
{\#google\_ads\_iframe\_/103512698/21930050695\_0\_\_container\_\_ style=“border: 0pt none; display:
inline-block; width: 728px; height: 280px;”}

</div>

::: ::: :::

  

<div id="personalNoteDiv" class="clear hideIt">

<div class="personalNoteHeader clear">

<span class="noteHeaderText">My Personal Notes</span>
<span class="hideNotesDivIcon">*arrow\_drop\_up*</span>

</div>

<div class="collapsableDivPersonalNotes">

<div class="saveNoteDiv">

<span class="processSaveNote"></span>

Save

</div>

</div>

</div>

<div class="recommendedPostsDiv">

## Recommended Posts:

  - [Inheritance in Python](https://www.geeksforgeeks.org/inheritance-in-python/)
  - [Multiple Inheritance in C++](https://www.geeksforgeeks.org/multiple-inheritance-in-c/)
  - [Inheritance in Java](https://www.geeksforgeeks.org/inheritance-in-java/)
  - [Inheritance and friendship](https://www.geeksforgeeks.org/g-fact-34/)
  - [Inheritance and constructors in Java](https://www.geeksforgeeks.org/g-fact-67/)
  - [Difference between Inheritance and
    Polymorphism](https://www.geeksforgeeks.org/difference-between-inheritance-and-polymorphism/)
  - [Does overloading work with
    Inheritance?](https://www.geeksforgeeks.org/does-overloading-work-with-inheritance/)
  - [Java and Multiple Inheritance](https://www.geeksforgeeks.org/java-and-multiple-inheritance/)
  - [Difference between Single and Multiple Inheritance in
    C++](https://www.geeksforgeeks.org/difference-between-single-and-multiple-inheritance-in-c/)
  - [OOP in Python | Set 3 (Inheritance, examples of object, issubclass and
    super)](https://www.geeksforgeeks.org/oop-in-python-set-3-inheritance-examples-of-object-issubclass-and-super/)
  - [Sum of non-diagonal parts of a square
    Matrix](https://www.geeksforgeeks.org/sum-of-non-diagonal-parts-of-a-square-matrix/)
  - [Check if X and Y can be made zero by using given operation any number of
    times](https://www.geeksforgeeks.org/check-if-x-and-y-can-be-made-zero-by-using-given-operation-any-number-of-times/)
  - [Largest Even and Odd N-digit numbers in Hexadecimal Number
    System](https://www.geeksforgeeks.org/largest-even-and-odd-n-digit-numbers-in-hexadecimal-number-system/)
  - [Visibility Modes in C++ with
    Examples](https://www.geeksforgeeks.org/visibility-modes-in-c-with-examples/)

</div>

<div id="improvedBy">

  
**Improved By :** [vasu\_arora](https://auth.geeksforgeeks.org/user/vasu_arora/)

</div>

  

**Article Tags :**

<div class="practiceButton">

[C++](https://www.geeksforgeeks.org/category/programming-language/cpp/)

</div>

<div class="practiceButton">

[School Programming](https://www.geeksforgeeks.org/category/school-programming/)

</div>

<div class="no-p-tag" style="text-align:left;">

**Practice Tags :**

<div class="practiceButton">

[CPP](https://practice.geeksforgeeks.org/topics/CPP)

</div>

</div>

  

<div id="improveArticle" style="float: right;cursor: pointer;">

</div>

<div class="plugins upvoteArticle">

<div>

*thumb\_up*  
<span class="upvoteText">85</span>

</div>

<div class="plugins" style="text-align:right;">

<div id="markPlugin" data-pid="147294" data-ptitle="Inheritance in C++">

  
  

<div class="lists">

To-do Done

</div>

</div>

<div id="ratePlugin" class="difficultyRating" data-pid="147294" data-ptitle="Inheritance in C++">

<div class="techno dropdown">

<span id="rating_box" class="avg-rating level-2">2.2</span>  
  
<span id="vote_count">Based on **99** vote(s)</span>

<div class="markRating dropdown-content">

</div>

<span class="process"></span>

</div>

</div>

</div>

<div class="plugins userActionButtons">

<div id="feedbackButtonDiv" data-pid="147294" data-ptitle="Inheritance in C++" style="display:inline-block">

Feedback/ Suggest Improvement

Add Notes

Improve Article

</div>

<div id="addNoteButtonDiv" data-pid="147294" data-ptitle="Inheritance in C++" style="display:inline-block">

</div>

<div id="improveArticleButtonDiv" data-pid="147294" data-ptitle="Inheritance in C++" style="display:inline-block">

</div>

</div>

<div class="common-bottom">

Please write to us at contribute@geeksforgeeks.org to report any issue with the above content.

</div>

</div>

:::
