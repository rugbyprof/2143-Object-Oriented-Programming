
# Import and initialize the pygame library
import pygame
import random

""" Example 07 - Still moving ball(s) using a class. 
    This class has many more setters/getters and will know about pygame
"""


class GameBall():
    def __init__(self, pygame, screen, width, height):
        
        self.pygame = pygame
        self.screen = screen

        self.x = 0              # current location x coord
        self.y = 0              # current location y coord
        self.dx = 1             # current x direction
        self.dy = 1             # curernt y direction
        self.pace = 1           # pace = pixels per game loop
        self.size = 10          # size = size of ball
        self.width = width      # width of game window
        self.height = height    # height of game window

        self.red  = random.randint(0, 255)
        self.green=   random.randint(0, 255)
        self.blue =  random.randint(0, 255)

    
    def windowSize(self,w,h):
        """windowSize - set window width and height for pygame
        Params:
            w [int] : width of pygame window
            h [int] : height of pygame window
        """

        self.width = w
        self.height = h

    def randLoc(self):
        """randLoc - Set ball to a random location
        """

        self.x = int(random.random() * self.width)
        self.y = int(random.random() * self.height)

    
    def setLoc(self,x,y):
        """ 
        Description: jumpTo - basically totally resets the balls location jumping
                              it to whatever x,y. Not based on current location
                              and direction.
        Params:
            x [int] : x coord
            y [int] : y coord
        """
        self.x = x
        self.y = y


    def updateLoc(self):
        """
        Description: move - updates a balls location based on current 
                            position and current direction
        Params:
            None
        """

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

        self.pygame.draw.circle(self.screen, (self.red, self.green, self.blue), (self.x, self.y), self.size)

    def setWidth(self,w):
        """ setWidth - give ball class width of game window
        """
        self.width = w


    def setHeight(self,h):
        """ setheight - give ball class height of game window
        """
        self.height = h


#########################################################################################################

width = 500         # width of overall screen
height = 500        # same but height
max_balls = 25
max_pace = 15

pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([width, height])

running = True      # Run until the user asks to quit

balls = []

for i in range(max_balls):
    b = GameBall()

    rand_pace = int(random.random() * max_pace) 

    b.pace = rand_pace
    b.randLoc()

    balls.append(GameBall())    # append is like a "push"


while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))

    # if count % modded == 0:
    x, y, dx, dy = moveBall(x, y, dx, dy, ob_size, pace)
    
    # count = 0

    # Draw a solid blue circle in the center
    pygame.draw.circle(screen, (red, green, blue), (x, y), ob_size)

    # Flip the display
    pygame.display.flip()

    # increment our counter
    count += 1

# Done! Time to quit.
pygame.quit()
