#include <ncurses.h>

#include <map>
#include <string>
#include <utility>

void init_colors() {
    std::map<std::string, int> cnum = {{"BLACK", 0}, {"MAROON", 1},   {"GREEN", 2}, {"OLIVE", 3}, {"NAVY", 4},  {"PURPLE", 5},
                                       {"TEAL", 6},  {"SILVER", 7},   {"GREY", 8},  {"RED", 9},   {"LIME", 10}, {"YELLOW", 11},
                                       {"BLUE", 12}, {"FUCHSIA", 13}, {"AQUA", 14}, {"WHITE", 15}};

    init_color(cnum["BLACK"], 0, 0, 0);
    init_color(cnum["MAROON"], 128 * 4, 0, 0);
    init_color(cnum["GREEN"], 0, 128 * 4, 0);
    init_color(cnum["OLIVE"], 128 * 4, 128 * 4, 0);
    init_color(cnum["NAVY"], 0, 0, 128 * 4);
    init_color(cnum["PURPLE"], 128 * 4, 0, 128 * 4);
    init_color(cnum["TEAL"], 0, 128 * 4, 128 * 4);
    init_color(cnum["SILVER"], 192, 192, 192);
    init_color(cnum["GREY"], 128 * 4, 128 * 4, 128 * 4);
    init_color(cnum["RED"], 255 * 4, 0, 0);
    init_color(cnum["LIME"], 0, 255 * 4, 0);
    init_color(cnum["YELLOW"], 255 * 4, 255 * 4, 0);
    init_color(cnum["BLUE"], 0, 0, 255 * 4);
    init_color(cnum["FUCHSIA"], 255 * 4, 0, 255 * 4);
    init_color(cnum["AQUA"], 0, 255 * 4, 255 * 4);
    init_color(cnum["WHITE"], 255 * 4, 255 * 4, 255 * 4);

    init_pair(cnum["MAROON"], cnum["MAROON"], cnum["BLACK"]);
    init_pair(cnum["GREEN"], cnum["GREEN"], cnum["BLACK"]);
    init_pair(cnum["OLIVE"], cnum["OLIVE"], cnum["BLACK"]);
    init_pair(cnum["NAVY"], cnum["NAVY"], cnum["BLACK"]);
    init_pair(cnum["PURPLE"], cnum["PURPLE"], cnum["BLACK"]);
    init_pair(cnum["TEAL"], cnum["TEAL"], cnum["BLACK"]);
    init_pair(cnum["SILVER"], cnum["SILVER"], cnum["BLACK"]);
    init_pair(cnum["GREY"], cnum["GREY"], cnum["BLACK"]);
    init_pair(cnum["RED"], cnum["RED"], cnum["BLACK"]);
    init_pair(cnum["LIME"], cnum["LIME"], cnum["BLACK"]);
    init_pair(cnum["YELLOW"], cnum["YELLOW"], cnum["BLACK"]);
    init_pair(cnum["BLUE"], cnum["BLUE"], cnum["BLACK"]);
    init_pair(cnum["FUCHSIA"], cnum["FUCHSIA"], cnum["BLACK"]);
    init_pair(cnum["AQUA"], cnum["AQUA"], cnum["BLACK"]);
    init_pair(cnum["WHITE"], cnum["WHITE"], cnum["BLACK"]);
}

int main() {
    initscr();
    start_color();
    use_default_colors();  // Enable extended colors

    init_colors();

    if (COLORS >= 256) {
        for (int i = 1; i < 16; i++) {
            attron(COLOR_PAIR(i));
            printw("This is color %d\n", i);
            attroff(COLOR_PAIR(i));
            attron(COLOR_PAIR(i) | A_BOLD);
            printw("This is color %d\n", i);
            attroff(COLOR_PAIR(i) | A_BOLD);
        }
        refresh();
    } else {
        printw("256-color mode not supported.");
    }

    refresh();
    getch();
    endwin();
    return 0;
}