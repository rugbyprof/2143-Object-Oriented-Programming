 How To Document and Organize Your C++ Code
 ==========================================
 
 ### On This Page
 
 *   [1. Introduction](#ovw)
 *   [2. Naming Conventions](#naming)
 *   [3. Comments](#comment)
     *   [3.1. Block Comments](#blockcomment)
     *   [3.2. File Comment Block](#filecomment)
     *   [3.3. Function Comment Block](#functioncomment)
     *   [3.4. Example Program Documentation](#docexample)
 *   [4. Curly Braces](#curlybrace)
 *   [5. Whitespace](#whitespace)
 *   [6. Constants](#constants)
 *   [7. No global variables](#globalvars)
 
 * * *
 
### Introduction
 ----------------
 
 Programming style is about how you organize and document your code. Style is more than a matter of aesthetic interest. A program written following a consistent style is easier to read, easier to correct and easier to maintain.
 
 A program may be written only once, but is read many times:
 
 *   During debugging
 *   When adding to the program
 *   When updating the program
 *   When trying to understand the program
 
 Anything that makes a program more readable and understandable saves lots of time, even in the short run.
 
 Most programmers agree that coding standards are important. The problem is that there is no single standard for C++. As a professional programmer, you must be prepared to adapt your style to the standards of your company or project.
 
 This course follows often-used industry coding standards. Some portion of the grade for most programming assignments is based on your coding style and how well it conforms to this document.
 
 

 ### 2. Naming Conventions
 
 #### 2.1. Use Meaningful Names
 
 Choose names that suggest their purpose. Good names help you understand the problem you are solving. 

 #### 2.2. Variable Names
 
 There are two commonly-used styles you may use. However, you must be consistent and only use one of them in a program. The instructor's preference is the first style.
 
 1.  Start with a lower-case letter and use uppercase letters as separators. Do not use underbars ( `'_'`).
   
     ```cpp
     int myVar
     ```
     
 2.  Use all lower case letters and use underbars ( `'_'`) as separators.
     
     ```cpp
     int my_var
     ```
     
 
 #### 2.3. Constant Names
 
 Use all capital letters and use underbars ( `'_'`) as separators.
 
 ```cpp
 const int MY_CONST = 1;
 ```
 
 #### 2.4. Function Names
 
 There are two commonly-used styles you may use. However, you must be consistent and only use one of them in a program. The instructor's preference is the first style.
 
 1.  Start with a lower-case letter and use uppercase letters as separators. Do not use underbars ( `'_'`).
   
     ```cpp
     int myFunction()
     ```

 2.  Use all lower case letters and use underbars ( `'_'`) as separators.
     
     ```cpp
     int my_function()
     ```
 
 #### 2.5. Class Names
 
 Start with an upper-case letter and use uppercase letters as separators. Do not use underbars ( `'_'`).
 
 ```cpp
 class MyClassName
 ```
 
 ### 3. Comments
 
 Comments are explanatory notes for the humans reading a program. With good name choices, comments can be minimal in a program. The only required comments are block comments at the beginning of each file and before each function declaration. Block comments are described in the next section.
 
 One other time to add comments, other than block comments, is when your code is unusual or obscure. When something is important and not obvious, it merits a comment.
 
 #### 3.1. Block Comments
 
 [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html) is a tool that examines the declarations and documentation comments of your code to produce a set of HTML pages. Another tool is [Ccdoc](http://ccdoc.sourceforge.net/). The pages produced by these tools describe your code to other programmers. For an example of the documentation produced, see the [Introduction](http://ccdoc.sourceforge.net/htdocs/introduction/introduction.htm) to CcDoc.
 
 The documentation comments are derived from block comments, which you create as follows:
 
 *   Indent the first line to align with the code below the comment.
 *   Start the comment with the begin-comment symbol ( `/**`) followed by a return.
 *   Add a description of the purpose of the class or function.
 *   Insert a blank comment line between the description and the list of tags, as shown.
 *   Insert additional blank lines to create various tags.
 *   The last line begins with the end-comment symbol ( `*/`) indented so the asterisks line up and followed by a return. Note that the end-comment symbol contains only a single asterisk.
  
```cpp
     /**
     *  Course: CMPS 2143 - OOP
     *
     *  Purpose: Calculate the total of 6 checks
     * 
     *  @author Ada Lovelace
     *  @version 1.1 01/03/17 
     */
```

 *   For more information on the tags, see the CcDoc [Directives](http://ccdoc.sourceforge.net/htdocs/users_guide/users_guide.htm#directives).
 
 #### 3.2. File Comment Block
 
 Every source file must have a comment block at the top containing the course number, assignment number, name of the file and purpose of the file. One or two lines is usually sufficient to explain the purpose. In addition, you must add the author tag containing your name and the version tag containing the date the assignment is due. For example:

 ```cpp
     /**
     *  Course: CMPS 3013 - Algorithms
     *  Assignment: P02
     *  Purpose: Calculate the total of 6 checks
     * 
     *  @author Ada Lovelace
     *  @version 1.1 01/03/17 
     */
 ```

 The following tags always must be used:
 
 *   [@author](http://ccdoc.sourceforge.net/htdocs/users_guide/users_guide.htm#at_author)
 *   [@version](http://ccdoc.sourceforge.net/htdocs/users_guide/users_guide.htm#at_version)
 
 #### 3.3. Function Comment Block
 
 Every function must have a comment block before the function prototype declaration. For example:
 
```cpp
 /**
  *  Encodes a single digit of a POSTNET "A" bar code.
  *
  *  @param {int} digit the single digit to encode.
  *  @return {string} a bar code of the digit using "|" as the long bar and "," as the half bar.
  */


 string encode(int digit);
```
 The first line is a description of how to use the function.
 
 Where appropriate, the following tags must be used:
 
 *   [@param](http://ccdoc.sourceforge.net/htdocs/users_guide/users_guide.htm#at_param)
 *   [@return](http://ccdoc.sourceforge.net/htdocs/users_guide/users_guide.htm#at_returns)
 
 
 
 #### 3.4. Example Program Documentation
 
 The following short program shows a brief example of properly-documented source code.

 ```cpp
/**
*  Course: CMPS 3013 - Algorithms
*  Assignment: P02
*  Purpose: Calculate the total of 6 checks
* 
*  @author Ada Lovelace
*  @version 1.1 01/03/17 
*/


 #include <iostream>
 
 #include <cmath>
 using namespace std;
 
 const double PI = 3.14159;
 
/**
 *   Returns the area of a circle with the specified radius.
 *
 *   @param {double} radius : The radius of the circle.
 *   @return {double} : The area of the circle.
 */
 double area(double radius);
 
/**
 *  Returns the volume of a sphere with the specified radius.
 *
 *  @param {double} radius : The radius of the circle.
 *  @return {double} The volume of the sphere.
 */
 double volume(double radius);
 
 // Controls operation of the program.
 int main(void) {
     double radius_of_both, area_of_circle, volume_of_sphere;
 
     cout << "Enter a radius to use for both a circle\\n"
             << "and a sphere (in inches): ";
     cin >> radius_of_both;
 
     area_of_circle = area(radius_of_both);
     volume_of_sphere = volume(radius_of_both);
 
     cout << "Radius = " << radius_of_both << " inches\\n"
             << "Area of circle = " << area_of_circle
             << " square inches\\n"
             << "Volume of sphere = " << volume_of_sphere
             << " cubic inches\\n";
 
     return 0;
 }
 
 // Returns the area of a circle with the specified radius.
 double area(double radius) {
     return (PI * pow(radius, 2));
 }
 
 // Returns the volume of a sphere with the specified radius.
 double volume(double radius) {
     return ((4.0 / 3.0) * PI * pow(radius, 3));
 }
 
```
 
 ### 4. Curly Braces
 
 A fervent issue of great debate in programming circles is placement of curly braces. Either of the following two styles is acceptable in this course:
 
 1.  Place the initial brace on the same line as the keyword and the trailing brace inline on its own line with the keyword:
     ```cpp
     if (condition) {
         ...
     }
     
     while (condition) {
         ...
     }
     ```
 2.  Place brace under and inline with keywords:
     
     ```cpp
     if (condition)
     {
         ...
     }
     
     while (condition)
     {
         ...
     }
     ```
 
 The first style is traditional for Unix and C programmers and is the personal preference of the instructor and [Bjarne Stroustrup](http://www.stroustrup.com/bs_faq2.html#layout-style).
 
 #### 4.1. When Braces are Needed
 
 All `if`, `while` and `do` statements must either have braces or be on a single line. This helps to make sure someone adding a line of code does not forget to add braces.
 
 
 
 ### 5. Whitespace
 
 Always layout your source code so that elements that are part of a group go together.
 
 
 #### 5.1. Line Length
 
 Limit your line lenght to about 80 characters since long lines make it difficult to read your program code, especially on smaller screens.
 
 #### 5.2. Spacing Around Operators
 
 Always put spaces before and after binary operators, including `<<` and `>>`. This improves the readability of expressions. For example:
 
 ```cpp
 cin >> a;
 double c = -a * b + 42 - d / 100;
 cout << c << endl;
 ```

 #### 5.3. Indentation
 
 Always indent within curly braces. Use 3 or 4 spaces for each indentation level, but be consistent. For example:
 
 ```cpp
 int func() {
     int dragons = 0;
     cout << "Enter the number of dragons: "
     cin >> dragons;
     while (dragons > 0) {
         Dragon d = getDragon();
         if (d.isFriendly()) {
             rideDragon();
         }
         dragons = dragons - 1;
     }
     return 42;
 }
 ```

 #### 5.4. `if-else-if-else` Formatting
 
 Always line up `if` statements with their associated `else` statement. Beyond that, there are two common styles that you may use:
 
 1.  Place the initial brace on the same line as the keyword and the trailing brace inline on the same line as the next statement. For example:
     ```cpp
     if (condition) {               // Comment
         ...
     } else if (condition) {        // Comment
         ...
     } else {                       // Comment
         ...
     }
     ```
 2.  Place brace under and inline with keywords. For example:
     
     ```cpp
     if (condition)                 // Comment
     {
         ...
     }
     else if (condition)            // Comment
     {
         ...
     }
     else                           // Comment
     {
         ...
     }
     ```
 
 
 
 ### 6. Constants
 
 In C++, you declare constants, which are variables that cannot change, using the keyword `const`. You may use local constants within functions, member constants declared in a class, or global constants declared outside of any class or function.
 
 ```cpp
 const int MY_CONSTANT = 10;
 ```
 
 Because of their special meaning, write constants in all upper case and use underbars ( `'_'`) as separators.
 
 
 ### 7. No Global Variables
 
 A global variable is declared outside of any function and can be accessed by any function in a program. For example, in the following code `myGlobal` is a global variable.
 
 ```cpp
 #include <iostream>
 using namespace std;
 
 double myGlobal = 0;
 
 int main(void) {
     // main function code
     myGlobal = 1;
 }
 
 void anotherFunc() {
     myGlobal = 2;
 }
 // other functions
 ```

 There is rarely a need to use global variables. Moreover, global variables make a program harder to understand and to maintain. Thus, for this course, do NOT use global variables.
 
<sup>Source: http://www.edparrish.net/common/cppdoc.html </sup>