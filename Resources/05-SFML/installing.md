## Installing SFML On Windows

## Short way

**MSYS2:**

- Install MSYS2
- Provides an easier way to install and manage MinGW and SFML with package managers like pacman.
- Install GCC then SFML using:

```
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-x86_64-sfml
```

## Long Way

Here’s a clear, somewhat “standard” approach that works reliably doing everything individually:

### 1. Install MinGW

1. Download MinGW-w64 from MinGW-w64 SourceForge.
2. Choose the latest release with a posix thread model and seh exception handling for compatibility with SFML.
3. Install MinGW-w64 to a folder (e.g., C:\mingw-w64).
4. Add C:\mingw-w64\bin to your system’s PATH variable.

Test the installation:

```bash
g++ --version
```

Ensure it returns the version of MinGW you just installed.

### 2. Download and Extract SFML

1. Go to the SFML download page.
2. Download the version compatible with your MinGW-w64 installation (e.g., GCC 11.2.0 MinGW (64-bit)).
3. Extract SFML to a folder (e.g., C:\SFML).

### 3. Set Up VSCode

1. Install the following extensions in VSCode:
   - C/C++ (by Microsoft): For IntelliSense and debugging.
   - Code Runner (optional): To easily run your projects.
2. Create a new folder for your project (e.g., sfml-test) and open it in VSCode.
3. Create the following files in your project folder:
   - main.cpp: Your SFML program.
   - .vscode/tasks.json: For build tasks.
   - .vscode/launch.json: For debugging.
   - .vscode/c_cpp_properties.json: For IntelliSense.

### 4. Configure tasks.json

Tell VSCode how to compile SFML programs using MinGW:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build SFML Project",
      "type": "shell",
      "command": "g++",
      "args": [
        "-IC:/SFML/include", // Path to SFML headers
        "-LC:/SFML/lib", // Path to SFML libraries
        "main.cpp", // Source file
        "-o",
        "main.exe", // Output executable
        "-lsfml-graphics", // SFML graphics library
        "-lsfml-window", // SFML window library
        "-lsfml-system" // SFML system library
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"],
      "detail": "Compile SFML project"
    }
  ]
}
```

### 5. Configure launch.json

Set up debugging for your SFML program:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Run SFML Project",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/main.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": true,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "miDebuggerPath": "C:/mingw-w64/bin/gdb.exe"
    }
  ]
}
```

### 6. Configure c_cpp_properties.json

Enable IntelliSense for SFML headers:

```json
{
  "configurations": [
    {
      "name": "MinGW",
      "includePath": [
        "${workspaceFolder}/**",
        "C:/SFML/include" // Path to SFML headers
      ],
      "defines": [],
      "compilerPath": "C:/mingw-w64/bin/g++.exe",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "intelliSenseMode": "windows-gcc-x64"
    }
  ],
  "version": 4
}
```

### 7. Write a Simple Test Program

Create a basic main.cpp to test SFML:

```cpp
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
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

### 8. Build and Run

1. Build the program:
   - Press Ctrl+Shift+B or select Terminal → Run Build Task.
2. Run the program:
   - Press F5 or click Run and Debug.

### 9. Troubleshooting

• Missing DLLs: Copy the required SFML DLLs (sfml-graphics-2.dll, sfml-window-2.dll, sfml-system-2.dll) from C:\SFML\bin to your project folder.
• Incompatible Compiler: Ensure your SFML version matches your MinGW version (check g++ --version).

## Alternative Tools

If the manual setup is too tedious, consider using:

**CMake:**

- CMake simplifies SFML project configuration and can be integrated with VSCode for better portability and automation.

🚀
