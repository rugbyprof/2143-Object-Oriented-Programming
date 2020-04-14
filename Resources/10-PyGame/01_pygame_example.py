#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random

"""
Pygame hello world: Print a circle in middle of screen.
"""


pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([500, 500])

# Run until the user asks to quit
running = True

while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))

    red = 0
    green = 0
    blue = 255


    # Draw a solid blue circle in the center
    pygame.draw.circle(screen, (red, green, blue), (250, 250), 75)

    # Flip the display
    pygame.display.flip()


# Done! Time to quit.
pygame.quit()
