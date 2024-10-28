#include <ncurses.h>

// 1.	COLOR_BLACK
// 2.	COLOR_RED
// 3.	COLOR_GREEN
// 4.	COLOR_YELLOW
// 5.	COLOR_BLUE
// 6.	COLOR_MAGENTA
// 7.	COLOR_CYAN
// 8.	COLOR_WHITE

int main() {
    initscr();
    start_color();
    use_default_colors();  // Enable extended colors

    // Initialize color pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);

    if (COLORS >= 256) {
        // Use color pair 1 (red text on black background)
        attron(COLOR_PAIR(1));
        printw("This is red text on a black background\n");
        attroff(COLOR_PAIR(1));

        // Use color pair 1 (red text on black background)
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("This is red text on a black background\n");
        attroff(COLOR_PAIR(1) | A_BOLD);

        // Use color pair 2 (green text on black background)
        attron(COLOR_PAIR(2));
        printw("This is green text on a black background\n");
        attroff(COLOR_PAIR(2));

        // Use color pair 2 (green text on black background)
        attron(COLOR_PAIR(2) | A_BOLD);
        printw("This is green text on a black background\n");
        attroff(COLOR_PAIR(2) | A_BOLD);

        // Use color pair 3 (blue text on white background)
        attron(COLOR_PAIR(3));
        printw("This is blue text on a white background\n");
        attroff(COLOR_PAIR(3));

        // Use color pair 3 (blue text on white background)
        attron(COLOR_PAIR(3) | A_BOLD);
        printw("This is blue text on a white background\n");
        attroff(COLOR_PAIR(3) | A_BOLD);
    } else {
        printw("256-color mode not supported.");
    }

    refresh();
    getch();
    endwin();
    return 0;
}