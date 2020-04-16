#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random
from quadtree import QuadTree

class Config:
    screen_width = 640
    screen_height = 480
    population_size = 100
    neighborhoods = 4

class SIRmodel(object):

    sir_stages = ["susceptible","infected","recovered"] # names of stages
    contagious_period = [2,14]                      # days you are contagious (while infected)
    probability_infected = .20                      # probability you infect someone

    # just as an example not going to use
    @staticmethod
    def getInitialStage():
        return sir_stages[0]

    

class NeighborHood(object):
    def __init__(self,screen_width,screen_height):
        self.people = []



class Population(object):
    def __init__(self):
        self.total_people = 0
        self.neighborhoods = []

class Person(pygame.sprite.Sprite):
    """
    This class represents the ball.
    It derives from the "Sprite" class in Pygame
    """
    def __init__(self, color, size=15,speed=2):
        """ Constructor: set up our person
        """
        # Call the parent class (Sprite) constructor
        super().__init__()

        self.size = size
        self.speed = speed
        self.image = pygame.image.load(Config.sprite_images[self.color])
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

if __name__=='__main__':
    SIRmodel.probability_infected = .3

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
