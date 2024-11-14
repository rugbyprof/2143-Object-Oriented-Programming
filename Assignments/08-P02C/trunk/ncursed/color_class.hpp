#pragma once

#include <ncurses.h>

#include <map>
#include <string>
#include <utility>

/**
 * @brief Function to create many colors
 */
void colorful() {
    std::map<std::string, int> cnum = {{"BLACK", 0}, {"MAROON", 1},   {"GREEN", 2}, {"OLIVE", 3}, {"NAVY", 4},  {"PURPLE", 5},
                                       {"TEAL", 6},  {"SILVER", 7},   {"GREY", 8},  {"RED", 9},   {"LIME", 10}, {"YELLOW", 11},
                                       {"BLUE", 12}, {"FUCHSIA", 13}, {"AQUA", 14}, {"WHITE", 15}

    };

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

    init_pair(0, cnum["BLACK"], cnum["BLACK"]);
    init_pair(1, cnum["MAROON"], cnum["BLACK"]);
    init_pair(2, cnum["GREEN"], cnum["BLACK"]);
    init_pair(3, cnum["OLIVE"], cnum["BLACK"]);
    init_pair(4, cnum["NAVY"], cnum["BLACK"]);
    init_pair(5, cnum["PURPLE"], cnum["BLACK"]);
    init_pair(6, cnum["TEAL"], cnum["BLACK"]);
    init_pair(7, cnum["SILVER"], cnum["BLACK"]);
    init_pair(8, cnum["GREY"], cnum["BLACK"]);
    init_pair(9, cnum["RED"], cnum["BLACK"]);
    init_pair(10, cnum["LIME"], cnum["BLACK"]);
    init_pair(11, cnum["YELLOW"], cnum["BLACK"]);
    init_pair(12, cnum["BLUE"], cnum["BLACK"]);
    init_pair(13, cnum["FUCHSIA"], cnum["BLACK"]);
    init_pair(14, cnum["AQUA"], cnum["BLACK"]);
    init_pair(15, cnum["WHITE"], cnum["BLACK"]);

    init_pair(16, cnum["BLACK"], cnum["WHITE"]);
    init_pair(17, cnum["MAROON"], cnum["WHITE"]);
    init_pair(18, cnum["GREEN"], cnum["WHITE"]);
    init_pair(19, cnum["OLIVE"], cnum["WHITE"]);
    init_pair(20, cnum["NAVY"], cnum["WHITE"]);
    init_pair(21, cnum["PURPLE"], cnum["WHITE"]);
    init_pair(22, cnum["TEAL"], cnum["WHITE"]);
    init_pair(23, cnum["SILVER"], cnum["WHITE"]);
    init_pair(24, cnum["GREY"], cnum["WHITE"]);
    init_pair(25, cnum["RED"], cnum["WHITE"]);
    init_pair(26, cnum["LIME"], cnum["WHITE"]);
    init_pair(27, cnum["YELLOW"], cnum["WHITE"]);
    init_pair(28, cnum["BLUE"], cnum["WHITE"]);
    init_pair(29, cnum["FUCHSIA"], cnum["WHITE"]);
    init_pair(30, cnum["AQUA"], cnum["WHITE"]);
    init_pair(31, cnum["WHITE"], cnum["WHITE"]);

    init_pair(32, cnum["BLACK"], cnum["PURPLE"]);
}

class Colorly {
   public:
    Colorly() { attron(COLOR_PAIR(color)); }
    ~Colorly() { attroff(COLOR_PAIR(color)); }
    static void setColor(int c) { color = c; }
    static void setWin(WINDOW* w) { win = w; }
    static void randColor() { color = rand() % 32 + 1; }
    static void colorOn() { attron(COLOR_PAIR(color)); }
    static void colorOff() { attroff(COLOR_PAIR(color)); }
    static void colorOn(int c) { attron(COLOR_PAIR(c)); }
    static void colorOff(int c) { attroff(COLOR_PAIR(c)); }
    static void winColorOn() { wattron(win, COLOR_PAIR(color)); }
    static void winColorOff() { wattroff(win, COLOR_PAIR(color)); }
    static void winColorOn(int c) { wattron(win, COLOR_PAIR(c)); }
    static void winColorOff(int c) { wattroff(win, COLOR_PAIR(c)); }
    static void winColorOn(WINDOW* w) { wattron(w, COLOR_PAIR(color)); }
    static void winColorOff(WINDOW* w) { wattroff(w, COLOR_PAIR(color)); }
    static void winColorOn(WINDOW* w, int c) { wattron(w, COLOR_PAIR(c)); }
    static void winColorOff(WINDOW* w, int c) { wattroff(w, COLOR_PAIR(c)); }

   private:
    static int color;
    static WINDOW* win;
};

// Define the static member variables
int Colorly::color   = rand() % 32 + 1;
WINDOW* Colorly::win = nullptr;