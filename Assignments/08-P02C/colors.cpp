#include <ncurses.h>

int main() {
    initscr();
    start_color();
    use_default_colors();  // Enable extended colors

    if (COLORS >= 256) {
        init_pair(1, 196, -1);  // Use color 196 (a bright red) with default background
        attron(COLOR_PAIR(1));
        printw("This is a bright red color from the extended 256-color palette.");
        attroff(COLOR_PAIR(1));
    } else {
        printw("256-color mode not supported.");
    }

    refresh();
    getch();
    endwin();
    return 0;
}