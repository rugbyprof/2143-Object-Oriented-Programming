#!/usr/bin/env python3

import pygame
import sys
import random
import math

# https://pythonconquerstheuniverse.wordpress.com/2010/10/20/a-globals-class-pattern-for-python/
# A design pattern to handle global variables


class Config:
    """ Config: A design pattern (arguably not a great one) that lets you put configuration information
        into an easily accessible container that treats each class level variable kindof like a global! 
    """

    # Notice there is no constructor (__init__) method.
    # Everything is a class level variable

    # image path dictionary
    img_path = {
        'black': './images/pac_black_30x30.png',
        'blue': './images/pac_blue_30x30.png',
        'green': './images/pac_green_30x30.png',
        'light_blue': './images/pac_light_blue_30x30.png',
        'orange': './images/pac_orange_30x30.png',
        'red': './images/pac_red_30x30.png',
        'white': './images/pac_white_30x30.png',
        'yellow': './images/pac_yellow_30x30.png'
    }

    # Image Constants
    contagious_image = img_path['yellow']
    infected_image = img_path['red']
    recovered_image = img_path['green']
    transition_image = img_path['black']
    susceptible_image = img_path['white']

    # Global Values
    screen_height = 480
    screen_width = 640
    sprite_base_speed = 2
    sprite_size = 15

    # direction lists (or arrays if you like)
    # -1 = move left  or up
    #  1 = move right or down
    x_direction = [-1, 1]
    y_direction = [-1, 1]


class Population(pygame.sprite.Sprite):
    """Population: represents a collection of People along with their physical 
       location and proximity to each other
    """
    def __init__(self, width, height, infected_prob, recovered_prob,
                 susceptible_prob):

        self.Susceptible_Prob = susceptible_prob
        self.Infected_Prob = infected_prob
        self.Recovered_Prob = recovered_prob


class DiseaseStates(object):
    """SIR model: 
    """
    def __init__(self, pop_size=None, states=None):

        if pop_size is None:
            print("DiseaseStates class needs a population to be initialized...")
            sys.exit()

        # dictionary of states where key = "state name/label" and value = "ratio" of population
        self.States = {}

        # assign population size
        self.PopulationSize = pop_size

        # Create a list of these "states" which will hold a representative
        # number of occurences of each state. This means that if the population size
        # is 1000 and the ratios are S=.97, I=.02, and R=.01 then there will be
        # 970 "S" values 20 "I" values and 10 "R" values in the StateProbability list.
        self.StateProbability = []

        if not states is None:
            self.setStates(states)
        else:
            self.States = {
                "susceptible": .97,
                "infected": .02,
                "recovered": .01,
            }
            self.BuildStateValues()

    def SetStates(self, states):
        """SetStateValues: assigns the state name and ratio to a `States` dictionary.
           Also creates the list of probabilities to choose from when assigning a "state"
           to a person. 
        Params:
            states [dict] : Example: {"Susceptible":.97,"Infected":.02,"Recovered":.01}
        """

        for k, v in states.items():
            self.States[k] = v

        self.BuildStateValues()

    def BuildStateValues(self):
        """Creates the list of probabilities to choose from when assigning a "state"
           to a person. 
        Params:
            None
        """
        for k, v in self.States.items():
            self.StateProbability.extend([k] * int(v * self.PopulationSize))

        # Shuffle the list so we can randomly assign "states" to individuals
        random.shuffle(self.StateProbability)
    
    def StateExists(self,state):
        return state in self.States

    def AssignState(self):
        val = self.StateProbability.pop()
        return val

    def GetStateImage(self):
        pass




class Person(pygame.sprite.Sprite):
    """Person : Inherits from pygame Sprite
    """
    def __init__(self, pid, pos, state="susceptible", im_size=15):
        super().__init__()

        self.pid = pid

        self.last_cid = 0  # last change in direction

        self.im_size = im_size

        if SIR == "S":  # use susceptible image for sprite
            self.image = pygame.image.load(Config.susceptible_image)
        elif SIR == "I":  # use infected image for sprite
            self.image = pygame.image.load(Config.infected_image)
        else:  # use recovered image for sprite
            self.image = pygame.image.load(Config.recovered_image)

        # scale the image based on class input
        self.image = pygame.transform.scale(self.image,
                                            (self.im_size, self.im_size))

        # set up base variables for sprite class
        self.size = Config.sprite_size  # size of sprite :)
        self.width = width  # game board width
        self.height = height  # game board height
        self.rect = self.image.get_rect(
            center=pos)  # kinda the "sprite" container

        self.dx = 0  # x direction
        self.dy = 0  # y direction
        self.sir = SIR  # Which phase from model? S / I / R

        # give each person a little different speed
        self.speed = 1 + int(random.random() * Config.sprite_base_speed)

        self.last_move_frame = None

    def dir_x(self, x):
        """Set the x direction for the person (east/west). Invoke using the move method.
        """
        self.dx += x

    def dir_y(self, y):
        """Set the y direction for the person (east/west). Invoke using the move method.
        """
        self.dy += y

    def move(self, dx=None, dy=None):
        """Invoke to move a person in any cardinal direction by re-setting dx and/or dy.
        """
        self.stop_leaving_world()

        if dx != None:
            self.dx = dx

        self.rect.x += (self.dx * self.speed)

        if dy != None:
            self.dy = dy

        self.rect.y += (self.dy * self.speed)

    def determineSides(self, other):
        d = []
        if self.rect.midtop[1] > other.rect.midtop[1]:
            d.append("top")
        if self.rect.midleft[1] > other.rect.midleft[1]:
            d.append("left")
        if self.rect.midright[1] > other.rect.midright[1]:
            d.append("right")
        if self.rect.midtop[1] < other.rect.midtop[1]:
            d.append("bottom")

        return d


    def collided(self, other):
        if self.pid == other.pid:
            return
        x1, y1 = self.rect.center
        x2, y2 = other.rect.center

        d = math.sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))

        if d <= self.size:
            self.last_collision = pygame.time.get_ticks()
            return True

    def change_direction(self, other):

        current = pygame.time.get_ticks()

        sides = self.determineSides(other)

        dx = self.dx
        dy = self.dy

        if "top" in sides or "bottom" in sides:
            dx *= -1
        if "left" in sides or "right" in sides:
            dy *= -1
        self.move(dx, dy)

    def stop_leaving_world(self):
        """ This method checks if a sprites x,y coordinates are off the game board.
            If they are below 0, we make them 1 and if they are greater than the 
            width or the height, we make them (width/height - sprite.size).
            Also, if sprite goes off game board, we reverse the direction of the sprite. 
        """

        if self.rect.y <= 0:  # if y off screen top reverse direction
            self.dy *= -1
            self.rect.y = 1
        elif self.rect.y >= self.height - self.size:  # if y off screen bottom reverse direction
            self.dy *= -1
            self.rect.y = self.height - self.size

        if self.rect.x <= 0:  # if x off screen left reverse direction
            self.dx *= -1
            self.rect.x = 1
        elif self.rect.x >= self.width - self.size:  # if x off screen right reverse direction
            self.dx *= -1
            self.rect.x = self.width - self.size



def main(num_people=5, width=None, height=None):

    if width == None:
        width = Config.screen_width

    if height == None:
        height = Config.screen_height

    # Initialize PyGame
    pygame.init()

    pygame.display.set_caption("Covid 19 Baby")

    # Get a reference to the screen
    screen = pygame.display.set_mode((width, height))

    # Not Sure :)
    clock = pygame.time.Clock()

    # Create a Pygame Group
    # A group allows minipulation to the entire group OR
    # manipulating one member at a time. Nice to have the option
    population = pygame.sprite.Group()
    sprites = []
    pid = 0
    # Set up 20 "people" and place them at random locations on the screen
    for i in range(num_people):
        # pick a random position
        posx = int(random.random() * width - int(Config.sprite_size / 2))
        posy = int(random.random() * height - int(Config.sprite_size / 2))

        # create a position tuple
        pos = (posx, posy)

        # create a person
        p = Person(pid, pos, SIR[i], Config.SPRITE_SIZE, width, height)

        # shuffle the direction arrays
        random.shuffle(Config.x_direction)
        random.shuffle(Config.y_direction)

        # assign xy direction to a person
        p.dir_x(Config.x_direction[0])
        p.dir_y(Config.y_direction[0])

        # add person to the population
        population.add(p)
        sprites.append(p)

        pid += 1

    # keep looping while we are not done!
    done = False

    # Game loop
    while not done:
        # Check for interaction with game window (some event)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

        population.update()

        # for every person "p" call he move method
        for p in population:
            p.move()

        # check every i (a sprite / person) against every other sprite / person
        for i in range(len(sprites)):
            for j in range(len(sprites)):
                if sprites[i].collided(sprites[j]):
                    sprites[i].change_direction(sprites[j])

        # redraw the screen with r30 g30 b30 (basically almost black)
        screen.fill((30, 30, 30))

        # draw the "population" group onto the "screen"
        population.draw(screen)

        # Draw a rect over the selected sprite.
        #pygame.draw.rect(screen, (255, 128, 0), selected_person.rect, 2)

        pygame.display.flip()
        clock.tick(30)


def myKwargs(argv):
    kwargs = {}
    args = []
    for param in argv:
        if '=' in param:
            k, v = param.split('=')
            if v.isnumeric():
                kwargs[k] = int(v)
            else:
                kwargs[k] = v
        else:
            if param.isnumeric():
                param = int(param)
            args.append(param)

    return kwargs, args


###############################################################################
###############################################################################

if __name__ == '__main__':
    kwargs, args = myKwargs(sys.argv)

    print(kwargs)

    num_people = kwargs.get("num_people", 20)
    width = kwargs.get("width", 640)
    height = kwargs.get("height", 480)

    Config.screen_width = width
    Config.screen_height = height

    main(num_people, width, height)
    pygame.quit()
