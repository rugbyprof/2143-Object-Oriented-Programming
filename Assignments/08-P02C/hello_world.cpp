#include <ncurses.h>

#include "logger.hpp"
#include <string>
#include <vector>

using namespace std;

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // Hide the cursor
    clear();
    refresh();

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    start_color();


    Logger::setFilePath("log.txt");

    init_pair(1, COLOR_BLACK, COLOR_YELLOW);  // Normal: Black text, white background
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    int rows, cols, size;
    int ch;

    getmaxyx(stdscr, rows, cols);

    string text = "Hello World ";

    size = strlen(text.c_str());

    while (true) {
        mvprintw(rows / 2, (cols / 2) - strlen(text.c_str()), text.c_str());
        ch = getch();

        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == KEY_MOUSE) {
            MEVENT event;
            Logger::log("Mouse pressed", "true");
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    Logger::log("clicked", vector<int>({event.y, event.x}));
                }
            }
        }
        mvprintw(rows / 2, (cols / 2) - strlen(text.c_str()), text.c_str());
        Logger::log("Key pressed", to_string(ch));
        refresh();
    }
    clear();
    endwin();
    return 0;
}