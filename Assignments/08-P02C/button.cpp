#include <ncurses.h>

#include <string>

// Define button position and size
const int BUTTON_Y      = 5;
const int BUTTON_X      = 10;
const int BUTTON_WIDTH  = 10;
const int BUTTON_HEIGHT = 3;

void draw_button(WINDOW *button_win, bool clicked) {
    box(button_win, 0, 0);  // Draw border around button
    wrefresh(button_win);
    // Set color pair based on clicked state
    if (clicked) {
        wbkgd(button_win, COLOR_PAIR(3));  // Black background, white text
        wattron(button_win, COLOR_PAIR(3));
    } else {
        wbkgd(button_win, COLOR_PAIR(1));  // White background, black text
        wattron(button_win, COLOR_PAIR(1));
    }

    // Draw button text centered in the window
    mvwprintw(button_win, 1, (BUTTON_WIDTH - 4) / 2, "ROLL");
    wrefresh(button_win);
}

bool is_click_in_button(int click_y, int click_x) {
    return click_y >= BUTTON_Y && click_y < BUTTON_Y + BUTTON_HEIGHT && click_x >= BUTTON_X && click_x < BUTTON_X + BUTTON_WIDTH;
}

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

    // Initialize color pairs
    init_pair(1, COLOR_BLACK, COLOR_WHITE);  // Normal: Black text, white background
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // Clicked: White text, black background
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Clicked: White text, black background

    // Create button window
    WINDOW *button_win = newwin(BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_Y, BUTTON_X);
    draw_button(button_win, false);  // Draw initially unclicked button

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
            if (event.bstate & BUTTON1_CLICKED && is_click_in_button(event.y, event.x)) {
                clicked = !clicked;                // Toggle the clicked state
                draw_button(button_win, clicked);  // Redraw button based on state

                // Print "button clicked" message on the main screen
                mvprintw(BUTTON_Y + BUTTON_HEIGHT + 2, BUTTON_X, "Button clicked");
                refresh();
            }
        }
    }

    // Cleanup
    delwin(button_win);
    endwin();
    return 0;
}