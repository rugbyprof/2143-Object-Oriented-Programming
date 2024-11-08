#include <ncurses.h>  // Ncurses library

#include "color_class.hpp"
#include "input_class.hpp"
#include "logger_class.hpp"  // Logger utility
#include <fstream>           // File I/O
#include <iostream>          // Input/Output
#include <map>               // Map data structure
#include <string>            // String data structure
#include <vector>            // Vector data structure

using namespace std;

int main() {
    int height, width;
    int x, y;
    string str;
    int color;
    string yx;

    initscr();  // Start ncurses mode

    // Get terminal size
    getmaxyx(stdscr, height, width);

    Logger::log("height x width", vector<string>({std::to_string(height), to_string(width)}));

    noecho();     // Don't echo input
    cbreak();     // Disable line buffering
    curs_set(0);  // Hide the cursor

    setlocale(LC_ALL, "");  // Enable Unicode support

    start_color();  // enable colors in ncurses

    Input input("Enter text: ", 3, 30, height - 1, (width + 30) / 2);

    colorful();  // my custom color class to create many colors

    keypad(stdscr, TRUE);               // enable keypad for special keys
    mousemask(ALL_MOUSE_EVENTS, NULL);  // enable mouse events

    clear();    // clear screen to prevent scrolling
    refresh();  // refresh / redraw screen

    color = rand() % 32 + 1;
    attron(COLOR_PAIR(color));  // set color pair 1
    printw("This is a basic skeleton for a ncurses program\n");
    refresh();
    attroff(COLOR_PAIR(color));  // unset color pair 1

    while (true) {
        int ch = getch();

        input.printBorder();
        input.printInput(height - 1, (width - 30) / 2 + 15);
        input.captureInput();

        if (ch == 'q')  // Exit on 'q'
            break;
        else if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    y = event.y;
                    x = event.x;
                    Logger::log("You clicked at x,y:", vector<string>({to_string(x), to_string(y)}));
                    Logger::log("Mouse clicked", vector<int>({event.x, event.y}));
                    yx = to_string(y) + "," + to_string(x);

                    mvprintw(y, x, yx.c_str());
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
        Colorly::randColor();
        Colorly::colorOn();
        Logger::printLastLine(stdscr);
        Colorly::colorOff();
        refresh();
    }

    // Wait for a key press before exiting
    // getch();
    endwin();  // End ncurses mode

    return 0;
}