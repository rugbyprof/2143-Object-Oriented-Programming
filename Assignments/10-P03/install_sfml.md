## Step-by-Step Guide to Installing SFML on WSL

1. Ensure You Have WSL and a Linux Distribution Installed

- First, make sure you have WSL enabled and a Linux distribution (like Ubuntu) installed. To do this, open PowerShell and run:

```bash
wsl --install
```

- Restart your system if needed, and open your Linux distribution from the Start Menu to set it up.

2. Update Your Package List

- Open your Linux terminal (Ubuntu or other WSL distro) and update the package lists to ensure you have the latest versions:

```bash
sudo apt update
sudo apt upgrade
```

3. Install Required Packages

- Install development tools such as g++ and make if they aren’t already installed:

```bash
sudo apt install build-essential
```

4. Install SFML

- Install SFML using the package manager. This will also install all necessary dependencies:

```bash
sudo apt install libsfml-dev
```

5. Verify the Installation

- To verify the installation, you can compile a simple SFML program. Create a file named main.cpp with the following code:

```bash
#include <SFML/Graphics.hpp>

int main() {
sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
sf::CircleShape shape(50);
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

- Compile the code:

```bash
g++ -o sfml_test main.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

6. Run Your Program

- To run graphical applications, you’ll need an X server on Windows, such as VcXsrv or Xming.

- Run your program in the WSL terminal:

```bash
./sfml_test
```

- The SFML window should appear on your screen via the X server.

Summary

1. Enable and set up WSL.
2. Install necessary packages with sudo apt install libsfml-dev.
3. Set the DISPLAY variable and run your SFML application.

This setup allows SFML programs to run on WSL, utilizing an X server to display graphics on your Windows system.
