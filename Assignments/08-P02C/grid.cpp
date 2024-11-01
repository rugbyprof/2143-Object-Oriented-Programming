#include <ncurses.h>

#include "logger.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void log(const char *key, const char *val, bool append = true) {
    std::ofstream fout;
    if (append)
        fout.open("log.txt", std::ios::app);
    else
        fout.open("log.txt");
    fout << key << ": " << val << std::endl;

    fout.close();
}

/**
 * @brief Information about a Ncurses window
 * @param win (WINDOW *)    : Pointer to the Ncurses window
 * @param start_y (int)     : The starting y-coordinate of the window
 * @param start_x (int)     : The starting x-coordinate of the window
 * @param height (int)      : The height of the window
 * @param width (int)       : The width of the window
 */
struct WindowType {
    WINDOW *win;
    int start_y, start_x;
    int height, width;
    WindowType(WINDOW *win, int start_y, int start_x, int height, int width)
        : win(win), start_y(start_y), start_x(start_x), height(height), width(width) {}
};

/**
 * @brief Check if a click event occurred within a window
 * @param click_y (int)     : The y-coordinate of the click event
 * @param click_x (int)     : The x-coordinate of the click event
 * @param win_info (WindowType) : Information about the window
 * @return (bool)           : True if the click event occurred within the window, False otherwise
 */
bool windowClicked(int click_y, int click_x, const WindowType &win_info) {
    return click_y >= win_info.start_y && click_y < win_info.start_y + win_info.height && click_x >= win_info.start_x &&
           click_x < win_info.start_x + win_info.width;
}

/**
 * @brief Get the column number of a click event within a window
 * @param click_y (int)     : The y-coordinate of the click event
 * @param click_x (int)     : The x-coordinate of the click event
 * @param win_info (WindowType) : Information about the window
 * @return (int)            : The column number of the click event
 */
int colClicked(int click_y, int click_x, const WindowType &win_info) {
    int sx     = win_info.start_x;
    int ex     = win_info.start_x + win_info.width;
    int thirds = win_info.width / 3;

    if (click_x < sx + thirds)
        return 0;
    else if (click_x < sx + 2 * thirds)
        return 1;
    else
        return 2;
    return 0;
}

/**
 * @brief Create a window for a player's matrix
 * @param start_y (int)     : The starting y-coordinate of the window
 * @param start_x (int)     : The starting x-coordinate of the window
 * @return (WINDOW *)       : Pointer to the Ncurses window
 */
WindowType playerMatrix(int start_y, int start_x) {
    int cell_height = 1;
    int cell_width  = 3;
    int height      = 3 * (cell_height + 1) + 1;
    int width       = 3 * (cell_width + 1) + 1;

    int base_x = 1;
    int base_y = 1;

    WINDOW *win = newwin(height + 2, width + 2, start_y, start_x);

    mvwhline(win, ((base_y + cell_height) * 0) + 1, base_x + 1, ACS_HLINE, width - 2);
    mvwhline(win, ((base_y + cell_height) * 1) + 1, base_x + 1, ACS_HLINE, width - 2);
    mvwhline(win, ((base_y + cell_height) * 2) + 1, base_x + 1, ACS_HLINE, width - 2);
    mvwhline(win, ((base_y + cell_height) * 3) + 1, base_x + 1, ACS_HLINE, width - 2);

    mvwvline(win, base_y + 1, ((base_x + cell_width) * 0) + 1, ACS_VLINE, height - 2);
    mvwvline(win, base_y + 1, ((base_x + cell_width) * 1) + 1, ACS_VLINE, height - 2);
    mvwvline(win, base_y + 1, ((base_x + cell_width) * 2) + 1, ACS_VLINE, height - 2);
    mvwvline(win, base_y + 1, ((base_x + cell_width) * 3) + 1, ACS_VLINE, height - 2);

    mvwaddch(win, base_y, base_x, ACS_ULCORNER);
    mvwaddch(win, base_y, base_x + width - 1, ACS_URCORNER);
    mvwaddch(win, base_y + height - 1, base_x, ACS_LLCORNER);
    mvwaddch(win, base_y + height - 1, base_x + width - 1, ACS_LRCORNER);

    mvwaddch(win, ((base_y + cell_height) * 1) + 1, base_x, ACS_LTEE);
    mvwaddch(win, ((base_y + cell_height) * 2) + 1, base_x, ACS_LTEE);
    mvwaddch(win, ((base_y + cell_height) * 1) + 1, base_x + width - 1, ACS_RTEE);
    mvwaddch(win, ((base_y + cell_height) * 2) + 1, base_x + width - 1, ACS_RTEE);

    mvwaddch(win, base_y, ((base_x + cell_width) * 1) + 1, ACS_TTEE);
    mvwaddch(win, base_y, ((base_x + cell_width) * 2) + 1, ACS_TTEE);
    mvwaddch(win, base_y + height - 1, ((base_x + cell_width) * 1) + 1, ACS_BTEE);
    mvwaddch(win, base_y + height - 1, ((base_x + cell_width) * 2) + 1, ACS_BTEE);

    mvwaddch(win, ((base_y + cell_height) * 1) + 1, ((base_x + cell_width) * 1) + 1, ACS_PLUS);  // ACS_PLUS
    mvwaddch(win, ((base_y + cell_height) * 1) + 1, ((base_x + cell_width) * 2) + 1, ACS_PLUS);  // ACS_PLUS
    mvwaddch(win, ((base_y + cell_height) * 2) + 1, ((base_x + cell_width) * 1) + 1, ACS_PLUS);  // ACS_PLUS
    mvwaddch(win, ((base_y + cell_height) * 2) + 1, ((base_x + cell_width) * 2) + 1, ACS_PLUS);  // ACS_PLUS

    wrefresh(win);
    return WindowType(win, start_y, start_x, height, width);
}

int main() {
    initscr();  // Start ncurses mode
    int rows, cols;

    // Get terminal size
    getmaxyx(stdscr, rows, cols);

    log("rows", std::to_string(rows).c_str());
    log("cols", std::to_string(cols).c_str());

    noecho();     // Don't echo input
    cbreak();     // Disable line buffering
    curs_set(0);  // Hide the cursor

    setlocale(LC_ALL, "");  // Enable Unicode support

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    clear();  // clear screen to prevent scrolling
    refresh();

    WindowType win1 = playerMatrix(1, 60);
    WindowType win2 = playerMatrix(1, 40);

    printw("Click anywhere (Press 'q' to quit)");
    refresh();

    while (true) {
        int ch = getch();

        if (ch == 'q')  // Exit on 'q'
            break;
        else if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    if (windowClicked(event.y, event.x, win1)) {
                        int col = colClicked(event.y, event.x - 1, win1);
                        log("colclicked", std::to_string(col).c_str());
                        Logger::printLastLine(stdscr);
                        mvprintw(event.y, event.x, std::to_string(col).c_str());  // Mark click location
                    } else if (windowClicked(event.y, event.x, win2)) {
                        int col = colClicked(event.y, event.x - 1, win2);
                        log("colclicked", std::to_string(col).c_str());
                        Logger::printLastLine(stdscr);
                        mvprintw(event.y, event.x, std::to_string(col).c_str());  // Mark click location
                    }
                    refresh();
                }
            }
        }
        wrefresh(win1.win);
        wrefresh(win2.win);
    }

    // Wait for a key press before exiting
    // getch();
    endwin();  // End ncurses mode

    return 0;
}