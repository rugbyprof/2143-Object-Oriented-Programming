#pragma once

#include <ncurses.h>

#include "logger.hpp"
#include <ctime>
#include <string>

using namespace std;

class Grid {
   private:
    int start_y, start_x;
    int cell_width, cell_height;
    int width, height;
    int base_y, base_x;
    int border_color = 1;
    int number_color = 2;
    WINDOW *win;
    int values[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    void init() {
        Logger::log("Initializing grid", "true");
        cell_height = 1;
        cell_width  = 3;
        height      = 3 * (cell_height + 1) + 1;
        width       = 3 * (cell_width + 1) + 1;
        win         = newwin(height + 2, width + 2, start_y, start_x);
        base_y      = 1;
        base_x      = 1;

        Logger::log("height", vector<int>({height, width, cell_height, cell_width}));
        drawGrid();
    }

   public:
    Grid(int y = 0, int x = 0) : start_y(y), start_x(x) {
        Logger::log("yx", vector<string>{to_string(y), to_string(x)});
        init();
    }

    void drawGrid() {
        wattron(win, COLOR_PAIR(border_color));  // Turn on color pair 2
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
        wattroff(win, COLOR_PAIR(border_color));
        wattron(win, COLOR_PAIR(number_color));
        printValues();
        wattroff(win, COLOR_PAIR(number_color));
        wrefresh(win);
    }

    void printValues() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int y = ((base_y + cell_height) * i) + 2;
                int x = ((base_x + cell_width) * j) + 3;
                if (values[i][j] > 0) {
                    mvwprintw(win, y, x, to_string(values[i][j]).c_str());
                }
            }
        }
    }

    /**
     * @brief Check if a click event occurred within a window
     * @param click_y (int)     : The y-coordinate of the click event
     * @param click_x (int)     : The x-coordinate of the click event
     * @param win_info (WindowType) : Information about the window
     * @return (bool)           : True if the click event occurred within the window, False otherwise
     */
    bool clicked(int click_y, int click_x) {
        return click_y >= start_y && click_y < start_y + height && click_x >= start_x && click_x < start_x + width;
    }

    /**
     * @brief Get the column number of a click event within a window
     * @param click_y (int)     : The y-coordinate of the click event
     * @param click_x (int)     : The x-coordinate of the click event
     * @param win_info (WindowType) : Information about the window
     * @return (int)            : The column number of the click event
     */
    int colClicked(int click_y, int click_x) {
        int sx     = start_x;
        int ex     = start_x + width;
        int thirds = width / 3;

        if (click_x < sx + thirds)
            return 0;
        else if (click_x < sx + 2 * thirds)
            return 1;
        else
            return 2;
        return 0;
    }

    void addValue(int click_y, int click_x, int value) {
        int col = colClicked(click_y, click_x);
        Logger::log("colClicked", to_string(col).c_str());
        int row          = availableRow(col);
        values[row][col] = value;
        refreshGrid();
    }

    int availableRow(int col) {
        for (int i = 2; i >= 0; i--) {
            if (values[i][col] == 0) {
                return i;
            }
        }
        return -1;
    }

    void refreshGrid() {
        wclear(win);
        drawGrid();
    }
    WINDOW *getWindow() { return win; }
};
