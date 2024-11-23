## SFML Cygwin Setup

Here’s a step-by-step guide to setting up SFML with Visual Studio Code (VSCode) on Windows using Cygwin as your build environment.

### Step 1: Install Required Tools

1. Install Cygwin:
   - Download the installer from Cygwin’s official site.
   - During installation, select the following packages:
   - gcc-core: The C compiler.
   - g++: The C++ compiler.
   - make: The build automation tool.
   - gdb: The debugger (optional but recommended).
2. Install SFML:
   - Download the SFML library for GCC from SFML’s official site.
   - Choose the version compatible with GCC on Windows (e.g., GCC MinGW 64-bit or 32-bit).
   - Extract the SFML files to a location, such as C:/SFML.
3. Install Visual Studio Code:
   - Download and install VSCode from VSCode’s official site.
4. Install Extensions in VSCode:
   - Open VSCode and install the following extensions:
   - C/C++ (by Microsoft): For C++ IntelliSense and debugging.
   - Code Runner (optional): For quickly running code snippets.
   - CMake Tools (optional): If you want to use CMake with SFML.

### Step 2: Configure Cygwin in VSCode

1. Add Cygwin to the PATH:
   - Open Windows Environment Variables (search “Edit the system environment variables” in the Start Menu).
   - Add the path to your Cygwin/bin directory (e.g., C:/cygwin64/bin) to the system PATH variable.
2. Test Cygwin in VSCode:
   - Open VSCode and create a new terminal (`Ctrl+``).
   - Set the terminal to use Cygwin:
   - Click the dropdown arrow in the terminal and select Select Default Profile → Cygwin.
   - Run:

g++ --version

Ensure that Cygwin’s GCC is recognized.

### Step 3: Set Up SFML in Your Project

**1. Project Folder Structure:**

Create the following folder structure:

```bash
project/
├── src/ # Your C++ source files
├── include/ # Optional: For header files
├── lib/ # SFML library files
├── build/ # Where compiled files will go
├── SFML/ # SFML extracted files (or link to your SFML directory)
└── main.cpp # Entry point
```

Copy the contents of the lib and include folders from the downloaded SFML package into your project/SFML/ folder.

**2. Write a Simple SFML Program:**

Create a main.cpp file in your src/ folder with this example:

```c++
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
sf::RenderWindow window(sf::VideoMode(800, 600), "SFML with VSCode & Cygwin");
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

### Step 4: Configure Build Tasks in VSCode

**1. Create a tasks.json File:**

In VSCode, press Ctrl+Shift+P → Type “Tasks: Configure Task” → Select “Create tasks.json file from template” → Choose “Others”.
Replace the content of tasks.json with:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build SFML",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17",
        "-Wall",
        "${workspaceFolder}/src/main.cpp",
        "-I${workspaceFolder}/SFML/include",
        "-L${workspaceFolder}/SFML/lib",
        "-lsfml-graphics",
        "-lsfml-window",
        "-lsfml-system",
        "-o",
        "${workspaceFolder}/build/main"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": []
    }
  ]
}
```

**2. Configure the Output Directory:**

The -o flag in the args specifies the output directory and file.

**3. Build the Project:**

- Press Ctrl+Shift+B to run the “Build SFML” task.
- If successful, the main executable will be created in the build/ directory.

### Step 5: Configure Debugging

**1. Create a launch.json File:**

Press Ctrl+Shift+P → Type “Debug: Open launch.json” → Select “C++ (GDB/LLDB)”.
Replace the content of launch.json with:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug SFML",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/main",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": true,
      "MIMode": "gdb",
      "miDebuggerPath": "C:/cygwin64/bin/gdb.exe",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    }
  ]
}
```

**2. Run the Debugger:**

- Press F5 to start debugging.
- Ensure your breakpoint handling and GDB installation work as expected.

### Step 6: Test SFML Program

Run the compiled executable (build/main). If everything is set up correctly, you should see a window with a green circle.

### Common Issues

**1. Missing `.dll` Files:**

Copy the required SFML DLLs (e.g., `sfml-graphics-2.dll`, `sfml-window-2.dll`, `sfml-system-2.dll`) from SFML/bin into your build/ directory or ensure they are in your `PATH`.

**2. Compiler Incompatibility:**

Make sure the SFML library you downloaded matches your GCC version.

**3. Terminal Issues:**

If VSCode’s terminal doesn’t recognize Cygwin tools, ensure the PATH to Cygwin/bin is correctly set in your system.
