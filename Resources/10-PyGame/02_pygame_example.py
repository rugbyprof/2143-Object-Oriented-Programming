#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random

"""
This version simply changes the color of the ball using the
random library in python.
"""


pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([500, 500])

# Run until the user asks to quit
running = True
count = 0
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))

    # Change the color of the ball randomly 
    # we slow down the change rate by creating a counter  
    # and modding by some value (1000 in this case)
    # otherwise it will change too fast
    if count % 100 == 0:
        red = random.randint(0, 255)
        green = random.randint(0, 255)
        blue = random.randint(0, 255)

        # set counter to zero so it doesn't grow to super large
        count = 0

    # Draw a solid blue circle in the center
    pygame.draw.circle(screen, (red, green, blue), (250, 250), 75)

    # Flip the display
    pygame.display.flip()

    # increment our counter
    count += 1

# Done! Time to quit.
pygame.quit()
