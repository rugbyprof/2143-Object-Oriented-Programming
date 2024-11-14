In ncurses, refresh() and clear() serve different purposes, and understanding when to use each will help you control the display more effectively.

1. refresh()

   • Purpose: refresh() updates the terminal to reflect any changes made since the last screen update.
   • When to Call: Call refresh() whenever you want to apply the changes you’ve made to the screen and make them visible to the user. It’s typically called once per frame in a game loop to “commit” the current frame’s content.
   • Effect: refresh() applies changes but does not clear any content. It’s like “pushing” the current state of the screen to the display.

Example Usage of refresh()

// Modify content on the screen
mvprintw(10, 10, "Hello, world!");
// Make the changes visible
refresh();

    •	In this example, without refresh(), the “Hello, world!” text would be added to the ncurses buffer but wouldn’t actually show on the terminal until refresh() is called.

2. clear()

   • Purpose: clear() wipes the entire screen buffer by filling it with blank spaces.
   • When to Call: Use clear() when you want to remove all existing content on the screen before drawing a new frame from scratch. This is particularly useful in animations or games, where each frame may have significantly different content.
   • Effect: clear() erases the screen content and leaves it blank. After calling clear(), you need to call refresh() to make the cleared screen visible to the user.

Example Usage of clear()

clear(); // Wipe the screen
mvprintw(5, 5, "Fresh frame"); // Add new content
refresh(); // Display the new content

Typical Use in a Game Loop

In most games, each frame is completely redrawn, so the common pattern is to call clear() at the beginning of each frame, followed by rendering all elements, and then calling refresh() to display the new frame.

while (true) {
clear(); // Clear the previous frame

    // Draw updated game state (e.g., characters, score, etc.)
    mvprintw(10, 10, "Game content here");

    refresh();  // Show the updated frame

    // Handle input, update game state, etc.

}

When to Skip clear()

If your updates only affect part of the screen, and you want to keep the rest of the screen unchanged, you can skip clear() and only use refresh(). This approach can improve performance by reducing unnecessary redraws.

For example, a scoreboard in the corner of the screen that updates independently of the main game content would only require refresh() when the score changes, without calling clear() and redrawing the entire screen.

// Update only the scoreboard without clearing the whole screen
mvprintw(0, 0, "Score: %d", score);
refresh();

Summary

    •	Use refresh() to apply updates to the screen and make changes visible.
    •	Use clear() followed by refresh() when you want a clean slate for each frame, commonly in animations or game loops.
    •	Skip clear() if you only need to update a portion of the screen to keep the display efficient.

By combining these thoughtfully, you’ll have smooth and efficient control over the ncurses display!
