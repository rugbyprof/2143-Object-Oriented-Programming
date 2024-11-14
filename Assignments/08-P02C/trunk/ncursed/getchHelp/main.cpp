#include <ncurses.h>
#include <unistd.h>  // For usleep

int main() {
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);  // Make getch() non-blocking
    keypad(stdscr, TRUE);

    bool running = true;
    int ch;

    while (running) {
        ch = getch();  // Non-blocking check for user input

        switch (ch) {
            case 'q':
                running = false;  // Quit the game on 'q' press
                break;
            case KEY_UP:
                // Handle up arrow key
                break;
            case KEY_DOWN:
                // Handle down arrow key
                break;
                // Additional cases for other keys
        }

        // Game logic and screen updates go here
        mvprintw(5, 5, "Game is running... Press 'q' to quit.");

        refresh();      // Update screen
        usleep(50000);  // Sleep for 50ms to control frame rate
    }

    endwin();
    return 0;
}