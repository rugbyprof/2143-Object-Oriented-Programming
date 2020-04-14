#!/usr/bin/env python3

"""
This 
"""

import pygame
import sys
import random
import math

# images dictionary
SKINS = {
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
CONTAGIOUS_IMAGE = SKINS['yellow']
INFECTED_IMAGE = SKINS['red']
RECOVERED_IMAGE = SKINS['yellow']
RECOVERING_IMAGE = SKINS['black']
SUSCEPTIBLE_IMAGE = SKINS['white']

# Global Values
SCREEN_HEIGHT = 480
SCREEN_WIDTH = 640
SPRITE_BASE_SPEED = 2
SPRITE_SIZE = 15

# SIR MODEL
INFECTED_PROB = .10
RECOVERED_PROB = .10
SUSCEPTIBLE_PROB = .80

# direction lists (or arrays if you like)
# -1 = move left  or up
#  1 = move right or down
XDirection = [-1, 1]
YDirection = [-1, 1]

# Status List
SIR = []

# Adjust Percentages for each phase
S = ["S"] * int(SUSCEPTIBLE_PROB * 100)  # repeat "S" for probability num times
I = ["I"] * int(INFECTED_PROB * 100)  # repeat "I" for probability num times
R = ["R"] * int(RECOVERED_PROB * 100)  # repeat "R" for probability num times

# Append each into single list of 100 items where each probability adds
# up to 100 items (ex: S=80 occurences, I=10 occurences, and R=10 occurences)
SIR = S + I + R

# Shuffle the array so we choose items randomly from it.
random.shuffle(SIR)


class Person(pygame.sprite.Sprite):
    """Person : Inherits from pygame Sprite
    """
    def __init__(self,
                 pid,
                 pos,
                 SIR="S",
                 im_size=15,
                 width=SCREEN_WIDTH,
                 height=SCREEN_HEIGHT):
        super().__init__()

        self.pid = pid

        self.last_cid = 0  # last change in direction

        self.im_size = im_size

        if SIR == "S":
            self.image = pygame.image.load(
                SUSCEPTIBLE_IMAGE)  # use susceptible image for sprite
        elif SIR == "I":
            self.image = pygame.image.load(
                INFECTED_IMAGE)  # use infected image for sprite
        else:
            self.image = pygame.image.load(
                RECOVERED_IMAGE)  # use recovered image for sprite

        # scale the image based on class input
        self.image = pygame.transform.scale(self.image,
                                            (self.im_size, self.im_size))

        # set up base variables for sprite class
        self.size = SPRITE_SIZE  # size of sprite :)
        self.width = width  # game board width
        self.height = height  # game board height
        self.rect = self.image.get_rect(
            center=pos)  # kinda the "sprite" container

        self.dx = 0  # x direction
        self.dy = 0  # y direction
        self.sir = SIR  # Which phase from model? S / I / R

        # give each person a little different speed
        self.speed = 1 + int(random.random() * SPRITE_BASE_SPEED)

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

    def transition_skin(self):
        current = pygame.time.get_ticks()

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
        self.move(dx,dy)

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
        width = SCREEN_WIDTH

    if height == None:
        height = SCREEN_HEIGHT

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
        posx = int(random.random() * width - int(SPRITE_SIZE / 2))
        posy = int(random.random() * height - int(SPRITE_SIZE / 2))

        # create a position tuple
        pos = (posx, posy)

        # create a person
        p = Person(pid, pos, SIR[i], SPRITE_SIZE, width, height)

        # shuffle the direction arrays
        random.shuffle(XDirection)
        random.shuffle(YDirection)

        # assign xy direction to a person
        p.dir_x(XDirection[0])
        p.dir_y(YDirection[0])

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
    """This process command line arguments and lets you "configure" the current run.
       It takes parameters that look like: key=value or num_people=100 (with NO spaces between)
       and puts them into a python dictionary that looks like:
       {
           "key":"value",
           "num_people":100
       }

       If a parameter doesn't have an "=" sign in it, it puts it into a list
       Both the dictionary (kwargs) and list (args) get returned.
       See usage below under if__name__=='__main__'
    """
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


if __name__ == '__main__':
    kwargs, args = myKwargs(sys.argv)

    print(kwargs)

    num_people = kwargs.get("num_people", 20)
    width = kwargs.get("width", 640)
    height = kwargs.get("height", 480)

    main(num_people, width, height)
    pygame.quit()