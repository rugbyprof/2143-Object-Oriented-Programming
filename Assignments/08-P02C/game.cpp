#include <locale.h>
#include <ncurses.h>

#include "buttonClass.hpp"
#include "colors.hpp"
#include "diceClass.hpp"
#include "gridClass.hpp"
#include "logger.hpp"
#include <ctime>
#include <string>
#include <vector>

using namespace std;

int main() {
    srand(time(0));
    setlocale(LC_ALL, "");  // Enable Unicode support
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // Hide the cursor
    clear();
    refresh();

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    start_color();

    colorful();

    Logger::setFilePath("log2.txt");

    int rows, cols, size;
    int ch;

    getmaxyx(stdscr, rows, cols);

    string text = "ROLL";

    size = strlen(text.c_str()) + 2;

    Logger::log("vals", vector<int>({size, 3, (rows / 2), ((cols - size) / 2)}));

    // Button button(text, 2, 1, Frame({size, 3, (rows / 2), ((cols - size) / 2)}));
    Button button(text, 5, 32, Frame({3, size, 10, 15}));
    button.draw_button();

    Grid grid(1, 10);
    grid.refreshGrid();

    DiceViz dice(3, 30);

    dice.setBorderColor(11);
    dice.setDotColor(5);

    while (true) {
        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == KEY_MOUSE) {
            MEVENT event;
            Logger::log("Mouse pressed", "true");
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    Logger::log("clicked", vector<int>({event.y, event.x}));
                    if (button.clicked(event.y, event.x)) {
                        button.draw_button();
                        Logger::log("drawing button", "true");
                        dice.animate_dice(30);
                        dice.draw_dice(dice.getLastDiceValue());
                        button.toggle();
                    }
                    if (grid.clicked(event.y, event.x - 1)) {
                        Logger::log("clicked grid", "true");
                        dice.clear();
                        grid.addValue(event.y, event.x - 1, dice.getLastDiceValue());  // Mark click location
                        grid.refreshGrid();
                    }
                }
            }
        }
        Logger::log("Key pressed", to_string(ch));
        button.draw_button();
        refresh();
        ch = getch();
    }

    // while (true) {
    //     // mvprintw(rows / 2, (cols / 2) - strlen(text.c_str()), text.c_str());
    //     ch = getch();

    //     if (ch == 'q' || ch == 'Q') {
    //         break;
    //     } else if (ch == KEY_MOUSE) {
    //         MEVENT event;
    //         Logger::log("Mouse pressed", "true");
    //         if (getmouse(&event) == OK) {
    //             if (event.bstate & BUTTON1_CLICKED) {
    //                 Logger::log("clicked", vector<int>({event.y, event.x}));
    //                 if (button.clicked(event.y, event.x)) {
    //                     button.draw_button();
    //                     Logger::log("drawing button", "true");
    //                     dice.animate_dice(30);
    //                     // dice.refresh();
    //                 }
    //                 if (grid.clicked(event.y, event.x - 1)) {
    //                     Logger::log("clicked grid", "true");
    //                     grid.addValue(event.y, event.x, rand() % 6 + 1);  // Mark click location
    //                 }
    //             }
    //         }
    //     }
    //     Logger::log("Key pressed", to_string(ch));
    //     button.draw_button();
    //     refresh();
    // }
    clear();
    endwin();
    return 0;
}