## SFML Install - Step by Step instructions
#### Due: No Due Date

Written By: Tom Bauer

### Instructions 

- Go to https://www.sfml-dev.org/download/sfml/2.5.0/ to download the files.
- Go to the location of your downloaded file.
- Right click and extract the file (remember where you unzipped it).
- Find the folder `SFML-2.5.0` (which will be inside the originally extracted folder) 
- Move it directly to the `C:` drive. 
- Open Visual Studio
  - create a new program 
  - select empty project and give it a name (e.g. sfml_test)
- After your project is open in visual studio, right click on the project and go down to `add` and select `new item`. 
- Add a `.cpp` and name the file `main.cpp`
vRight click again on project (in project explorer) and select `Properties`.
- Make sure that under the Configurations drop down that you have `All Configurations`.
- On the left-hand side box, go down to `C/C++` and expand that menu. Select `General` in the sub-menu.
- Click on `General` and then in the right side click `Additional Include Directories`.
- Click the drop-down arrow to the right and select `edit`.
- Click in the empty area to add the name of the directory that it is in and copy this:
```txt
  C:\SFML-2.5.0\include         
```
  - and paste it in that spot.
  - Click on OK
- Now go back to the left-hand side box and go down to `Linker` and expand that. 
- Click on ìGeneralî and then in the right side click ìAdditional Library Directoriesî
- Click the drop-down arrow to the right and select ìeditî
- Copy and paste this into that entry:     
```
C:\SFML-2.5.0\lib
```
- Click on OK 

- Now go under ìLinkerî again and this time go to `Input`
- On the right side click `Additional Dependencies`
- Click the drop-down arrow to the right and select `edit`
- In the box that opens up, copy and paste the following:

```
sfml-main.lib
sfml-graphics.lib
sfml-window.lib
sfml-system.lib
sfml-audio.lib
sfml-network.lib
```

- Now go to the SFML folder in the C: drive and go into the bin folder
- Select All and copy and paste those into the folder where your main.cpp for this project is located

- Now for the test program, copy and paste the following:

```cpp
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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

- Build and Run the program and it should display a window with a black background and a green circle

