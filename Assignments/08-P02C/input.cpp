#include <ncurses.h>

#include <fstream>
#include <iostream>
#include <string>

void log(const char *key, const char *val, bool append = true) {
    std::ofstream fout;
    if (append)
        fout.open("log.txt", std::ios::app);
    else
        fout.open("log.txt");
    fout << key << ": " << val << std::endl;

    fout.close();
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    std::string input;
    int mx, my;

    mvprintw(0, 0, "Click anywhere to place the cursor for character entry. Press 'q' to quit.");
    refresh();

    MEVENT event;
    int ch;

    while ((ch = getch()) != 'q') {
        log("ch", std::to_string(ch).c_str());
        // Check for mouse events
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED) {
                move(event.y, event.x);
                my = event.y;
                mx = event.x;
                refresh();
            }
        }
        // Check if Enter was pressed
        else if (ch == '\n' || ch == KEY_ENTER) {
            mvprintw(0, 0, "                                                                                      ");
            mvprintw(0, 0, "You entered: %s\n", input.c_str());
            getch();
            refresh();
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            log("backspace", "true");
            log("input before", input.c_str());
            if (input.length() > 0) {
                input.pop_back();
                // delch();
                refresh();
            }
            log("input after", input.c_str());
        }
        // Handle standard characters
        else if (ch >= 32 && ch <= 126) {  // Check if `ch` is a printable ASCII character
            input += ch;
            mvprintw(my, mx, "                    ");
            mvprintw(my, mx, "%s", input.c_str());
            // addch(ch);
            refresh();
        }
    }

    endwin();
    return 0;
}