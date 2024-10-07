#include <locale.h>
#include <ncurses.h>
#include <unistd.h>  // For usleep()

#include <map>
#include <string>
#include <utility>

using namespace std;

void draw_dice(int start_y, int start_x, int number) {
    // Draw the box around the dice
    WINDOW *dice_win = newwin(5, 7, start_y, start_x);

    wattron(dice_win, COLOR_PAIR(1));  // Turn on color pair 2
    box(dice_win, 0, 0);
    wrefresh(dice_win);

    std::map<std::string, std::pair<int, int> > dot_pos;

    // Add entries to the map
    dot_pos["ul"] = std::make_pair(1, 1);  // Upper left
    dot_pos["ur"] = std::make_pair(1, 5);  // Upper right
    dot_pos["ml"] = std::make_pair(2, 1);  // Middle left
    dot_pos["mm"] = std::make_pair(2, 3);  // Middle middle
    dot_pos["mr"] = std::make_pair(2, 5);  // Middle right
    dot_pos["ll"] = std::make_pair(3, 1);  // Lower left
    dot_pos["lr"] = std::make_pair(3, 5);  // Lower right

    // Print dots based on the number on the dice
    switch (number) {
        case 1:
            mvwprintw(dice_win, dot_pos["mm"].first, dot_pos["mm"].second, "●");
            break;
        case 2:
            mvwprintw(dice_win, dot_pos["ul"].first, dot_pos["ul"].second, "●");
            mvwprintw(dice_win, dot_pos["lr"].first, dot_pos["lr"].second, "●");
            break;
        case 3:
            mvwprintw(dice_win, dot_pos["ul"].first, dot_pos["ul"].second, "●");
            mvwprintw(dice_win, dot_pos["mm"].first, dot_pos["mm"].second, "●");
            mvwprintw(dice_win, dot_pos["lr"].first, dot_pos["lr"].second, "●");
            break;
        case 4:
            mvwprintw(dice_win, dot_pos["ul"].first, dot_pos["ul"].second, "●");
            mvwprintw(dice_win, dot_pos["ur"].first, dot_pos["ur"].second, "●");
            mvwprintw(dice_win, dot_pos["lr"].first, dot_pos["lr"].second, "●");
            mvwprintw(dice_win, dot_pos["ll"].first, dot_pos["ll"].second, "●");
            break;
        case 5:
            mvwprintw(dice_win, dot_pos["ul"].first, dot_pos["ul"].second, "●");
            mvwprintw(dice_win, dot_pos["ur"].first, dot_pos["ur"].second, "●");
            mvwprintw(dice_win, dot_pos["lr"].first, dot_pos["lr"].second, "●");
            mvwprintw(dice_win, dot_pos["ll"].first, dot_pos["ll"].second, "●");
            mvwprintw(dice_win, dot_pos["mm"].first, dot_pos["mm"].second, "●");
            break;
        case 6:
            mvwprintw(dice_win, dot_pos["ul"].first, dot_pos["ul"].second, "●");
            mvwprintw(dice_win, dot_pos["ur"].first, dot_pos["ur"].second, "●");
            mvwprintw(dice_win, dot_pos["lr"].first, dot_pos["lr"].second, "●");
            mvwprintw(dice_win, dot_pos["ll"].first, dot_pos["ll"].second, "●");
            mvwprintw(dice_win, dot_pos["ml"].first, dot_pos["ml"].second, "●");
            mvwprintw(dice_win, dot_pos["mr"].first, dot_pos["mr"].second, "●");
            break;
    }
    wattroff(dice_win, COLOR_PAIR(2));  // Turn off the color

    wrefresh(dice_win);

    delwin(dice_win);
}

int main() {
    // Set the locale to use Unicode
    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();

    // Initialize colors
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);  // Text in red, background black
    init_pair(2, COLOR_BLUE, COLOR_BLACK);    // Text in blue, background black
    init_pair(3, COLOR_GREEN, COLOR_YELLOW);  // Text in blue, background black

    // Enable Unicode support in ncurses
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support colors\n");
        return 1;
    }

    // Draw a border
    box(stdscr, 0, 0);

    // Move the cursor and print text
    attron(COLOR_PAIR(3));  // Turn on color pair 1 (red text)
    mvprintw(3, 10, "Welcome to KnuckleBones!");  // Print colored text
    attroff(COLOR_PAIR(3));                       // Turn off the color

    refresh();        // Ensure the message stays on screen
    curs_set(FALSE);  // Hide the cursor

    int dy1 = 5, dx1 = 10;
    int dy2 = 5, dx2 = 20;
    int refresh_count = 50;  // Set how many times you want to refresh

    // Shuffle dice faces for a set amount of time
    for (int i = 0; i < refresh_count; ++i) {
        int dice_value = rand() % 6 + 1;  // Random number between 1 and 6
        // No need to clear the whole screen, just refresh the dice window
        draw_dice(dy1, dx1, dice_value);
        dice_value = rand() % 6 + 1;
        draw_dice(dy2, dx2, dice_value);
        usleep(100000);  // 100ms delay for visual effect
    }

    // Show final dice face
    int final_dice_value = rand() % 6 + 1;
    draw_dice(dy1, dx1, final_dice_value);
    draw_dice(dy1, dx1 + 10, final_dice_value);

    // Refresh to show changes
    refresh();

    getch();  // Wait for key press before exiting
    endwin();

    return 0;
}