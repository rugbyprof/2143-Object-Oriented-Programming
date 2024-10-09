## Program 2A - Ncurses test

#### Due: 10-11-2024 (Friday)

To install **ncurses** on Windows 11 using **Windows Subsystem for Linux (WSL)**, follow these instructions step-by-step. We'll use a small **hello world** example to test that `ncurses` is working properly.

### Steps to Install ncurses on Windows 11 with WSL:

1. **Install WSL on Windows 11**:

   - Open **PowerShell** as Administrator and run:
     ```bash
     wsl --install
     ```
   - This will install WSL and set up **Ubuntu** as the default Linux distribution (if you don't have WSL already installed). You may need to restart your computer after this command.

2. **Launch WSL (Ubuntu)**:

   - Once WSL is installed, you can launch **Ubuntu** either from the Start Menu or by typing `wsl` in PowerShell or the Command Prompt.
   - Update the Ubuntu packages after launching it:
     ```bash
     sudo apt update
     sudo apt upgrade
     ```

3. **Install ncurses**:

   - Now, install the `ncurses` library using `apt`:
     ```bash
     sudo apt install libncurses5-dev libncursesw5-dev
     ```
   - This will install the development libraries for `ncurses`, which are required for compiling and running programs that use `ncurses`.

4. **Create a Simple ncurses "Hello World" Program**:

   - Use a text editor like `nano` to create a small C++ program for testing `ncurses`:

     ```bash
     nano hello_ncurses.cpp
     ```

   - Inside `hello_ncurses.cpp`, write the following code:

     ```cpp
     #include <ncurses.h>

     int main() {
         initscr();            // Start ncurses mode
         printw("Hello, World!"); // Print message on the screen
         refresh();            // Refresh to show the message
         getch();              // Wait for user input
         endwin();             // End ncurses mode
         return 0;
     }
     ```

5. **Compile and Run the ncurses Program**:

   - To compile the program, use `g++` and link it with the `ncurses` library:
     ```bash
     g++ hello_ncurses.cpp -o hello_ncurses -lncurses
     ```
   - Run the compiled program:

     ```bash
     ./hello_ncurses
     ```

   - You should see the text `Hello, World!` displayed in your terminal, and it will wait for you to press any key to exit.

### Explanation:

- **`initscr()`**: Initializes the ncurses mode.
- **`printw()`**: Prints "Hello, World!" on the screen.
- **`refresh()`**: Refreshes the screen to show the message.
- **`getch()`**: Waits for the user to press a key.
- **`endwin()`**: Ends the ncurses mode and restores normal terminal behavior.

## Deliverables

- Create a folder called `P02A` and add a `README.md` to it.
- Place a screenshot of your ncurses code running inside the README file.
- Remember what [readmees](../../Resources/02-Readmees/README.md) should look like.
- Upload this folder to your `Assignments` folder in Github.
