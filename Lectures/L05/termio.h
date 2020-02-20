#pragma once
// Define whether we are using Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS true
#endif

// Include for all platforms
#include <chrono>
#include <codecvt>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <vector>

// Include only for Windows
#if defined(WINDOWS)
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#else
// Include only for *nix
#include <unistd.h>
#endif

namespace Term
{

using std::cout;
using std::ostream;
using std::string;
using std::to_string;
using std::vector;
using std::wcout;
using std::wostream;

/* ██████╗ ██████╗  ██████╗ ████████╗ ██████╗ ████████╗██╗   ██╗██████╗ ███████╗███████╗       
 * ██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔═══██╗╚══██╔══╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔════╝       
 * ██████╔╝██████╔╝██║   ██║   ██║   ██║   ██║   ██║    ╚████╔╝ ██████╔╝█████╗  ███████╗       
 * ██╔═══╝ ██╔══██╗██║   ██║   ██║   ██║   ██║   ██║     ╚██╔╝  ██╔═══╝ ██╔══╝  ╚════██║       
 * ██║     ██║  ██║╚██████╔╝   ██║   ╚██████╔╝   ██║      ██║   ██║     ███████╗███████║       
 * ╚═╝     ╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝    ╚═╝      ╚═╝   ╚═╝     ╚══════╝╚══════╝       
 *                                                                                            
 *    ██╗        ██████╗ ██████╗ ███╗   ██╗███████╗████████╗ █████╗ ███╗   ██╗████████╗███████╗
 *    ██║       ██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗████╗  ██║╚══██╔══╝██╔════╝
 * ████████╗    ██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ███████║██╔██╗ ██║   ██║   ███████╗
 * ██╔═██╔═╝    ██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██║██║╚██╗██║   ██║   ╚════██║
 * ██████║      ╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║██║ ╚████║   ██║   ███████║
 * ╚═════╝       ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
 * ANSI Shadow font
 * http://patorjk.com/software/taag/
*/

/**
 * TermIO Color codes, used to choose foreground and background
 * in the Color object
 */
const unsigned short DEFAULT = 0;
const unsigned short BLACK = 1;
const unsigned short RED = 2;
const unsigned short YELLOW = 3;
const unsigned short GREEN = 4;
const unsigned short BLUE = 5;
const unsigned short CYAN = 6;
const unsigned short MAGENTA = 7;
const unsigned short WHITE = 8;

/** Fuses two multi-line string together for printing side-by-side */
inline string fuse(string left, string right, bool pad = false);

/** Fuses multiple multi-line strings together for printing side-by-side. */
inline string fuse(std::initializer_list<string> strings, bool pad = false);

/** Fuses multiple multi-line strings together for printing side-by-side. */
inline string fuse(std::vector<string> strings, bool pad = false);

/** Split a string and store each new substring in a vector. */
inline vector<string> split(string text, char delim, bool include = false);

/** Split a string, using a regular expression as a delimeter, and store
 * each new substring in a vector. */
inline vector<string> rsplit(string text, string delim, bool include = false);

/** Replaces all instances of a substring in a text with a new string. */
inline string replace_all(string text, string from, string to);

/** It is easier to consistently pass in strings instead of keeping track of
 * wide vs narrow strings. So, we will overload << to make wostreams able to
 * work with strings (by converting them inside the operation to wstring) */
inline std::wostream &operator<<(wostream &wout, string text);

/**
 * A Point object is used to move the cursor on the terminal.
 * When sent into an IO object, the cursor will change to the Point's
 * row and column position
 */
class Point
{
public:
    unsigned short row;
    unsigned short col;
    /** Creates a point */
    inline Point(const unsigned short &row, const unsigned short &col);
};
typedef Point pnt;
typedef Point p;

/**
 * A Color object is used to color the strings being sent to the terminal.
 * When sent to an IO object, the terminal will begin using the specified
 * foreground and background colors from the Color object.
 */
class Color
{
public:
    unsigned short fg;
    unsigned short bg;
    /** Creates a Color object */
    inline Color(const unsigned short &fg, const unsigned short &bg = 0);
};
typedef Color col;

/**
 * Commands are objects which when sent to an IO object should run some
 * function.
 * Their function is stored as the call() method. Commands should be unique
 * inherited classes of this super-class and should override call().
 */
class Command
{
public:
    virtual void call() = 0;
};
typedef Command com;

/**
 * CLEAR IS A SINGLETON: This means there is only ONE instance of the class.
 * The instance is defined by Clear::get() and there are two references to it
 * declared, Term::clear and Term::clr.
 * The Clear object is a command which, when passed to an IO object, will
 * clear the terminal's screen using its call() method.
 */
class Clear : public Command
{
public:
    inline static Clear &get();
    inline void call() override;

private:
    inline Clear();
};
static Clear &clear = Clear::get();
static Clear &clr = Clear::get();

/**
 * SLEEP IS A SINGLETON: This means there is only ONE instance of the class.
 * The instance is defined by Sleep::get() and there are two references to it
 * declared, Term::sleep and Term::slp.
 * The Sleep object is a command which, when passed to an IO object, will
 * make the program sleep for a time specified in the objects constructor.
 */
class Sleep : public Command
{
public:
    inline static Sleep &get();
    /** Stops the thread (or program, if single-threaded) for a number of
     * milliseconds determined by the data member of this object. */
    inline void call() override;
    /** Sets how many ms the thread should sleep when
     * using the sleep object. */
    inline Sleep &operator()(int ms);

private:
    unsigned int ms;
    inline Sleep();
};
static Sleep &sleep = Sleep::get();
static Sleep &slp = Sleep::get();

/**
 * Main input/output control for the library. Can use various other objects to
 * print, colorize, get input, and various screen functions.
 */
class IO
{
public:
    // constructors

    inline IO();
    inline IO(ostream &out);
    inline IO(wostream &wout);

    // output operations

    /** Prints a string to the terminal and interprets any color codes found */
    inline IO &operator<<(string text);
    /** Prints a character to the terminal */
    inline IO &operator<<(const char &letter);
    /** Prints an integer to the terminal */
    inline IO &operator<<(const int &number);
    /** Prints a double to the terminal */
    inline IO &operator<<(const double &number);

    // special output operations

    /** Moves the terminal's cursor to a row/column specified
     * by a Point object. */
    inline IO &operator<<(const Point &point);
    /** Changes the color of the terminal to the foreground and
     * background specified by the Color object. */
    inline IO &operator<<(const Color &color);
    /** Executes a command object. */
    inline IO &operator<<(Command &command);

    // input operations
    /** Gets a single character from stdin. Input is unbuffered, echoless,
     * blocking. For non-blocking, use a separate thread. */
    inline IO &operator>>(char &ch_var);
    /** Gets a single key from stdin (characters or arrow keys). Input is
     * unbuffered, echoless, blocking. For non-blocking, use a separate
     * thread. */
    inline IO &operator>>(char *&str_var);

private:
    ostream *out;
    wostream *wout;
    bool wide;
    inline void set_color(Color c);

#if defined(WINDOWS)
    bool windows_setup;
    HANDLE stdin_terminal;
    HANDLE stdout_terminal;
    inline void setupWindows();
#endif
};
} // namespace Term

/* ██╗███╗   ███╗██████╗ ██╗     ███████╗███╗   ███╗███████╗███╗   ██╗████████╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗
 * ██║████╗ ████║██╔══██╗██║     ██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
 * ██║██╔████╔██║██████╔╝██║     █████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║   ███████║   ██║   ██║██║   ██║██╔██╗ ██║███████╗
 * ██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║
 * ██║██║ ╚═╝ ██║██║     ███████╗███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║███████║
 * ╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
 * ANSI Shadow font
 * http://patorjk.com/software/taag/
*/

/* dP     dP           dP                                 88888888b                              dP   oo                            
 * 88     88           88                                 88                                     88                                 
 * 88aaaaa88a .d8888b. 88  88d888b. .d8888b. 88d888b.    a88aaaa    dP    dP 88d888b. .d8888b. d8888P dP .d8888b. 88d888b. .d8888b. 
 * 88     88  88ooood8 88  88'  `88 88ooood8 88'  `88     88        88    88 88'  `88 88'  `""   88   88 88'  `88 88'  `88 Y8ooooo. 
 * 88     88  88.  ... 88  88.  .88 88.  ... 88           88        88.  .88 88    88 88.  ...   88   88 88.  .88 88    88       88 
 * dP     dP  `88888P' dP  88Y888P' `88888P' dP           dP        `88888P' dP    dP `88888P'   dP   dP `88888P' dP    dP `88888P' 
 * ooooooooooooooooooooooo~88~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 *                         dP                                                                                                       
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

/**
 * Fuses two multi-line string together for printing side-by-side
 * @param left the string that will be on the left half of the fused string
 * @param right the string that will be on the right half of the fused string
 * @param pad bool, whether to pad each line of the string to be the same width
 */
std::string Term::fuse(string left, string right, bool pad)
{
    string result = "";
    // split the strings, create vectors
    vector<string> lv = split(left, '\n');
    vector<string> rv = split(right, '\n');
    // correct the number of lines in the strings so they match
    if (lv.size() > rv.size())
    {
        int diff = lv.size() - rv.size();
        for (int i = 0; i < diff; i++)
        {
            rv.push_back("");
        }
    }
    else if (lv.size() < rv.size())
    {

        int diff = rv.size() - lv.size();
        for (int i = 0; i < diff; i++)
        {
            lv.push_back("");
        }
    }
    if (pad)
    {
        // find the largest line out of any of the vectors
        int max = 0;
        for (int i = 0; i < lv.size(); i++)
        {
            if (lv[i].size() > max)
                max = lv[i].size();
            if (rv[i].size() > max)
                max = rv[i].size();
        }
        // for each line in both vectors, pad the line for max size
        for (int i = 0; i < lv.size(); i++)
        {
            if (lv[i].size() < max)
            {
                int diff = max - lv[i].size();
                lv[i] += std::string(diff, ' ');
            }
            if (rv[i].size() < max)
            {
                int diff = max - rv[i].size();
                rv[i] += std::string(diff, ' ');
            }
        }
    }
    // loop through the vectors and produce the new string
    for (int i = 0; i < lv.size(); i++)
    {
        result += lv[i] + rv[i] + '\n';
    }
    return result;
}

/**
 * Fuses multiple multi-line strings together for printing side-by-side.
 * @param strings an initializer list of strings to fuse, left to right
 * Initializer lists look like: {myStrVar, "Hello", "test", other_string_var}
 * @param pad bool, whether to pad each line of the string to be the same width
 */
std::string Term::fuse(std::initializer_list<string> strings, bool pad)
{
    // Variable for storing the resulting string
    string result = "";
    // Moving the initializer_list into a vector b/c I think they're easier
    vector<string> vstrings;
    vstrings.insert(vstrings.end(), strings.begin(), strings.end());
    // Loop through all strings and fuse them
    for (int i = 0; i < vstrings.size(); i++)
    {
        result = fuse(result, vstrings[i], pad);
    }
    return result;
}

/**
 * Fuses multiple multi-line strings together for printing side-by-side.
 * 
 * I didn't think you could create a dynamic intializer list, so I just
 * filled a vector with strings ....
 * 
 * @param strings a vector of strings ordered left to right
 * 
 * @param pad bool, whether to pad each line of the string to be the same width
 */
std::string Term::fuse(std::vector<string> strings, bool pad)
{
    // Variable for storing the resulting string
    string result = "";
    // Moving the initializer_list into a vector b/c I think they're easier

    // Loop through all strings and fuse them
    for (int i = 0; i < strings.size(); i++)
    {
        result = fuse(result, strings[i], pad);
    }
    return result;
}

/**
 * Split a string and store each new substring in a vector.
 * @param text the original string
 * @param delim the delimiting character to split by
 * @param include determines if the delimeter should be included in the
 * returned substrings
 * @return vector containing each substring
 */
std::vector<std::string> Term::split(string text, char delim, bool include)
{
    // Just calls the regular expression split but delimeter does not have to be
    // a regular expression
    return rsplit(text, string(1, delim), include);
}

/**
 * Split a string, using a regular expression as a delimeter, and store
 * each new substring in a vector.
 * Part of the rsplit() implementation came from Stack Overflow user Marcin,
 * see the following post:
 * https://stackoverflow.com/questions/16749069/c-split-string-by-regex
 * @param text the original string
 * @param delim the regular expression to match and split by
 * @param include determines if the delimeter should be included in the
 * returned substrings
 * @return vector containing each substring
 */
std::vector<std::string> Term::rsplit(string text, string delim, bool include)
{
    std::vector<std::string> elems;
    std::regex rgx(delim);
    // Find parts of the string which do not match the regexp and append them
    // to the vector
    // code -1 at the end means find everything but the rgx string (delimeter)
    std::sregex_token_iterator iter(text.begin(), text.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (iter != end)
    {
        elems.push_back(*(iter));
        ++iter;
    }

    // If we want to include the delimeter, then we need to go re-add it to
    // the beginning of each line.
    if (include)
    {
        // code 0 at the end means find instances of the rgx string (delimeter)
        std::sregex_token_iterator iter(text.begin(), text.end(), rgx, 0);
        std::sregex_token_iterator end;

        int i = 0;
        while (iter != end)
        {
            // We are inserting the delimiter at the start
            // of the NEXT string in the vector
            string temp = elems[i + 1];
            // assign the string the delimiter
            elems[i + 1] = *iter;
            // add back the original content
            elems[i + 1] += temp;
            // the iterator moves forward
            ++iter;
            // increment elems index
            i++;
        }
    }

    return elems;
}

/**
 * Replaces all instances of a substring in a text with a new string.
 * @param text the main text to replace in
 * @param from the substring to replace
 * @param to the new string to replace it with
 * @return the updated main string
 */
std::string Term::replace_all(string text, string from, string to)
{
    size_t start_pos = 0;
    // While we can find the substring "from"
    // (start position changes each time we make a replacement)
    while ((start_pos = text.find(from, start_pos)) != string::npos)
    {
        // Make the replacement
        text.replace(start_pos, from.length(), to);
        // Move past the string replacement's length, we don't need to
        // check it
        start_pos += to.length();
    }
    return text;
}

/**
 * It is easier to consistently pass in strings instead of keeping track of
 * wide vs narrow strings. So, we will overload << to make wostreams able to
 * work with strings (by converting them inside the operation to wstring)
 * @param wout the wide ostream to be output to
 * @param text the text to be converted to a wstring
 * @return the same wostream being used (for chaining output statements)
 */
std::wostream &Term::operator<<(wostream &wout, string text)
{
    /**
     * create a string <-> wide string converter
     * example from stack overflow
     * std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
     * std::string narrow = converter.to_bytes(wide_utf16_source_string);
     * std::wstring wide = converter.from_bytes(narrow_utf8_source_string);
     */
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide_text = converter.from_bytes(text);
    wout << wide_text;
    return wout;
}

/*  a88888b.                                                        dP     .88888.  dP       oo          
 * d8'   `88                                                        88    d8'   `8b 88                   
 * 88        .d8888b. 88d8b.d8b. 88d8b.d8b. .d8888b. 88d888b. .d888b88    88     88 88d888b. dP .d8888b. 
 * 88        88'  `88 88'`88'`88 88'`88'`88 88'  `88 88'  `88 88'  `88    88     88 88'  `88 88 Y8ooooo. 
 * Y8.   .88 88.  .88 88  88  88 88  88  88 88.  .88 88    88 88.  .88    Y8.   .8P 88.  .88 88       88 
 *  Y88888P' `88888P' dP  dP  dP dP  dP  dP `88888P8 dP    dP `88888P8     `8888P'  88Y8888' 88 `88888P' 
 * oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo88~ooooooooo
 *                                                                                           dP          
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

Term::Sleep::Sleep() {}

Term::Sleep &Term::Sleep::get()
{
    static Sleep instance;
    return instance;
}

/**
 * Sets how many ms the thread should sleep
 * when using the sleep object.
 * @param ms how much time, in miliseconds (1/1000 of a second), the
 * program should sleep when this object is passed to an IO object.
 */
Term::Sleep &Term::Sleep::operator()(int ms)
{
    this->ms = ms;
    return get();
}

/** Stops the thread (or program, if single-threaded) for a number of
 * milliseconds determined by the data member of this object. */
void Term::Sleep::call()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Term::Clear::Clear() {}

Term::Clear &Term::Clear::get()
{
    static Clear instance;
    return instance;
}

void Term::Clear::call()
{
#if defined(WINDOWS)
    // The Windows version of this method comes almost character-for-character
    // from the Microsoft docs. Credit Here:
    // https://docs.microsoft.com/en-us/windows/console/clearing-the-screen
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0}; // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
    {
        return;
    }
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
    {
        return;
    }
    SetConsoleCursorPosition(hConsole, coordScreen);
#else
    // on *nix use ANSI escape
    std::cout << "\033[2J";
#endif
}

/*  888888ba           oo            dP      8888ba.88ba             dP   dP                      dP          
 *  88    `8b                        88      88  `8b  `8b            88   88                      88          
 * a88aaaa8P' .d8888b. dP 88d888b. d8888P    88   88   88 .d8888b. d8888P 88d888b. .d8888b. .d888b88 .d8888b. 
 *  88        88'  `88 88 88'  `88   88      88   88   88 88ooood8   88   88'  `88 88'  `88 88'  `88 Y8ooooo. 
 *  88        88.  .88 88 88    88   88      88   88   88 88.  ...   88   88    88 88.  .88 88.  .88       88 
 *  dP        `88888P' dP dP    dP   dP      dP   dP   dP `88888P'   dP   dP    dP `88888P' `88888P8 `88888P' 
 * ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

/**
 * Creates a point
 * @param row the row where the point is positioned
 * @param col the column where the point is positioned
 */
Term::Point::Point(const unsigned short &row, const unsigned short &col)
{
    this->row = row;
    this->col = col;
}

/*  a88888b.          dP                      8888ba.88ba             dP   dP                      dP          
 * d8'   `88          88                      88  `8b  `8b            88   88                      88          
 * 88        .d8888b. 88 .d8888b. 88d888b.    88   88   88 .d8888b. d8888P 88d888b. .d8888b. .d888b88 .d8888b. 
 * 88        88'  `88 88 88'  `88 88'  `88    88   88   88 88ooood8   88   88'  `88 88'  `88 88'  `88 Y8ooooo. 
 * Y8.   .88 88.  .88 88 88.  .88 88          88   88   88 88.  ...   88   88    88 88.  .88 88.  .88       88 
 *  Y88888P' `88888P' dP `88888P' dP          dP   dP   dP `88888P'   dP   dP    dP `88888P' `88888P8 `88888P' 
 * oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

/**
 * Creates a Color object
 * @param fg color code for the foreground
 * @param bg color code for the background
 */
Term::Color::Color(const unsigned short &fg, const unsigned short &bg)
{
    this->fg = fg;
    this->bg = bg;
}

/* ██╗ ██████╗     ███╗   ███╗███████╗████████╗██╗  ██╗ ██████╗ ██████╗ ███████╗
 * ██║██╔═══██╗    ████╗ ████║██╔════╝╚══██╔══╝██║  ██║██╔═══██╗██╔══██╗██╔════╝
 * ██║██║   ██║    ██╔████╔██║█████╗     ██║   ███████║██║   ██║██║  ██║███████╗
 * ██║██║   ██║    ██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║   ██║██║  ██║╚════██║
 * ██║╚██████╔╝    ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝██████╔╝███████║
 * ╚═╝ ╚═════╝     ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝
 * ANSI Shadow font
 * http://patorjk.com/software/taag/
 */

Term::IO::IO()
{
#if defined(WINDOWS)
    windows_setup = false;
    wide = true;
    wout = &wcout;
#else
    wide = false;
    out = &cout;
#endif
}

/* dP                               dP      8888ba.88ba             dP   dP                      dP          
 * 88                               88      88  `8b  `8b            88   88                      88          
 * 88 88d888b.  88d888b. dP    dP d8888P    88   88   88 .d8888b. d8888P 88d888b. .d8888b. .d888b88 .d8888b. 
 * 88 88'  `88  88'  `88 88    88   88      88   88   88 88ooood8   88   88'  `88 88'  `88 88'  `88 Y8ooooo. 
 * 88 88    88  88.  .88 88.  .88   88      88   88   88 88.  ...   88   88    88 88.  .88 88.  .88       88 
 * dP dP    dP  88Y888P' `88888P'   dP      dP   dP   dP `88888P'   dP   dP    dP `88888P' `88888P8 `88888P' 
 * oooooooooooo~88~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 *              dP                                                                                           
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

/**
 * Gets a single character from stdin.
 * Input is unbuffered, echoless, blocking. For non-blocking, use a
 * separate thread.
 * @param ch_var the variable to read a character into
 * @return this object (for chaining inputs)
 */
Term::IO &Term::IO::operator>>(char &ch_var)
{
#if defined(WINDOWS)
    // Setup Windows if we haven't yet.
    if (!windows_setup)
        setupWindows();

    // Keeps track of the console mode we started with
    DWORD mode;
    // Get the current mode so we can restore it later
    GetConsoleMode(stdin_terminal, &mode);
    // Set the console mode to unbuffered and echoless
    SetConsoleMode(stdin_terminal, 0);

    ch_var = std::cin.get();

    // Restore the original console mode
    SetConsoleMode(stdin_terminal, mode);
#else
    // turn off echo and get the input without a buffer
    system("stty -brkint -ignpar -istrip -icrnl -ixon -opost -isig -icanon -echo");
    // get the next stdin character
    //key = getchar();
    std::cin >> ch_var;
    // set the terminal back to buffered input and echo
    system("stty cooked echo");
#endif
    return *this;
}

/*  .88888.             dP                        dP      8888ba.88ba             dP   dP                      dP          
 * d8'   `8b            88                        88      88  `8b  `8b            88   88                      88          
 * 88     88 dP    dP d8888P  88d888b. dP    dP d8888P    88   88   88 .d8888b. d8888P 88d888b. .d8888b. .d888b88 .d8888b. 
 * 88     88 88    88   88    88'  `88 88    88   88      88   88   88 88ooood8   88   88'  `88 88'  `88 88'  `88 Y8ooooo. 
 * Y8.   .8P 88.  .88   88    88.  .88 88.  .88   88      88   88   88 88.  ...   88   88    88 88.  .88 88.  .88       88 
 *  `8888P'  `88888P'   dP    88Y888P' `88888P'   dP      dP   dP   dP `88888P'   dP   dP    dP `88888P' `88888P8 `88888P' 
 * oooooooooooooooooooooooooo~88~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 *                            dP                                                                                           
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

/**
 * Prints a string to the terminal and interprets any color codes found
 * @param text the string to print to the terminal
 * @return a reference to this IO object, to account for chained outputs
 */
Term::IO &Term::IO::operator<<(string text)
{
#if defined(WINDOWS)
    // Setup Windows if we haven't yet.
    if (!windows_setup)
        setupWindows();
#endif

    // Reset the color on every new line, easiest way to do this is just to
    // replace every '\n' with '&00\n' (using the Termio color escapes)
    text = replace_all(text, "\n", "&00\n");

    // Replace every instance of "&&" with, where X represents an
    // invisible non-printable, "&X". We will later ignore X when printing
    text = replace_all(text, "&&", '&' + string(1, char(0)));

    // Split the string by "&XY" with X and Y as numeric color codes
    vector<string>
        strings = rsplit(text, "&[0-8][0-8]", true);

    // Print each line of the vector
    for (int i = 0; i < strings.size(); i++)
    {
        // Now that we've finished searching for escapes, we want the "&X"'s
        // to become just plain '&'.
        strings[i] = replace_all(strings[i], "&" + string(1, char(0)), string(1, '&'));

        // Set the color based on the first 3 characters of each substring
        // (Make sure the substring contains a color code, it may be "")
        if (strings[i].size() > 3 && i > 0)
        {
            set_color(Color(strings[i][1] - '0', strings[i][2] - '0'));
        }

        // Print the line, using either a wide or narrow stream
        if (wide)
        {
            // Strings too small to contain a color code OR
            // the first string in the vector (which can't contain a color code
            // or it would have split into the second) should be printed in
            // their entirety, other strings we need to skip the first 3 chars
            // which are the color code.
            if (strings[i].size() > 3 && i > 0)
                *wout << strings[i].substr(3);
            else
                *wout << strings[i];
        }
        else
        {
            // Strings too small to contain a color code OR
            // the first string in the vector (which can't contain a color code
            // or it would have split into the second) should be printed in
            // their entirety, other strings we need to skip the first 3 chars
            // which are the color code.
            if (strings[i].size() > 3 && i > 0)
                *out << strings[i].substr(3);
            else
                *out << strings[i];
        }

        set_color(Color(0, 0));
    }

    // Return this IO object (for any chained outputs)
    return *this;
}

/**
 * Prints a character to the terminal
 * @param letter the character to print to the terminal
 * @return a reference to this IO object, to account for chained outputs
 */
Term::IO &Term::IO::operator<<(const char &letter)
{
#if defined(WINDOWS)
    // Setup Windows if we haven't yet.
    if (!windows_setup)
        setupWindows();
#endif

    if (wide)
    {
        *wout << letter;
    }
    else
    {
        *out << letter;
    }
    return *this;
}

/**
 * Prints an integer to the terminal
 * @param number the integer to print to the terminal
 * @return a reference to this IO object, to account for chained outputs
 */
Term::IO &Term::IO::operator<<(const int &number)
{
#if defined(WINDOWS)
    // Setup Windows if we haven't yet.
    if (!windows_setup)
        setupWindows();
#endif

    if (wide)
    {
        *wout << number;
    }
    else
    {
        *out << number;
    }
    return *this;
}

/**
 * Prints a double to the terminal
 * @param number the double to print to the terminal
 * @return a reference to this IO object, to account for chained outputs
 */
Term::IO &Term::IO::operator<<(const double &number)
{
#if defined(WINDOWS)
    // Setup Windows if we haven't yet.
    if (!windows_setup)
        setupWindows();
#endif

    if (wide)
    {
        *wout << number;
    }
    else
    {
        *out << number;
    }
    return *this;
}

/* .d88888b                              oo          dP    8888ba.88ba             dP   dP                      dP          
 * 88.    "'                                         88    88  `8b  `8b            88   88                      88          
 * `Y88888b.  88d888b. .d8888b. .d8888b. dP .d8888b. 88    88   88   88 .d8888b. d8888P 88d888b. .d8888b. .d888b88 .d8888b. 
 *       `8b  88'  `88 88ooood8 88'  `"" 88 88'  `88 88    88   88   88 88ooood8   88   88'  `88 88'  `88 88'  `88 Y8ooooo. 
 * d8'   .8P  88.  .88 88.  ... 88.  ... 88 88.  .88 88    88   88   88 88.  ...   88   88    88 88.  .88 88.  .88       88 
 *  Y88888P   88Y888P' `88888P' `88888P' dP `88888P8 dP    dP   dP   dP `88888P'   dP   dP    dP `88888P' `88888P8 `88888P' 
 * oooooooooo~88~ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 *            dP                                                                                                            
 * Nancyj-Underlined font
 * http://patorjk.com/software/taag/
 */

/**
 * Moves the terminal's cursor to a row/column specified by
 * a Point object.
 * @param point the Point containing the row/column to move to
 * @return this object, for chaining outputs.
 */
Term::IO &Term::IO::operator<<(const Point &point)
{
#if defined(WINDOWS)
    if (!windows_setup)
    {
        setupWindows();
    }
    // if using Windows, use windows.h
    // We must have a reference to the active terminal for Windows
    // Coordinates are (x, y). Columns are x, rows are y, so r/c becomes c/r
    COORD cor = {(short)point.col, (short)point.row};
    SetConsoleCursorPosition(stdout_terminal, cor);
#else
    // for some reason, row and column in ANSI start at 1, we want it to start at 0
    int r = point.row + 1;
    int c = point.col + 1;
    // on *nix use ANSI escape
    std::string pos = "\033[" + std::to_string(r) + ';' + std::to_string(c) + 'f';
    std::cout << pos;
#endif
    return *this;
}

/**
 * Changes the color of the terminal to the foreground and
 * background specified by the Color object.
 * @param color a Color object containing a foreground and background code
 * (codes are specified in Termio.h near the top of the file)
 * @return this object, for chaining outputs.
 */
Term::IO &Term::IO::operator<<(const Color &color)
{
    set_color(color);
    return *this;
}

/**
 * Executes a command object.
 * @param command the command to use .call() on.
 * @return this object, for chaining outputs.
 */
Term::IO &Term::IO::operator<<(Command &command)
{
    command.call();
    return *this;
}

void Term::IO::set_color(Color c)
{
#if defined(WINDOWS)
    static const unsigned short _fg[] = {7, 0, 4, 6, 2, 1, 3, 5, 7};
    static const unsigned short _bg[] = {0, 0, 64, 96, 32, 16, 48, 80, 112};
#else
    static const unsigned short _fg[] = {39, 30, 31, 33, 32, 34, 36, 35, 37};
    static const unsigned short _bg[] = {49, 40, 41, 43, 42, 44, 46, 45, 47};
#endif

#if defined(WINDOWS)
    if (!windows_setup)
        setupWindows();
    SetConsoleTextAttribute(stdout_terminal, _fg[c.fg] + _bg[c.bg]);
#else
    if (wide)
    {
        *wout << "\033[" + to_string(_fg[c.fg]) + to_string(_bg[c.bg]) + 'm';
    }
    else
    {
        *out << "\033[" + to_string(_fg[c.fg]) + ';' + to_string(_bg[c.bg]) + 'm';
    }
#endif
}

#if defined(WINDOWS)
void Term::IO::setupWindows()
{
    // If we're using windows and it has not yet been fixed
    if (!windows_setup)
    {
        // set the console mode for unicode
        _setmode(_fileno(stdout), _O_U16TEXT);
        // We must have a reference to the input terminal for Windows' input API
        stdin_terminal = GetStdHandle(STD_INPUT_HANDLE);
        // We must have a reference to the output terminal for Windows' color API
        stdout_terminal = GetStdHandle(STD_OUTPUT_HANDLE);
        // Mark the Windows fix as complete
        windows_setup = true;
    }
}
#endif