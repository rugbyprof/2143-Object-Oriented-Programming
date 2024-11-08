#pragma once

#include <ncurses.h>

#include <string>

struct Frame {
    int h;  // Height
    int w;  // Width
    int y;  // Y-coordinate
    int x;  // X-coordinate
};

class Button {
   private:
    Frame frame;
    WINDOW *button_win;
    bool is_clicked;
    std::string text;
    int on_color;
    int off_color;

   public:
    Button(std::string t, int on_color, int off_color) : text(t), on_color(on_color), off_color(off_color) {
        frame      = Frame({5, 20, 0, 0});
        is_clicked = false;
        button_win = newwin(frame.h, frame.w, frame.y, frame.x);
    }
    Button(std::string t, int on_color, int off_color, Frame f) : text(t), on_color(on_color), off_color(off_color), frame(f) {
        is_clicked = false;
        button_win = newwin(frame.h, frame.w, frame.y, frame.x);
    }
    void draw_button() {
        box(button_win, 0, 0);  // Draw border around button
        wrefresh(button_win);
        // Set color pair based on clicked state
        if (is_clicked) {
            wbkgd(button_win, COLOR_PAIR(on_color));  // Black background, white text
            wattron(button_win, COLOR_PAIR(on_color));
        } else {
            wbkgd(button_win, COLOR_PAIR(off_color));  // White background, black text
            wattron(button_win, COLOR_PAIR(off_color));
        }

        // Draw button text centered in the window
        int wmiddle = (frame.w - text.length()) / 2;
        int hmiddle = (frame.h - 1) / 2;
        mvwprintw(button_win, hmiddle, wmiddle, text.c_str());
        wrefresh(button_win);
    }

    void toggle() {
        is_clicked = !is_clicked;
        draw_button();
    }

    bool clicked(int y, int x) {
        if (y >= frame.y && y < frame.y + frame.h && x >= frame.x && x < frame.x + frame.w) {
            is_clicked = !is_clicked;
            return true;
        }
        return false;
    }
};