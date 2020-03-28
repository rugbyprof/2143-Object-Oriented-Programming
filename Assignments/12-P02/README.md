## Program 2 - Installing SFML Graphics Lib
#### Due: 03-31-2020 (Tuesday @ 12:30 p.m.)

### Overview

Yes, we are trying this again! OOP console apps is not doing us any good. We need to go up to the next level. There are some graphics libs for c and c++ but they are so outdated I hate to use them. [SFML](https://www.sfml-dev.org/) is well maintained and cross platform. It also has nice [tutorials](https://www.sfml-dev.org/tutorials/2.5/)/

You are tasked with going to the [SFML](https://www.sfml-dev.org/) site and implement the introductory tutorial for your platform. The tutorial will involve downloading and installing SFML and then getting the "hello world" version of a graphics library to run which in this case looks like:

<img src="https://www.sfml-dev.org/tutorials/2.5/images/start-cb-app.png">

If you want to try using VSCode as your compiler (as long as you got MingGW installed from earlier this semester) you can try the following commands from your terminal. Meaning if you can use `g++` from a command line to compile your programs, then this should work.

Example: 
- We want to compile `main.cpp`
- We will create a file called `runme` that we can run like: `./runme` to run our graphics code.
  
```sh
    g++ -std=c++11 -c main.cpp -I"./sfml/include/"
```
This command will create a file called `main.o` which is our object/executable file. BUT we need to link it with the sfml libraries. The `-L` tells `g++` that we need to link the following libraries with our "object" file (`main.o`).

```sh
    g++ main.o -o runme -L"./sfml/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
```