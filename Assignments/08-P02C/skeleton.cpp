#include <ncurses.h>  // Ncurses library

#include "logger.cpp"  // Logger utility
#include <fstream>     // File I/O
#include <iostream>    // Input/Output
#include <map>         // Map data structure
#include <string>      // String data structure
#include <vector>      // Vector data structure

using namespace std;

int main() {
    int height, width;
    int x, y;
    string str;

    initscr();  // Start ncurses mode

    // Get terminal size
    getmaxyx(stdscr, height, width);

    Logger::log("height x width", vector<string>({std::to_string(height), to_string(width)}));

    noecho();     // Don't echo input
    cbreak();     // Disable line buffering
    curs_set(0);  // Hide the cursor

    setlocale(LC_ALL, "");  // Enable Unicode support

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    clear();  // clear screen to prevent scrolling
    refresh();

    printw("This is a basic skeleton for a ncurses program\n");
    refresh();

    while (true) {
        int ch = getch();

        if (ch == 'q')  // Exit on 'q'
            break;
        else if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    y = event.y;
                    x = event.x;
                    Logger::log("You clicked at x,y:", vector<string>({to_string(x), to_string(y)}));
                }
            }
            // Handle backspace key
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            Logger::log("You hit the backspace", "true");
        }
        // Handle standard characters
        else if (ch >= 32 && ch <= 126) {  // Check if `ch` is a printable ASCII character
            str += ch;
            Logger::log("Input string:", str);
            // Handle enter key
        } else if (ch == '\n' || ch == KEY_ENTER) {
            Logger::log("You hit the enter key", "true");
        }
        Logger::printLastLine(stdscr);
        refresh();
    }

    // Wait for a key press before exiting
    // getch();
    endwin();  // End ncurses mode

    return 0;
}