Yes, you can register KEY_MOUSE as a key in the InputHandler to handle mouse events. However, there are a few additional considerations when dealing with ncurses mouse input compared to regular key input.

The main difference is that when getch() detects KEY_MOUSE, you’ll need to call getmouse(&event) to retrieve details of the mouse event, such as the x and y coordinates and the button state. This adds an extra layer to mouse handling but can still be integrated cleanly into the InputHandler.

Here’s how to modify InputHandler to register KEY_MOUSE and capture mouse events:

Step 1: Register KEY_MOUSE with a Callback that Accepts MEVENT

We’ll make InputHandler flexible enough to register a callback for KEY_MOUSE, which takes an MEVENT parameter. This way, you can directly handle mouse clicks or movements with the registered function.

Updated InputHandler Class

#include <iostream>
#include <map>
#include <functional>
#include <ncurses.h>
#include <any>
#include <typeinfo>
#include <stdexcept>

class InputHandler {
public:
// Register a callback with an int key (e.g., KEY_MOUSE or other key)
template <typename Func>
static void register_key(int key, Func callback) {
key_actions[key] = callback;
}

    // Handle keyboard or mouse input; special handling for KEY_MOUSE
    template <typename... Args>
    static auto handle_input(int key, Args... args) -> decltype(std::declval<std::function<void(Args...)>>()(args...)) {
        auto it = key_actions.find(key);
        if (it != key_actions.end()) {
            // Cast std::any to the expected function type and call it
            auto& callback_any = it->second;
            using CallbackType = std::function<void(Args...)>;

            if (callback_any.type() == typeid(CallbackType)) {
                auto& callback = std::any_cast<CallbackType&>(callback_any);
                return callback(args...);
            } else {
                throw std::runtime_error("Callback parameter types do not match!");
            }
        } else {
            throw std::runtime_error("No callback registered for key!");
        }
    }

private:
// Store callbacks as std::any to allow multiple function signatures
static std::map<int, std::any> key_actions;
};

// Define the static map outside the class
std::map<int, std::any> InputHandler::key_actions;

Step 2: Register a Callback for KEY_MOUSE

In your main code, you can register a callback for KEY_MOUSE that takes an MEVENT parameter. This callback can handle the mouse event details, such as checking which button was clicked and retrieving the coordinates.

void handle_mouse_event(const MEVENT& event) {
if (event.bstate & BUTTON1_CLICKED) {
std::cout << "Mouse clicked at (" << event.x << ", " << event.y << ")" << std::endl;
}
// Additional mouse handling logic
}

Step 3: Integrate handle_input to Process Mouse Events

In the main game loop, you can check for KEY_MOUSE and call getmouse(&event) to get the mouse details. Then pass the MEVENT struct to handle_input.

int main() {
initscr();
keypad(stdscr, TRUE);
mousemask(ALL_MOUSE_EVENTS, NULL); // Enable all mouse events
noecho();
curs_set(0);

    // Register the mouse handler with KEY_MOUSE
    InputHandler::register_key(KEY_MOUSE, handle_mouse_event);

    MEVENT event;
    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                // Pass the mouse event to the InputHandler
                try {
                    InputHandler::handle_input(KEY_MOUSE, event);
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        } else {
            // Handle other keys (non-mouse keys) here if needed
        }
    }

    endwin();
    return 0;

}

Explanation

    1.	Registering KEY_MOUSE: We register KEY_MOUSE with a callback (handle_mouse_event) that accepts an MEVENT argument.
    2.	Calling getmouse(&event): Inside the main loop, we detect KEY_MOUSE and then call getmouse(&event) to capture the mouse details.
    3.	Passing MEVENT to handle_input: We pass KEY_MOUSE and event to handle_input, which routes the event to the appropriate callback.

Summary

This setup allows InputHandler to handle both keyboard and mouse events cleanly:
• For Keyboard Events: Use regular int arguments for keys and define callbacks without parameters.
• For Mouse Events: Register KEY_MOUSE with callbacks that take an MEVENT argument, allowing you to capture details like x, y coordinates and button state.

By structuring InputHandler this way, you’re able to capture both types of events seamlessly and avoid clutter in the main game loop.
