#include <ncurses.h>

#include "logger.cpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Grid {
   private:
    int start_y, start_x;
    int cell_width, cell_height;
    int width, height;
    int base_y, base_x;
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

        printValues();
        wrefresh(win);
    }

    void printValues() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int y = ((base_y + cell_height) * i) + 2;
                int x = ((base_x + cell_width) * j) + 3;
                mvwprintw(win, y, x, std::to_string(values[i][j]).c_str());
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
        Logger::log("colClicked", std::to_string(col).c_str());
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
        wrefresh(win);
        printValues();
    }
    WINDOW *getWindow() { return win; }
};

int main() {
    initscr();  // Start ncurses mode
    int rows, cols;

    // Get terminal size
    getmaxyx(stdscr, rows, cols);

    Logger::log("rows", std::to_string(rows).c_str());
    Logger::log("cols", std::to_string(cols).c_str());

    noecho();     // Don't echo input
    cbreak();     // Disable line buffering
    curs_set(0);  // Hide the cursor

    setlocale(LC_ALL, "");  // Enable Unicode support

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    clear();  // clear screen to prevent scrolling
    refresh();

    Grid grid(10, 40);

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
                    if (grid.clicked(event.y, event.x - 1)) {
                        int col = grid.colClicked(event.y, event.x - 1);
                        Logger::log("colclicked", std::to_string(col).c_str());
                        grid.addValue(event.y, event.x - 1, rand() % 6 + 1);  // Mark click location
                    }
                    refresh();
                }
            }
        }
        grid.refreshGrid();
    }

    // Wait for a key press before exiting
    // getch();
    endwin();  // End ncurses mode

    return 0;
}