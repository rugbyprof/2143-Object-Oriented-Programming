2143 OOP - Test 1
==============

Name: __________________________________

#### Instructions

- Use pencil only
- Write your name at the top of all pages turned in.
- Staple pages together at the top left corner.
- Make sure your pages are in order, with questions also in order. 
- Handwriting that is illegible (messy, small, not straight) will lose points.
- Indentation matters. Keep code aligned correctly.
- Failure to comply will result in loss of letter grade.
- All answers will be written on the paper provided, and not directly on the test.

#### Background:
- A polygon is a 2D shape made up of 3 or more sides. 
  
<img src="https://d3vv6lp55qjaqc.cloudfront.net/items/1H3p1Z3s1U1n3o0e262B/polygon.png" width="150">

- Each side can also be thought of as a line with a beginning point (x<sub>1</sub>,y<sub>1</sub>) and an ending point (x<sub>2</sub>,y<sub>2</sub>). 
	- For example, the polygon above has Points: P<sub>0</sub>, P<sub>1</sub>,P<sub>2</sub>,P<sub>3</sub>,P<sub>4</sub>
	- It also has Lines: (P<sub>0</sub>, P<sub>1</sub>),(P<sub>1</sub>, P<sub>2</sub>),(P<sub>2</sub>,P<sub>3</sub>),(P<sub>3</sub>,P<sub>4</sub>),(P<sub>4</sub>,P<sub>0</sub>).
- The length of a line (or distance between two points can be calculated using the following formula:
<img src="https://d3vv6lp55qjaqc.cloudfront.net/items/1p0u211H0n3P3V0c0G26/Image%202018-10-22%20at%208.27.08%20AM.png" width="175">
- Remember that:
	- Square root is `sqrt(some number)`
	- Exponentiation is `pow(2,3)` or 2<sup>3</sup>.
- A bounding box of a polygon can be found by finding the 4 extreme `x,y` values 
<img src="http://www.yaldex.com/games-programming/FILES/08fig40.gif" width="300">

#### General
- You are going to write 3 class definitions
- Each class should have methods to set / get the data members of the class. 
- Each class definition should build on the previous class. 
- Do not implement any methods until asked, definitions only.

#### Question 1: 

What are the 3 Central Principles of OOP?

#### Question 2 - Point Class

- Write a class that represents a point (x,y).
- X and Y are integer values.

#### Question 3 - Line Class

- Write a class that represents a line  (x<sub>1</sub>,y<sub>1</sub>) ,(x<sub>2</sub>,y<sub>2</sub>).
- Your class should have 2 constructors:
	- One that takes 4 values x<sub>1</sub>,y<sub>1</sub>,x<sub>2</sub>,y<sub>2</sub>
	- One that takes 2 values P<sub>1</sub>,P<sub>2</sub>.
- This class can return the length of its line.

#### Question 4 - Polygon Class
- Write a class that represents a polygon.
- Your polygon can have between `3` and `N` sides.
- Your class should have multiple constructors:
	- One that initializes an empty polygon
	- One that accepts an array of points [P<sub>1</sub>,P<sub>2</sub>,...,.P<sub>n</sub>].
	- One that accepts an array of lines.
- This class can return the perimeter of the polygon.
- This class can return the area of a bounding box of the polygon.

#### Question 5 - Implementation
- Implement the perimeter method of the polygon.

#### Question 6 - Bonus
- Implement the bounding box method of the polygon.