#include <ncurses.h>

#include <iostream>
#include <string>

int main() {
    initscr();                                                  // Initialize the ncurses screen
    noecho();                                                   // Don't echo typed characters
    cbreak();                                                   // Disable line buffering
    keypad(stdscr, TRUE);                                       // Enable special keys (arrows, function keys, etc.)
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);  // Enable mouse events

    std::string input;

    // Print instructions
    mvprintw(0, 0, "Click anywhere to place the cursor for character entry. Press 'q' to quit.");
    refresh();

    MEVENT event;  // Structure to store mouse event data
    int ch;

    while ((ch = getch()) != 'q') {
        if (getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED) {
                // Move cursor to the position where mouse clicked
                move(event.y, event.x);
                refresh();
            }
        }
        // Check if Enter was pressed
        if (ch == '\n' || ch == KEY_ENTER) {
            printw("\nYou entered: %s\n", input.c_str());
            getch();
            refresh();
            break;  // Exit the loop on Enter
        } else {
            // Add typed character to input and display
            input += ch;
            addch(ch);
        }
    }

    endwin();  // End ncurses mode
    return 0;
}