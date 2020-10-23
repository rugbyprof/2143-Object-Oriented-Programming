#include <iostream>
#include <map>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

using namespace std;

/**
 * This code is on replit without m any comments!! https://repl.it/@rugbyprof/Colored-text#main.cpp
 * 
 * Authors Note: I've been doing this so long that sometimes I over estimate what I remember. The 
 * coding GODS will always be there to slap stuff right out of your head. Which they did. 
 * 
 * Its not about failing ... its how you react to failure. I am now the proud owner of that little 
 * $##@*&*& of a color escape sequence. 
 * 
 * HELPER STUFF:
 *      I had to go study: https://www.tecmint.com/customize-bash-colors-terminal-prompt-linux/ and get the 
 *      escape sequence defintions and color names to int values.
 * 
 * FIRST THOUGHT:
 *      My first attempt was with static struct members in which I refreshed my memory here:
 *      LINK: https://www.edureka.co/blog/scope-resolution-operator-in-cpp/#:~:text=You%20can%20use%20scope%20resolution,operator%20(i.e.%20%3A%3Anum).
 *      That code is on repl.it in a hold.cpp file. 
 * 
 * SECOND THOUGHT:
 *           STL MAPS: http://www.cplusplus.com/reference/map/map/
 *       EXAMPLE: 
 *           map<string, string> fg; 
 *  
 *       Insert elements into the map: 
 *          fg.insert(pair<string, string>("Black", "30")); 
 *          fg.insert(pair<string, string>("Red", "31")); 
 *          fg.insert(pair<string, string>("Green", "32")); 
 *          fg.insert(pair<string, string>("Yellow", "33")); 
 *          fg.insert(pair<string, string>("Blue", "34")); 
 *          fg.insert(pair<string, string>("Purple", "35")); 
 *        
 *      Now you can 
 *         cout<<fg["Black"]; // and you get 30. 
 *      I also thougth this was clunky so I ditched it. 
 */




// Actual solution. Not perfect, but better

// We needed this in class just for reference
// Text Format	        Foreground (text) color	    Background color
// 0: normal text	    30: Black	                40: Black
// 1: bold	            31: Red	                    41: Red
// 4: Underlined text	32: Green	                42: Green
// 5: blink             33: Yellow	                43: Yellow
// 7: reverse           34: Blue	                44: Blue
// 8: concealed         35: Purple	                45: Purple
//                      36: Cyan	                46: Cyan
//                      37: White	                47: White

/**
 * NOTE: 
 * To alter the text you start with:
 *      "\033["         // add nothing but start of escape
 *      "\033[31"       // add foreground color (red)
 *      "\033[31;44"    // add foreground (red) and background color (blue)
 *      "\033[31;44m"   // its not finished until you add the "M"
 *                      // even for the previous example, it needs the m if the 31 is the last number.
 */

// more colors here
//https://misc.flogisoft.com/bash/tip_colors_and_formatting

// As you can see above, the foreground and background
// colors have the same ones value. You just need to append
// a tens in front (3 for foreground 4 for background)
string Black = "0";
string Red = "1";
string Green = "2";
string Yellow = "3";
string Blue = "4";
string Purple = "5";
string Cyan = "6";
string White = "7";
string Default = "9";

// Color "class/struct :) "
// I only used this construct so I could overload cout
// It quite literally has two data members (foreground color and background color)

/**
 * Description:
 *      Color -  simply represents the terminal color values to get differing
 *               foreground and background colors.
 * Methods:
 *      Color()             - default prints white text on black background
 *      Color(string)       - sets the foreground color, keeps default back
 *      Color(string,string)- sets both fore and background colors
 *      friend Ostream      - override the cout class so we can inject escape sequences for color!
 */
struct Color {
    string fg; // foreground color
    string bg; // background color

    // white foreground and black background
    Color() {
        fg = "3" + White;
        bg = "4" + Default;
    }

    // One param means foreground color with Black bacground
    Color(string f) : fg{f} {
        fg = "3" + fg;
        bg = "4" + Default;
    }

    // Two params = both foreground and background colors
    Color(string f, string b) : fg{f}, bg{b} {
        fg = "3" + fg;
        bg = "4" + bg;
    }
    friend ostream &operator<<(std::ostream &out, const Color &color);
};

/**
 * When a "Color(fg,bg)" is placed in cout, this method ensures
 * that its escape characters are formatted correctly. Pretty
 * simple.
 */
ostream &operator<<(std::ostream &out, const Color &color) {
    out << "\033[0;" << color.fg << ";" << color.bg << "m";
    return out;
}

/**
 * returns a random string between 0 - 8
 */
string randomColor() {
    return to_string(rand() % 8);
}

/**
 * returns a random card suit
 */
string randomSuit() {
    string suits[4] = {"♠", "♦", "♣", "♥"};
    return suits[rand() % 4];
}

/**
 * Description: 
 *      Jumps the cursor to specific x,y coord
 * Methods:
 *      GotoXY(int,int) - one constructor that moves to row and col
 * 
 *      friend Ostream   - override the cout class so we can jump between coords!
 */
struct GotoXY {
    int x;      // col
    int y;      // row

    GotoXY(int x, int y) : x{x}, y{y} {}
    friend ostream &operator<<(std::ostream &gout, const GotoXY &printxy);
};

/**
 * When a "GotoXY" instance is placed in a cout statement
 * this method takes over and jumps to that location!
 */
ostream &operator<<(std::ostream &out, const GotoXY &printxy) {
    out << "\033[" << printxy.y << ";" << printxy.x << "H";
    ;
    return out;
}

/**
 * Little helper methods to figure out what the size of the
 * terminal is in "rows" and "cols".
 */
struct winsize w;
struct WindowSize{
    int rows;
    int cols;

    /**
     * Uses some built in libraries to get a terminal window size.
     *      stdio.h, sys/ioctl.h, unistd.h 
     */
    WindowSize(){
        // magic happens here
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        // place values in more readable 
        // vars here ...
        rows = w.ws_row;
        cols = w.ws_col;
    }
    
    /**
     * Guess
     */
    int termWidth(){
        return cols;
    }

    /**
     * Guess
     */
    int termHeight(){
        return rows;
    }

    /**
     * Random int between 0 and width of terminal window
     */
    int randCol(){
        return rand() % cols;
    }

    /**
     * Random int between 0 and height of terminal window
     */
    int randRow(){
        return rand() % rows;
    }
};


int main() {
    srand(time(0));
    WindowSize W;
    
    for (int i = 0; i < 100000000; i++) {
        int x = W.randCol();
        int y = W.randRow();
        cout << GotoXY(x, y);
        cout << Color(randomColor(), Default) << randomSuit();
    }
    return 0;
}
