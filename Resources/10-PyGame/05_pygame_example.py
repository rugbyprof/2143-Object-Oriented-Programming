#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random

""" Example 05 - Still moving a single ball around, but with a class
    - This example will create a ball class.
    - The class will simply remember the specific information about the "ball".
    - It doesnt know about pygame. 
    - It only knows about the game screen width and height so it can do 
      calculations about the balls location.
"""

class GameBall(object):
    def __init__(self, pace=1, size=10, width=500, height=500):
        """ Constructor
            This method creates a ball with params that are pre-picked for now to
            keep it simple. 
        """
        # The only 2 customizable params (for now)
        self.width = width      # width of game window
        self.height = height    # height of game window

        # Pre picked values for our ball to keep the class simple
        self.pace = 1           # pace = pixels per game loop
        self.size = 10          # size = size of ball
        self.red = 0            # All balls init to black (for now)
        self.green = 0
        self.blue = 0

        # xy coords are randomly picked based on game window size
        self.x = int(random.random() * self.width )     # random x and y (for now)
        self.y = int(random.random() * self.height )    # random x and y (for now)

        # list (array) of directions (forward,backward) :) 
        direction = [1,-1]

        # shuffle the direction list (random order) then assign to dx and dy
        random.shuffle(direction)
        self.dx = direction[0]      # pick of first element 
        random.shuffle(direction)
        self.dy = direction[0]      # same


    def move(self, width=None, height=None):
        """
        Description: move - updates a balls location based on current 
                            position and current direction
        Params:
            width  [int]        : width of window
            height  [int]       : height of window
        """
        # If value passed in, set the class value
        if not width is None:
            self.setWidth(width)

        # Same as above
        if not height is None:
            self.setHeight(height)

        half = int((self.size * 1.6) / 2)           # not perfect, a little guessing
                                                    # with the 1.6 ... 

        self.x = self.x + (self.pace * self.dx)     # add pace * direction to current x
        self.y = self.y + (self.pace * self.dy)     # add pace * direction to current y

        if self.y <= 0 + half:                      # if y off screen top reverse direction
            self.dy *= -1
        elif self.y >= self.height - half:          # if y off screen bottom reverse direction
            self.dy *= -1

        if self.x <= 0 + half:                      # if x off screen left reverse direction
            self.dx *= -1
        elif self.x >= self.height - half:          # if x off screen right reverse direction
            self.dx *= -1

        return (self.x, self.y)   # returns balls new coords


pygame.init()

width = 500         # width of overall screen
height = 500        # same but height
running = True      # Run until the user asks to quit
max_balls = 10


# Set up the drawing window
screen = pygame.display.set_mode([width, height])

b = GameBall() # create a new instance of the GameBall class

# data members in python classes are not private!
# I can change it by using the dot operator
b.pace = 5

while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    # This also helps "clear" the screen everytime
    screen.fill((255, 255, 255))

    # move our ball
    b.move()

    # draw our ball
    pygame.draw.circle(screen, (b.red, b.green, b.blue), (b.x, b.y), b.size)

    # NOTE: Our GameBall class knows nothing about PyGame. PyGame simply prints 
    # a circle, and knows where to print it by getting the current color, position,
    # and size from our GameBall instance => b 

    # Flip the display
    pygame.display.flip()


# Done! Time to quit.
pygame.quit()
