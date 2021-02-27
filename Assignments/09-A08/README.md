## Assignment 8 - CopyConstructor
#### Due: TBD

### Overview 

Using the code from [here](code.cpp) re-write the `RgbColor` class so that it stores 
many colors and call it `ColorPallette` You can use an array or a vector to hold all of your rgb colors.

The question is, how would you redesign the `RgbColor` into the `ColorPallette`  class so that it holds many colors?
Does `ColorPallette` inherit from `RgbColor`? Do you compose `ColorPallette` with many instances of `RgbColor`?

I could turn this into a big program, but I won't. I wanted this to be a homework to which you alter the `RgbColor` class to hold many colors, and store them in a dynamically allocated structure. Why? So we can apply the [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C++_programming)) to this new class. 

The rule of three (also known as the Law of The Big Three or The Big Three) is a rule of thumb in C++ (prior to C++11) that claims that if a class defines any of the following then it should probably explicitly define all three:[1]

destructor
copy constructor
copy assignment operator



### Deliverables

- Create a folder called `A08` in your `Assignments` folder. 
- Add a `README.md` file in your `A08` folder.
- Don't forget your banner (cover page).

```
A08
2143
LASTNAME
```
- If your banner is wrong - you lose a letter grade. Its VERY confusing if you don't include the correct banner.
