#include <ncurses.h>

#include <iostream>

int main() {
    initscr();                                                  // Initialize the ncurses screen
    noecho();                                                   // Don't echo typed characters
    cbreak();                                                   // Disable line buffering
    keypad(stdscr, TRUE);                                       // Enable special keys (arrows, function keys, etc.)
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);  // Enable mouse events

    // Print instructions
    mvprintw(0, 0, "Click anywhere to place the cursor for character entry. Press 'q' to quit.");
    refresh();

    MEVENT event;  // Structure to store mouse event data
    int ch;

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_MOUSE:  // If a mouse event occurs
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON1_CLICKED) {
                        // Move cursor to the position where mouse clicked
                        move(event.y, event.x);
                        refresh();

                        // Allow character entry
                        char entry = getch();
                        addch(entry);  // Add the character where the cursor is
                        refresh();
                    }
                }
                break;

            default:
                break;
        }
    }

    endwin();  // End ncurses mode
    return 0;
}