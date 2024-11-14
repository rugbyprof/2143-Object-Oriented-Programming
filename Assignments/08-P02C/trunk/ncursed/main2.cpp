#include <ncurses.h>

#include "color_class.hpp"
#include "logger_class.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <string>
using namespace std;

class NcursesGame;

void GAMELOG(string key, string msg) {
    Colorly::colorOn(1);
    Logger::log(key, msg);
    Logger::printLastLine(stdscr);
}

class WindowType {
   public:
    WINDOW* win;
    int start_y, start_x;
    int height, width;
    int max_y, max_x;
    int txt_color;
    int border_color;
    bool has_border;
    bool is_main;

    WindowType(int start_y, int start_x, int height, int width, bool has_border = true, bool is_main = false)
        : start_y(start_y), start_x(start_x), height(height), width(width), has_border(has_border), is_main(is_main) {
        win = newwin(height, width, start_y, start_x);
        getmaxyx(win, max_y, max_x);
    }
    void setTextColor(int color_pair) {
        txt_color = color_pair;
        Colorly::winColorOn(win, color_pair);
    }
    void setBorderColor(int color_pair) {
        border_color = color_pair;
        Colorly::winColorOn(win, color_pair);
    }
    void clearColor(int color_pair) {
        if (txt_color == color_pair) {
            Colorly::winColorOff(win, color_pair);
        } else if (border_color == color_pair) {
            Colorly::winColorOff(win, color_pair);
        }
    }
    void redraw(bool redraw_main = false) {
        wclear(win);    // Clear only the window
        wrefresh(win);  // Refresh only the window
        if (redraw_main) {
            redraw();
        }
    }
    /**
     * int x: x position to draw text
     * int y: y position to draw text
     * string text: text to draw
     */
    void drawText(int x, int y, const std::string& text) {
        if (has_border) {
            mvwprintw(win, y + 1, x + 1, text.c_str());
        } else {
            mvwprintw(win, y, x, text.c_str());
        }
    }
    void setBorder() { has_border = true; }
    void clearBorder() { has_border = false; }
};

class NcursesGame {
   public:
    NcursesGame() {
        is_initialized = false;
        main_color     = 2;
    };
    ~NcursesGame() { cleanup(); };

    void initialize() {
        if (is_initialized)
            return;
        initscr();
        noecho();
        curs_set(0);
        // nodelay(stdscr, TRUE);  // Make getch() non-blocking
        keypad(stdscr, TRUE);
        start_color();

        colorful();

        Colorly::setWin(stdscr);

        Colorly::setColor(4);

        clear();
        refresh();

        is_initialized = true;
    }

    void refresh_screen() { refresh(); }

    void draw_text(int x, int y, const std::string& text) {
        clear();
        mvaddstr(y, x, text.c_str());
        GAMELOG("draw_text", text);
    }

    void draw_char(int x, int y, char ch) {
        mvaddch(y, x, ch);
        GAMELOG("draw_text", to_string(ch));
    }

    void set_color(int color_pair) { Colorly::winColorOn(color_pair); }

    void clear_color(int color_pair) { Colorly::winColorOff(color_pair); }

    void quit(WINDOW* win) {
        int ch;
        win_draw_text(win, 1, 1, "YOUR QUITTING?? (Y/n)", true);
        win_redraw(win, true);
        ch = getch();
        if (ch == 'Y' || ch == 'y') {
            cleanup();
            exit(0);
        }
        return;
    }

    void cleanup() {
        for (auto& win_pair : windows) {
            delwin(win_pair.second);
        }
        if (is_initialized) {
            is_initialized = false;
            endwin();
        }
    }

    // Window management
    WINDOW* create_window(int height, int width, int starty, int startx) {
        WINDOW* win                                               = newwin(height, width, starty, startx);
        windows[std::to_string(reinterpret_cast<uintptr_t>(win))] = win;
        return win;
    }

    void delete_window(WINDOW* win) {
        if (win) {
            delwin(win);
            windows.erase(std::to_string(reinterpret_cast<uintptr_t>(win)));
        }
    }

    void win_redraw(WINDOW* win, bool redraw_main = false) {
        wclear(win);    // Clear only the window
        wrefresh(win);  // Refresh only the window
        if (redraw_main) {
            redraw();
        }
    }

    void win_redraw_all() {
        for (auto& win_pair : windows) {
            wrefresh(win_pair.second);  // Refresh each window individually
        }
        refresh();  // Also refresh stdscr if needed
    }

    // Drawing methods
    void win_draw_text(WINDOW* win, int y, int x, const std::string& text, bool draw_box = false) {
        Colorly::winColorOn(win, 5);
        if (win) {
            if (draw_box) {
                box(win, 0, 0);
            }
            Colorly::winColorOn(win, 2);
            mvwprintw(win, y, x, text.c_str());  // Draw within window
            Colorly::winColorOff(win, 2);
        } else {
            mvprintw(y, x, text.c_str());  // Fallback to stdscr
        }
    }

    // Drawing methods
    void win_draw_text(WINDOW* win, int y, int x, int y2, int x2, const std::string& text, bool draw_box = false) {
        Colorly::winColorOn(win, 5);
        if (win) {
            if (draw_box) {
                box(win, 0, 0);
            }
            Colorly::winColorOn(win, 2);
            mvwprintw(win, y2, x2, text.c_str());  // Draw within window
            Colorly::winColorOff(win, 2);
        } else {
            mvprintw(y, x, text.c_str());  // Fallback to stdscr
        }
    }

    void win_draw_char(WINDOW* win, int x, int y, char ch) {
        if (win) {
            mvwaddch(win, y, x, ch);  // Draw within window
        } else {
            mvaddch(y, x, ch);  // Fallback to stdscr
        }
    }

    void redraw() {
        clear();
        refresh();
    }

   private:
    bool is_initialized;
    int main_color;
    std::map<std::string, WINDOW*> windows;  // Optional: Store windows by name for easy access
};

int main() {
    NcursesGame game;
    game.initialize();
    game.set_color(2);

    int w, h;
    getmaxyx(stdscr, h, w);

    int info_height = 3, info_width = w - 1;
    int game_height = h - 4, game_width = w - 1;

    WINDOW* info_win = game.create_window(info_height, info_width, 1, 1);  // Top-left for info
    WINDOW* game_win = game.create_window(game_height, game_width, 4, 1);  // Main game area

    box(info_win, 0, 0);
    box(game_win, 0, 0);

    MEVENT event;
    int ch = -1;

    string info = "RESTARTING GAME";

    while (true) {
        game.win_draw_text(info_win, 5, 6, "getch: " + to_string(ch), true);
        // if (ch == 'q') {
        //     game.quit(info_win);

        if (ch == 'r') {
            game.win_draw_text(game_win, game_height / 2, (game_width - info.size()) / 2, "RESTARTING GAME", true);
        }

        // mvwprintw(game_win, 20, 20, "WHAT THE HELL?");  // Draw within window

        // // Additional game loop code...

        game.win_redraw_all();
        // wrefresh(info_win);
        // wrefresh(game_win);
        ch = -1;
        while (ch < 0) {
            ch = getch();
        }
    }
    game.cleanup();
    return 0;
}