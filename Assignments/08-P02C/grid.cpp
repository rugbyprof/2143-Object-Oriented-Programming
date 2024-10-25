#include <ncurses.h>

void draw_grid(WINDOW *win, int start_y, int start_x, int cell_width, int cell_height) {
    // Draw the top line of the grid
    mvwaddch(win, start_y, start_x, ACS_ULCORNER);
    for (int col = 0; col < 3; ++col) {
        mvwhline(win, start_y, start_x + 1 + col * (cell_width + 1), ACS_HLINE, cell_width);
        if (col == 2) {
            mvwaddch(win, start_y, start_x + (col + 1) * (cell_width + 1), ACS_URCORNER);
        } else {
            mvwaddch(win, start_y, start_x + (col + 1) * (cell_width + 1), ACS_TTEE);
        }
    }

    // Draw the grid cells
    for (int row = 0; row < 3; ++row) {
        for (int line = 1; line <= cell_height; ++line) {
            mvwaddch(win, start_y + row * (cell_height + 1) + line, start_x, ACS_VLINE);
            for (int col = 0; col < 3; ++col) {
                mvwhline(win, start_y + row * (cell_height + 1) + line, start_x + 1 + col * (cell_width + 1), ' ', cell_width);
                mvwaddch(win, start_y + row * (cell_height + 1) + line, start_x + (col + 1) * (cell_width + 1), ACS_VLINE);
            }
        }

        // Draw the line at the bottom of each cell row
        if (row == 2)
            break;
        mvwaddch(win, start_y + (row + 1) * (cell_height + 1), start_x, ACS_LTEE);
        for (int col = 0; col < 3; ++col) {
            mvwhline(win, start_y + (row + 1) * (cell_height + 1), start_x + 1 + col * (cell_width + 1), ACS_HLINE, cell_width);
            if (col == 2) {
                mvwaddch(win, start_y + (row + 1) * (cell_height + 1), start_x + (col + 1) * (cell_width + 1), ACS_RTEE);
            } else {
                mvwaddch(win, start_y + (row + 1) * (cell_height + 1), start_x + (col + 1) * (cell_width + 1), ACS_PLUS);
            }
        }
    }

    // Draw the bottom line of the grid
    mvwaddch(win, start_y + 3 * (cell_height + 1), start_x, ACS_LLCORNER);
    for (int col = 0; col < 3; ++col) {
        mvwhline(win, start_y + 3 * (cell_height + 1), start_x + 1 + col * (cell_width + 1), ACS_HLINE, cell_width);
        if (col == 2) {
            mvwaddch(win, start_y + 3 * (cell_height + 1), start_x + (col + 1) * (cell_width + 1), ACS_LRCORNER);
        } else {
            mvwaddch(win, start_y + 3 * (cell_height + 1), start_x + (col + 1) * (cell_width + 1), ACS_BTEE);
        }
    }

    // Refresh the window to display the grid
    wrefresh(win);
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);

    clear();
    refresh();

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int cell_width = 3, cell_height = 1;
    int win_height = 3 * (cell_height + 1) + 1;
    int win_width  = 3 * (cell_width + 1) + 1;

    // Ensure the two windows will fit in the terminal
    if (win_width * 2 + 4 > term_width || win_height + 2 > term_height) {
        endwin();
        printf("Terminal window is too small for two grids side by side.\n");
        return 1;
    }

    // Create two adjacent windows for the grids
    WINDOW *grid_win1 = newwin(win_height + 2, win_width + 2, 2, 2);
    WINDOW *grid_win2 = newwin(win_height + 2, win_width + 2, 2, win_width + 4);

    // Draw borders around both windows
    box(grid_win1, 0, 0);
    box(grid_win2, 0, 0);

    // Draw grids inside each window
    draw_grid(grid_win1, 1, 1, cell_width, cell_height);
    draw_grid(grid_win2, 1, 1, cell_width, cell_height);

    // Add example content in each cell for the first grid
    mvwprintw(grid_win1, 2, 3, "1");
    mvwprintw(grid_win1, 2, 7, "2");
    mvwprintw(grid_win1, 2, 11, "3");

    // Add example content in each cell for the second grid
    mvwprintw(grid_win2, 2, 3, "4");
    mvwprintw(grid_win2, 2, 7, "5");
    mvwprintw(grid_win2, 2, 11, "6");

    // Refresh both windows
    wrefresh(grid_win1);
    wrefresh(grid_win2);

    getch();  // Wait for user input to exit

    // Clean up
    delwin(grid_win1);
    delwin(grid_win2);
    endwin();
    return 0;
}