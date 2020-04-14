#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random
import sys
import math

""" Example 08 - Still moving ball(s) (using a ball class). 
    - This example shows simple "collision" detection and changes
      the direction of each ball. Since the balls have the same mass
      we can simple "swap" their velocities to make them "bounce" off
      each other.

      It's not perfect (and were still not using PyGames built in methods
      even though I should be). 

      Balls going in similar directions, don't react or change direction
      correctly. I'm using "very" basic collsion detection here.

      We are not taking into account mass, or angle of impact, or 
      differing velocites because this isn't a game class :)

"""

class GameBall(object):
    def __init__(self, id,pace=1, size=20, width=500, height=500,buffer=10):
        """ Constructor
            This method creates a ball with params that are pre-picked for now to
            keep it simple. 
        """
        self.id = id
        # The only 2 customizable params (for now)
        self.width = width      # width of game window
        self.height = height    # height of game window

        # Pre picked values for our ball to keep the class simple
        self.pace = pace           # pace = pixels per game loop
        self.size = size          # size = size of ball
        self.red = 0            # All balls init to black (for now)
        self.green = 0
        self.blue = 0
        self.buffer = buffer    # A buffer (gutter) or padding from
                                # window edge

        # xy coords are randomly picked based on game window size
        self.x = int(random.random() * self.width )     # random x and y (for now)
        self.y = int(random.random() * self.height )    # random x and y (for now)

        # make sure ball spawns away from edge of window
        if self.x < self.buffer:
            self.x += self.buffer
        
        if self.x > self.width - self.buffer:
            self.x -= self.buffer

        if self.y < self.buffer:
            self.y += self.buffer
        
        if self.y > self.height - self.buffer:
            self.y -= self.buffer

        # list (array) of directions (forward,backward) :) 
        direction = [1,-1]

        # shuffle the direction list (random order) then assign to dx and dy
        random.shuffle(direction)
        self.dx = direction[0]      # pick of first element 
        random.shuffle(direction)
        self.dy = direction[0]      # same

        self.collided = False

        
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

    def collide(self,other):
        """ collide - Check to see if two balls "collide" or touch and gives them the same random color
        """
        # if the ball id's are the same, don't make them collide!
        if self.id == other.id:
            return
        
        # If we find that the position of 2 balls is within the size of each ball, then they have collided.
        # We then change color, and should probable change direction of the as well, but thats next!
        if abs(abs(self.x) - abs(other.x)) <= self.size and abs(abs(self.y) - abs(other.y)) <= int(self.size*2):

                tempdx = self.dx        # hold x direction of self 
                tempdy = self.dy        # hold y direction of self

                self.dx = other.dx      # take others x direction
                self.dy = other.dy      # take others y direction

                other.dx = tempdx       # other gets self's x direction
                other.dy = tempdy       # other gets self's y direction
                
                # create a list of random colors
                colors = [int(random.random()*255),int(random.random()*255),int(random.random()*255)]

                # shuffle the random colors (unnessary) :) But wanted to show shuffle method
                random.shuffle(colors)

                # assign same color to each ball that collides
                self.red = colors[0]
                other.red = colors[0]
                self.green = colors[1]
                other.green = colors[1]
                self.blue = colors[2]
                other.blue = colors[2]

            
#############################################################################################

if __name__=='__main__':

    max_balls = 8
    if len(sys.argv) > 1:
        max_balls = int(sys.argv[1])

    pygame.init()

    width = 500         # width of overall screen
    height = 500        # same but height
    running = True      # Run until the user asks to quit
    max_pace = 15
    min_pace = 5

    # Set up the drawing window
    screen = pygame.display.set_mode([width, height])

    balls = []  # empty list of balls so we can print many of them

    # loop "max_balls" number of times and create that many new balls
    for i in range(max_balls):
        balls.append(GameBall(i))    # append is like a "push"

        # Python doesn't have "private" members. So below we can:
        # 1) use the [-1] to get the "last" item in the list
        # 2) access the "pace" for that ball using the "dot" operator

        balls[-1].pace = int(random.random() * (max_pace-min_pace)) + min_pace # give each ball different speed

    while running:

        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Fill the background with white
        # This also helps "clear" the screen everytime
        screen.fill((255, 255, 255))

        # set each balls collided var to false for this game loop
        for b in balls:
            b.collided = False

        # loop through list of balls
        for i in range(len(balls)):

            # another inner loop to see if balls are colliding
            for j in range(len(balls)):
                # if collided this game loop, skip checking
                if i==j or balls[i].collided == True or balls[j].collided == True:
                    continue
                # run check for collision method
                balls[i].collide(balls[j])

            # move the current ball
            balls[i].move()

            # draw the current ball
            pygame.draw.circle(screen, (balls[i].red, balls[i].green, balls[i].blue), (balls[i].x, balls[i].y), balls[i].size)

        # Flip the display
        pygame.display.flip()


    # Done! Time to quit.
    pygame.quit()
