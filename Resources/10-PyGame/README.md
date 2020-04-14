## Resources 10-PyGame - Pygame Examples

Just some pygame examples bouncing a ball around so far...

These examples are a "python" intro with a little bit of "pygame" as well. 

Basically Eevery "game" has a game loop (no matter the language), and everything
gets updated there: 

```python
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    # This also helps "clear" the screen everytime
    screen.fill((255, 255, 255))

    # DO STUFF HERE

    # Flip the display = redraw screen / update everyones position
    pygame.display.flip()
```

All events happen in the middle of this "game loop". Pygame gives us methods to continuously redraw the screen as we update individual locations or attributes of objects (aka sprites which we will talk about later). So moving a ball, or changing its color, or looking for collisions all happen in this game loop.

Go through the pygame example files and see the progression from simple shape in [01_pygame_example.py](./01_pygame_example.py) to actual movement using a "ball" class and some crappy collision detection in [08_pygame_example.py](./08_pygame_example.py). I will post better "pygame" examples, as well as covide19 insight next.