#!/usr/bin/env python3
"""
This adds on to the previous example. 
We still have most of the config as globals at top of file. 

I change images and image sizes to more appropriate for a sim.

Added a pseudo SIR model, or really an example on how to pre-populate a sim
based on ratios. It needs to be in a class, and in this file I have some 
MAJOR issues (like it always creates a list of 100 values). But those are 
easily changed. 
"""
import pygame
import sys
import random

# Global Values 
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
SPRITE_SIZE = 15
SPRITE_BASE_SPEED = 2

# SIR MODEL 
SUSCEPTIBLE_PROB = .80
INFECTED_PROB = .10
RECOVERED_PROB = .10

# Image Constants
SUSCEPTIBLE_IMAGE = './images/pac_white_30x30.png'
CONTAGIOUSL_IMAGE = './images/pac_yellow_30x30.png'
INFECTED_IMAGE = './images/pac_red_30x30.png'
RECOVERING_IMAGE = './images/pac_yellow_30x30.png'
RECOVERED_IMAGE = './images/pac_yellow_30x30.png'

# direction lists (or arrays if you like)
# -1 = move left  or up
#  1 = move right or down
XDirection = [-1,1]
YDirection = [-1,1]

# Status List
SIR = []

# Adjust Percentages for each phase
S = ["S"] * int(SUSCEPTIBLE_PROB * 100) # repeat "S" for probability num times
I = ["I"] * int(INFECTED_PROB * 100)    # repeat "I" for probability num times
R = ["R"] * int(RECOVERED_PROB * 100)   # repeat "R" for probability num times

# Append each into single list of 100 items where each probability adds
# up to 100 items (ex: S=80 occurences, I=10 occurences, and R=10 occurences)
SIR = S + I + R

# Shuffle the array so we choose items randomly from it.
random.shuffle(SIR)

class Person(pygame.sprite.Sprite):
    """Person : Inherits from pygame Sprite
    """
    def __init__(self, pos, SIR="S",im_size=15):
        super().__init__()

        self.im_size = im_size

        if SIR == "S":
            self.image = pygame.image.load(SUSCEPTIBLE_IMAGE)  # use susceptible image for sprite
        elif SIR == "I":
            self.image = pygame.image.load(INFECTED_IMAGE)  # use infected image for sprite
        else:
            self.image = pygame.image.load(RECOVERED_IMAGE)  # use recovered image for sprite

        # scale the image based on class input
        self.image = pygame.transform.scale(self.image, (self.im_size, self.im_size))

        # set up base variables for sprite class
        self.size = SPRITE_SIZE                             # size of sprite :) 
        self.width = SCREEN_WIDTH                           # game board width
        self.height = SCREEN_HEIGHT                         # game board height
        self.rect = self.image.get_rect(center=pos)         # kinda the "sprite" container
        
        self.dx = 0                                         # x direction 
        self.dy = 0                                         # y direction
        self.sir = SIR                                      # Which phase from model? S / I / R

        # give each person a little different speed
        self.speed = 1 + int(random.random() * SPRITE_BASE_SPEED)              


    def dir_x(self,x):
        """Set the x direction for the person (east/west). Invoke using the move method.
        """
        self.dx += x

    def dir_y(self,y):
        """Set the y direction for the person (east/west). Invoke using the move method.
        """
        self.dy += y

    def move (self,dx=None,dy=None):
        """Invoke to move a person in any cardinal direction by re-setting dx and/or dy.
        """
        self.stop_leaving_world()

        if dx != None:
            self.dx = dx
            
        self.rect.x += (self.dx * self.speed)

        if dy != None:
            self.dy = dy
            
        self.rect.y += (self.dy * self.speed)
    
    def stop_leaving_world(self):
        """ This method checks if a sprites x,y coordinates are off the game board.
            If they are below 0, we make them 1 and if they are greater than the 
            width or the height, we make them (width/height - sprite.size).
            Also, if sprite goes off game board, we reverse the direction of the sprite. 
        """

        if self.rect.y <= 0:                               # if y off screen top reverse direction
            self.dy *= -1
            self.rect.y = 1
        elif self.rect.y >= self.height - self.size:       # if y off screen bottom reverse direction
            self.dy *= -1
            self.rect.y = self.height - self.size

        if self.rect.x <= 0:                               # if x off screen left reverse direction
            self.dx *= -1
            self.rect.x = 1
        elif self.rect.x >= self.width - self.size:        # if x off screen right reverse direction
            self.dx *= -1
            self.rect.x = self.width - self.size

def main():
    if len(sys.argv)  > 1:
        try:
            num_people = sys.argv[1] + 1
        except TypeError:
            print("Error: Parameter should have been an integer.")
    else:
        num_people = 20

    # Initialize PyGame
    pygame.init()

    # Get a reference to the screen
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

    # Not Sure :) 
    clock = pygame.time.Clock()

    # Create a Pygame Group
    # A group allows minipulation to the entire group OR
    # manipulating one member at a time. Nice to have the option
    population = pygame.sprite.Group()

    # Set up 20 "people" and place them at random locations on the screen
    for i in range(num_people):
        # pick a random position
        posx = int(random.random()*SCREEN_WIDTH - int(SPRITE_SIZE/2))
        posy = int(random.random()*SCREEN_HEIGHT - int(SPRITE_SIZE/2))

        # create a position tuple
        pos = (posx,posy)

        # create a person
        p = Person(pos,SIR[i],SPRITE_SIZE)

        # shuffle the direction arrays
        random.shuffle(XDirection)
        random.shuffle(YDirection)

        # assign xy direction to a person
        p.dir_x(XDirection[0])
        p.dir_y(YDirection[0])

        # add person to the population
        population.add(p)

    # keep looping while we are not done!
    done = False
    
    # Game loop
    while not done:
        # Check for interaction with game window (some event)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

        #population.update()
        
        # for every person "p" call he move method
        for p in population:
            p.move()

        # redraw the screen with r30 g30 b30 (basically almost black)
        screen.fill((30, 30, 30))

        # draw the "population" group onto the "screen"
        population.draw(screen)

        # Draw a rect over the selected sprite.
        #pygame.draw.rect(screen, (255, 128, 0), selected_person.rect, 2)

        pygame.display.flip()
        clock.tick(30)


if __name__ == '__main__':
    main()
    pygame.quit()