#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random

""" Example 03 - Moving the ball

    1) Let's change where the circle is drawn by giving it a random
       starting position,
    2) Then moving it in some random direction,
    3) Changing it's direction if it hits a wall
    4) And finally we use a function to get the new coords for the ball.

PROBLEM:
    This ball goes off the screen on both sides!! Can you fix the problem?

ALSO:
    The ball can be sped up using the "pace" or number of pixels moved each game
    loop, or by decreasing the number that counter is modded by.
"""

pygame.init()

width = 500         # width of overall screen
height = 500        # same but height
running = True      # Run until the user asks to quit
count = 0           # loop counter
x = width // 2      # center using // (integer divide)
y = height // 2     # center using // (integer divide)
x = 50
y = 100
dx = 1
dy = 1
modded = 1         # print ball when this val divides even
pace = 15            # pixels to move ball each game loop


def moveBall(x, y, dx, dy, pace=3):
    """
    Description: moveBall - returns coords and the direction (-dx is left and -dy is up) of the ball. 
    Params:
        x  [int] : x coordinate
        y  [int] : y coordinate
        dx [int] : x direction (-1 is left, 1 is right)
        dy [int] : y direction (-1 is up, 1 is down)
        pace [int] : how many spaces to move each game loop
    """

    x = x + (pace * dx)         # add pace * direction to current x
    y = y + (pace * dy)         # add pace * direction to current y

    if y <= 0:                  # if y off screen top reverse direction
        dy *= -1
    elif y >= height:           # if y off screen bottom reverse direction
        dy *= -1

    if x <= 0:                  # if x off screen left reverse direction
            dx *= -1
    elif x >= height:           # if x off screen right reverse direction
        dx *= -1

    return (x, y, dx, dy)       # return 4 values! (Try that c++!)


# Set up the drawing window
screen = pygame.display.set_mode([width, height])

red = random.randint(0, 255)
green = random.randint(0, 255)
blue = random.randint(0, 255)

while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))

    #if count % modded == 0:
    x, y, dx, dy = moveBall(x, y, dx, dy, pace)
    
    #count = 0

    # Draw a solid blue circle in the center
    pygame.draw.circle(screen, (red, green, blue), (x, y), 75)

    # Flip the display
    pygame.display.flip()

    # increment our counter
    count += 1

# Done! Time to quit.
pygame.quit()
