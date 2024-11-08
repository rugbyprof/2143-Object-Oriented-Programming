#include <ncurses.h>

#include <string>

using namespace std;

// COLOR_BLACK   0
// COLOR_RED     1
// COLOR_GREEN   2
// COLOR_YELLOW  3
// COLOR_BLUE    4
// COLOR_MAGENTA 5
// COLOR_CYAN    6
// COLOR_WHITE   7

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string) {
    int length, x, y;
    float temp;

    if (win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    length = strlen(string);
    temp   = (width - length) / 2;
    x      = startx + (int)temp;
    mvwprintw(win, y, x, "%s", string);
    refresh();
}

struct Point {
    int x;
    int y;
};

struct Frame {
    int w;  // Width
    int h;  // Height
    int x;  // X-coordinate
    int y;  // Y-coordinate
};

class Button {
   private:
    Frame frame;
    WINDOW *button_win;
    bool is_clicked;
    string text;
    int on_color;
    int off_color;

   public:
    Button(string t, int on_color, int off_color) : text(t), on_color(on_color), off_color(off_color) {
        frame      = Frame({20, 5, 0, 0});
        is_clicked = false;
        button_win = newwin(frame.h, frame.w, frame.y, frame.x);
    }
    Button(string t, int on_color, int off_color, Frame f) : text(t), on_color(on_color), off_color(off_color), frame(f) {
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

    bool clicked(int y, int x) {
        if (y >= frame.y && y < frame.y + frame.h && x >= frame.x && x < frame.x + frame.w) {
            is_clicked = !is_clicked;
            return true;
        }
        return false;
    }
};

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // Hide the cursor

    clear();
    refresh();

    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);  // Enable all mouse events
    start_color();

    // COLOR_BLACK   0
    // COLOR_RED     1
    // COLOR_GREEN   2
    // COLOR_YELLOW  3
    // COLOR_BLUE    4
    // COLOR_MAGENTA 5
    // COLOR_CYAN    6
    // COLOR_WHITE   7

    // Initialize color pairs
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);  // Normal: Black text, white background
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Clicked: White text, black background
    init_pair(3, COLOR_RED, COLOR_BLACK);     // Clicked: White text, black background

    Button button("ROLL", 1, 2, Frame({3, 10, 10, 10}));

    button.draw_button();

    // box(stdscr, 0, 0);

    MEVENT event;
    bool clicked = false;

    // Main event loop
    while (true) {
        int ch = getch();

        if (ch == 'q')
            break;  // Press 'q' to quit

        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            // Check if left mouse button was clicked within the button's bounds
            if (event.bstate & BUTTON1_CLICKED && button.clicked(event.y, event.x)) {
                clicked = !clicked;    // Toggle the clicked state
                button.draw_button();  // Redraw button based on state

                // Print "button clicked" message on the main screen
                // mvprintw(BUTTON_Y + BUTTON_HEIGHT + 2, BUTTON_X, "Button clicked");
                refresh();
            }
        }
    }

    // Cleanup
    // delwin(button_win);
    endwin();
    return 0;
}