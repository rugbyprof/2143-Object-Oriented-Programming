#include <ncurses.h>

#include "colors.hpp"
#include "logger.hpp"
#include <iostream>
#include <string>

class Input {
    std::string input;
    std::string prompt;
    int box_height;
    int box_width;
    int start_y;
    int start_x;
    WINDOW* input_win;
    int box_color;
    int text_color;

   public:
    Input() {
        input      = "";
        prompt     = "";
        box_height = 3;
        box_width  = 60;
        start_y    = 5;
        start_x    = 10;
        input_win  = newwin(box_height, box_width, start_y, start_x);
        box_color  = 1;
        text_color = 3;
    }
    Input(std::string prm, int h, int w, int y, int x) {
        input      = "";
        prompt     = prm;
        box_height = h;
        box_width  = w;
        start_y    = y;
        start_x    = x;
        input_win  = newwin(box_height, box_width, start_y, start_x);
        box_color  = 1;
        text_color = 3;
    }
    void addChar(char ch) { input += ch; }
    void removeChar() {
        if (input.length() > 0) {
            input.pop_back();
        }
    }
    void setBoxColor(int c) { box_color = c; }
    void setTextColor(int c) { text_color = c; }
    std::string getInput() { return input; }
    std::string setInput(std::string str) { input = str; }
    std::string resetInput() { input = ""; }
    void printInput(int y, int x) { mvprintw(y, x, "%s", input.c_str()); }
    void clearLine(int y, int x, int width) { mvprintw(y, x, "%-*s", width, " "); }
    void printBorder() {
        box(input_win, 0, 0);                        // Draw a border around the input box
        mvwprintw(input_win, 1, 1, prompt.c_str());  // Label inside the box
        wrefresh(input_win);
    }
    void clearWindow() {
        // Clear the input box and move on to the main loop
        werase(input_win);                                           // Erase content from input window
        wborder(input_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove the border
        wrefresh(input_win);                                         // Refresh to show cleared content
        delwin(input_win);                                           // Delete the input window
        wclear(input_win);
    }
    void captureInput() {
        std::string name;
        int ch;
        while ((ch = wgetch(input_win)) != '\n') {   // '\n' represents the Enter key
            if (ch == KEY_BACKSPACE || ch == 127) {  // Handle backspace
                if (!name.empty()) {
                    name.pop_back();
                    // Clear last character and refresh the input line
                    mvwprintw(input_win, 1, 7, "%s ", name.c_str());
                }
            } else if (ch >= 32 && ch <= 126 && name.size() < box_width - 8) {
                // Only add if it's a printable character and within box limit
                name += static_cast<char>(ch);
                mvwprintw(input_win, 1, 7, "%s", name.c_str());
            }
            wrefresh(input_win);  // Refresh the input box to show updates
        }
    }
};

// Step 1: Input text box for name entry

// // Display the welcome message on the main screen
// clear();
// mvprintw(8, 5, "Welcome, %s! Press 'q' to quit.", name.c_str());
// refresh();

// // Main loop for program (could capture other input here)
// while ((ch = getch()) != 'q') {
//     // Placeholder for additional actions
// }

// endwin();
// return 0;
// }