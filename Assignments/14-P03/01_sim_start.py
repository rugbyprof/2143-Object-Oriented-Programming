#!/usr/bin/env python3
"""
This just spawns a bunch of "people" (pac man ghosts) and
has them float around the screen. 

Most config values are controlled by global vals at top of file.

This also has a person class, mostly to show a basic python class,
as well as give basic example with pygame integration. We can do
better and we will later.
"""
import pygame
import sys
import random

# Global Values
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
SPRITE_SIZE = 30
SPRITE_SPEED = 5

# direction lists (or arrays if you like)
# -1 = move left  or up
#  1 = move right or down
XDirection = [-1, 1]
YDirection = [-1, 1]
L = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

age = 21

if age < 21:
    print("no")

if age >= 21:
    print("yes")

if age == 21:
    print("cool")

if age != 21:
    print("not")

if not age == 21:
    print("notnot")

stats = {"num_people": 100, "num_infected": 89, "num_immune": 3, "deaths": 8}

x,y,z = (34,26,88)

print("length:",len((34,26,88)))

print("coords:")
print(x)
print(y)
print(z)

for k,v in stats.items():
    print(f"Key:{k} = Value:{v}")

if not "deaths" in stats:
    stats["deaths"] = 0

stats["deaths"] += 1

print(stats['num_infected'])

print('<img src="image/path"')

print(f"Number Infected: {stats['num_infected']} Deaths: {stats['deaths']}")

print(stats)


class Person(pygame.sprite.Sprite):
    """Person : Inherits from pygame Sprite
    """
    def __init__(self, pos, width, height):
        super().__init__()
        self.size = SPRITE_SIZE  # size of sprite :)
        self.width = width  # game board width
        self.height = height  # game board height
        self.image = pygame.image.load(
            './images/pacman-30x30.png')  # use image for sprite
        self.rect = self.image.get_rect(
            center=pos)  # kinda the "sprite" container
        self.speed = SPRITE_SPEED  # pixel moves per game loop
        self.dx = 0  # x direction
        self.dy = 0  # y direction

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
        self.check_off_game_board()

        if dx != None:
            self.dx = dx

        self.rect.x += (self.dx * self.speed)

        if dy != None:
            self.dy = dy

        self.rect.y += (self.dy * self.speed)

    def check_off_game_board(self):
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
            self.rect.y = self.height - 30

        if self.rect.x <= 0:  # if x off screen left reverse direction
            self.dx *= -1
            self.rect.x = 1
        elif self.rect.x >= self.width - self.size:  # if x off screen right reverse direction
            self.dx *= -1
            self.rect.x = self.width - 30


def main():
    # If you run program with a number after the file name like:
    #       python3 01_sim_start.py 50
    # then you will get 50 people in your sim
    num_people = 0
    if len(sys.argv) > 1:
        try:
            num_people = int(sys.argv[1])
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
    #range creates a list of "num_people" size

    for _ in range(num_people):
        # pick a random position
        posx = int(random.random() * 590) + 15
        posy = int(random.random() * 420) + 15

        # create a position tuple
        pos = (posx, posy)

        # create a person
        p = Person(pos, 640, 480)

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
    """
    This gets run when file called directly.
    """
    main()
    pygame.quit()