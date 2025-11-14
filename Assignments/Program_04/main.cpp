#include "./includes/AutomatonUtils.hpp"
#include "./includes/ConwayLife.hpp"
#include "./includes/Screen.hpp"

#include <sys/ioctl.h>
#include <unistd.h> // For STDOUT_FILENO

using namespace std;

int main(int argc, char* argv[]){
    // int rows,cols = 0;
    // rows = stoi(argv[1]);
    // cols = stoi(argv[2]);

    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        std::cout << "Terminal rows: " << w.ws_row << std::endl;
        std::cout << "Terminal columns: " << w.ws_col << std::endl;
    } else {
        std::cerr << "Error getting terminal size." << std::endl;
    }

    TextScreen txtscr;

    ConwayLife gol(w.ws_row-1,w.ws_col/2);
    while(1){
        txtscr.render(gol.getGrid());
        gol.step();
        txtscr.pause(500);
    }


    return 0;
}