#!/usr/bin/env python3

"""
Some basic incomplete classes just for ideas
"""

# Import and initialize the pygame library
import pygame
import random

#______________________________________________________________________________
class Config:
    screen_width = 640
    screen_height = 480
    population_size = 100
    neighborhoods = 4


#______________________________________________________________________________
class SIRmodel(object):

    sir_stages = ["susceptible","infected","recovered"] # names of stages
    contagious_period = range(2,15)                     # days you are contagious (while infected)
    probability_infected = .20                          # probability you infect someone

    # just as an example not going to use
    @staticmethod
    def getInitialStage():
        return SIRmodel.sir_stages[0]

    @staticmethod
    def getCantagiousPeriod():
        return random.choice(SIRmodel.contagious_period)


#______________________________________________________________________________
class NeighborHood(object):
    def __init__(self,screen_width,screen_height,width,height):
        self.people = []                    # people belonging to neighborhood
        self.screen_width = screen_width    # width of world
        self.screen_height = screen_height  # height of world
        self.width = width                  # width of neighborhood
        self.height = height                # height of neighborhood
        self.base_x = 0                     # top left x,y of neighborhood
        self.base_y = 0

    def addPerson(self,person):
        """Add a person to the neighborhood
        """
        pass

    def movePeople(self):
        """Call the move method for each person
        """
        pass

#______________________________________________________________________________
class Population(object):
    def __init__(self):
        self.total_people = 0
        self.neighborhoods = []

    
    def getNumInfected(self):
        pass

    def getNumSusceptible(self):
        pass

    def getNumRecovered(self):
        pass

#______________________________________________________________________________
class Person(pygame.sprite.Sprite):
    """
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
        self.home = [0,0]
        self.range = 100

    def goHome(self):
        pass

    def goTravel(self,distance):
        pass



if __name__=='__main__':
    SIRmodel.probability_infected = .3

    print(SIRmodel.getCantagiousPeriod())

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
