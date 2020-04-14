#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random

""" Example 04 - Still moving

    1) Fix the bounce so its better looking (less off screen)
    2) Starts the ball in a random location
    3) Still randomly colors the ball


"""

pygame.init()

width = 500         # width of overall screen
height = 500        # same but height
running = True      # Run until the user asks to quit
count = 0           # loop counter
x = 0
y = 0
dx = 1
dy = 1
modded = 1         # print ball when this val divides even
pace = 15            # pixels to move ball each game loop
ob_size = 10



def moveBall(x, y, dx, dy, ob_size, pace=3):
    """
    Description: moveBall - returns coords and the direction (-dx is left and -dy is up) of the ball. 
    Params:
        x  [int]        : x coordinate
        y  [int]        : y coordinate
        dx [int]        : x direction (-1 is left, 1 is right)
        dy [int]        : y direction (-1 is up, 1 is down)
        ob_size [int]   : size of object 
        pace [int]      : how many spaces to move each game loop
    """

    half = int((ob_size * 1.6) / 2) # not perfect, a little guessing
                                    # with the 1.6 ... 

    x = x + (pace * dx)         # add pace * direction to current x
    y = y + (pace * dy)         # add pace * direction to current y

    if y <= 0 + half:           # if y off screen top reverse direction
        dy *= -1
    elif y >= height - half:    # if y off screen bottom reverse direction
        dy *= -1

    if x <= 0 + half:           # if x off screen left reverse direction
        dx *= -1
    elif x >= height - half:    # if x off screen right reverse direction
        dx *= -1

    return (x, y, dx, dy)       # return 4 values! (Try that c++!)


# Set up the drawing window
screen = pygame.display.set_mode([width, height])

red = random.randint(0, 255)
green = random.randint(0, 255)
blue = random.randint(0, 255)

x = int(width * random.random())    # faster than random.randint(low,high)
y = int(width * random.random())    # faster than random.randint(low,high)

while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))

    #if count % modded == 0:
    x, y, dx, dy = moveBall(x, y, dx, dy, ob_size, pace)
    
    #count = 0

    # Draw a solid blue circle in the center
    pygame.draw.circle(screen, (red, green, blue), (x, y), ob_size)

    # Flip the display
    pygame.display.flip()

    # increment our counter
    count += 1

# Done! Time to quit.
pygame.quit()
