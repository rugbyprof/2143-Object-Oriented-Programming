#include <ncurses.h>

#include <string>

int main() {
    initscr();             // Start ncurses mode
    noecho();              // Don't echo input characters to the screen
    cbreak();              // Disable line buffering, making input available immediately
    keypad(stdscr, TRUE);  // Enable special keys input like BACKSPACE

    // Define dimensions and position for the input box
    int box_height = 3;
    int box_width  = 30;
    int start_y    = 5;
    int start_x    = 10;

    // Create a new window for the input box
    WINDOW* input_win = newwin(box_height, box_width, start_y, start_x);
    if (input_win == NULL) {
        endwin();
        fprintf(stderr, "Error creating window.\n");
        return 1;
    }

    box(input_win, 0, 0);                  // Draw a border around the input box
    mvwprintw(input_win, 1, 1, "Name: ");  // Label inside the box
    wrefresh(input_win);                   // Display the initial box and label

    // Step 1: Input text box for name entry
    std::string name;
    int ch;
    while ((ch = wgetch(input_win)) != '\n') {   // '\n' represents the Enter key
        if (ch == KEY_BACKSPACE || ch == 127) {  // Handle backspace
            if (!name.empty()) {
                name.pop_back();
                // Clear last character and refresh the input line
                mvwprintw(input_win, 1, 7, "%s ", name.c_str());
            }
        } else if (ch >= 32 && ch <= 126 && name.size() < box_width - 8) {
            // Only add if it's a printable character and within box limit
            name += static_cast<char>(ch);
            mvwprintw(input_win, 1, 7, "%s", name.c_str());
        }
        wrefresh(input_win);  // Refresh the input box to show updates
    }

    // Clear the input box and move on to the main loop
    werase(input_win);                                           // Erase content from input window
    wborder(input_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove the border
    wrefresh(input_win);                                         // Refresh to show cleared content
    delwin(input_win);                                           // Delete the input window

    // Display the welcome message on the main screen
    clear();
    mvprintw(8, 5, "Welcome, %s! Press 'q' to quit.", name.c_str());
    refresh();

    // Main loop for program (could capture other input here)
    while ((ch = getch()) != 'q') {
        // Placeholder for additional actions
    }

    endwin();
    return 0;
}