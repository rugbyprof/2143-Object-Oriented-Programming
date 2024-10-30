#include <ncurses.h>

int main() {
    initscr();
    start_color();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Ensure the terminal supports 256 colors
    if (COLORS >= 256) {
        int x = 0;
        int y = 0;
        for (int i = 0; i < 256; i++) {
            init_pair(i, 0, i);
            // Print text with bright red on black background
            attron(COLOR_PAIR(i));
            printw("%d %d %d ...\n", y, x, i);
            mvwprintw(stdscr, y, x, "Code %d ...", i);
            attroff(COLOR_PAIR(i));
            y++;
            if (y % rows == 0) {
                x += 15;
                y = 0;
            }
        }
        refresh();
        getch();
    } else {
        printw("256 color mode is not supported on this terminal.");
        getch();
    }

    endwin();
    return 0;
}