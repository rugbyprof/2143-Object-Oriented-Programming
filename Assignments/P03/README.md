## Program 3 - SFML Tutorial Starter
#### Due: October 1<sup>st</sup> by Classtime

## Overview

Using the SFML libraries in this folder, here are the steps you need to go through to get the following simple program to work.  BTW this is the usual approach for installing a large number of API’s that you might be interested in out there so pay close attention to the process.

```cpp
#include <SFML/Graphics.hpp>
int main() {
 sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
 sf::CircleShape shape(100.f);
 shape.setFillColor(sf::Color::Green);
 while (window.isOpen()) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }
  window.clear();
  window.draw(shape);
  window.display();
}
  return 0;
}
```

- Fire up visual studio 15 or 17 and use the above as your main program.
- IF your using Visual Studio 2017 - use the zip with `17` in it. Otherwise, use the other one (for older versions of Visual Studio).
- Copy the appropriate `zip` file to your `C:` drive. I will be using the SFML17 version for the below discussion. 
- Change the solution platform (at the top of vs) from x86 to x64.  Be sure and do this before you do the following steps.

<img src="https://d3vv6lp55qjaqc.cloudfront.net/items/0M2N3e0Y11361X2g3z0F/%5Bd68e935ee0b434f208e9fe13789158b6%5D_Image+2018-09-24+at+10.02.01+AM.png" width="500">

- Go go `Project->Properties->Configuration Properties->VC++ Directories->Include Directories` and add `C:\SFML17-2.4.2\include`.  
- Go go `Project->Properties->Configuration Properties->VC++ Directories->Library Directories` and add `C:\SFML17-2.4.2\lib`.

<img src="https://d3vv6lp55qjaqc.cloudfront.net/items/352P0O0v1V023U3G0K0U/%5B9c23c58f631f34b8df97afecb198886c%5D_Image+2018-09-24+at+9.59.27+AM.png" width="500">

> Note that this tells visual where to look for your include files ( ie. `#include <SFML/Graphics.hpp>`) and your lib files ( ie. `sfml-graphics-d.lib; sfml-window-d.lib; sfml-system-d.lib; sfml-audio-d.lib`) , these are the debug versions denoted by the -d at the end.

- Copy the DLL’s from `C:\SFML17-2.4.2\bin` to your project directory that has your `main.cpp` file.  (This is just one of the places they can be placed. See [here](https://msdn.microsoft.com/en-us/library/7d83bc18.aspx) for other options).
- Go to `Project->Properties->Configuration Properties->Linker->Input` and add `sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib;` to the list.  This tells the linker which libs to actually look for in the `C:\SFML17-2.4.2\lib` directory that you specified above.

<img src="https://d3vv6lp55qjaqc.cloudfront.net/items/1U1t0f1K3Q3y2c3C2L3M/%5B7223c17edf6cdcaa7a1507a18589a768%5D_Image+2018-09-24+at+10.12.38+AM.png" width="500">

- Now compile and run the program. If you don’t get external linking errors etc. and it runs, you are amazing. If not double check everything above and try again.  You should get a small window with a large green dot in the middle.

### Requirements

- Add a proper comment block to your `main.cpp`.
    - I changed the comments requirements (added github repo line) so [go look](../Resources/comments.md).
- Screen shot your green dot output with enough of your desktop to show me its running on your machine.
- Turn in a printed copy of your commented `main.cpp` and your screenshot at the beginning of class.