#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random
import math

class Config:
    #no constructor
    width = 1024
    height = 768
    sprite_images = {
        "blue" : "./images/pac_blue_30x30.png",
        "light_blue" : "./images/pac_light_blue_30x30.png",
        "red" : "./images/pac_red_30x30.png",
        "white" : "./images/pac_white_30x30.png",
        "yellow" : "./images/pac_yellow_30x30.png",
        "orange" : "./images/pac_orange_30x30.png",
        "green" : "./images/pac_green_30x30.png"
    }
    social_distancing = False
    infection_radius = 10
    infection_rate = .20
    population_count = 16
    sprite_width = 15
    sprite_height = 15
    sprite_speed = 2

Config.width = 400
Config.height = 400
Config.pid = 1
Config.myClock = 1

"""

Stuff we lectured about 16 April at 1:00 pm


Pygame hello world: Print a circle in middle of screen.

dictionary {} key value pairs
list [] collection of anything
tuple () a "set" immutable


L = [10,"hello","goodbye",3.14159,[0,1,2,3,4]]

print(L[4][2])

Data = {"infected":3456789,"immune":9,"susceptible":74747474,"dead_names":["terry","whoever"]}

print(Data["dead_names"][0])

x,y = (34,78)
"""



# pygame thing
class Person(pygame.sprite.Sprite):
    """
    This class represents the ball.
    It derives from the "Sprite" class in Pygame
    """
    def __init__(self,
                 screen_width,
                 screen_height,
                 color,
                 width=15,
                 height=15,
                 speed=1,inx=None,iny=None):
        """ Constructor. Pass in the color of the block,
        and its size. """
        # Call the parent class (Sprite) constructor
        super().__init__()

        self.id = Config.pid
        Config.pid +=1

        self.state = "susceptible"

        # screen width and height used to know
        # when to change direction at edge of screen
        self.screen_width = screen_width
        self.screen_height = screen_height

        # size of our sprite
        self.width = width
        self.height = height

        # direction x and direction y
        self.dx = random.choice([-1, 1])
        self.dy = random.choice([-1, 1])

        speeds = range(1,6)
        # pixels per game loop
        #self.speed = random.choice([1,7])
        self.speed = speed
        self.original_speed = speed

        self.color = color

        # Create an image of the block, and fill it with a color.
        # This could also be an image loaded from the disk.

        # pygame thing
        self.image = pygame.image.load(Config.sprite_images[self.color])
        # pygame thing
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

        # Fetch the rectangle object that has the dimensions of the image.
        # Update the position of this object by setting the values
        # of rect.x and rect.y

        if inx is None:
            # creates a random location between bounds of screen size
            x = int(random.random() * self.screen_width)
        else:
            x = inx

        if iny is None:
            # creates a random location between bounds of screen size
            y = int(random.random() * self.screen_height)
        else:
            y = iny

        # pygame thing
        self.rect = self.image.get_rect(center=(x, y))

        self.lastCollisionTime = 0

    def move(self):
        """move : moves our sprite around the screen
        """
        self.check_bounds()

        # add speed pixels to current location
        # multiplied by direction


        if self.lastCollisionTime > 0 and Config.myClock - self.lastCollisionTime > 2:
            print(f"current-time = {Config.myClock} last: {self.lastCollisionTime}")
            self.speed = self.original_speed
            self.lastCollisionTime = 0
            print(f"speed: {self.speed}")

        # pygame thing
        self.rect.x += self.speed * self.dx
        self.rect.y += self.speed * self.dy
    
 

    def check_bounds(self):
        """check_bounds: checks to see if we are still on the screen.
           If not, we reverse direction.
        """
        # if our x goes less than zero or more than width negate dx.
        if self.rect.x >= self.screen_width-self.width or self.rect.x <= 0:
            self.dx *= -1

        #
        if self.rect.y >= self.screen_height-self.width or self.rect.y <= 0:
            self.dy *= -1

    def determineSides(self, other):
        """ Determines where the sprite is in relation to other, kind of like
            "top left" or "bottom right".
            Returns: List of sides  (e.g ['right','bottom'])
        """
        d = []
        if self.rect.midtop[1] < other.rect.midtop[1]:
            d.append("top")
        if self.rect.midleft[0] < other.rect.midleft[0]:
            d.append("left")
        if self.rect.midright[0] > other.rect.midright[0]:
            d.append("right")
        if self.rect.midbottom[1] > other.rect.midbottom[1]:
            d.append("bottom")

        return d
    
    def changeDirection(self,other):

        sides = self.determineSides(other)

        self.lastCollisionTime = Config.myClock

        #print(self.lastCollisionTime)
        
        self.speed *= .5

        #print(f"{self.color} {sides}")
        if "right" in sides:
            self.dx = -1
            #self.rect.x -= 5
        if "left" in sides:
            self.dx = 1
            #self.rect.x += 5
        if "top" in sides:
            self.dy = -1
            #self.rect.y -= 5
        if "bottom" in sides:
            #self.rect.y += 5
            self.dy = 1

        

    def collide(self, other,social_distance=20):
        """collide : check to see of we hit another sprite
           Params:
               other [Person] : other person getting checked for collision
        """
        # if not other.state == "infected":
        #     return

        # getting x,y for both sprites
        x1, y1 = self.rect.center
        x2, y2 = other.rect.center

        # distance
        d = math.sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))
        
        if d < social_distance:
            self.changeDirection(other)
            #print(f"d:{d} collision:{self.width*1.2}")

        # if distance is less than some threshold , then do something
        if d < self.width*1 and random.random() < Config.infection_rate:
            self.image = pygame.image.load(Config.sprite_images["red"])
            self.image = pygame.transform.scale(self.image,
                                                (self.width, self.height))
            self.state = "infected"


#__________________________________________________________________________

if __name__=='__main__':
    pygame.init()

    # Set up the drawing window
    screen = pygame.display.set_mode([Config.width, Config.height])

    # sprites should be in a sprite group
    sprites_list = pygame.sprite.Group()

    # a list to hold all of our people sprites
    people = []

    # list of colors
    colors = ["blue", "light_blue", "white", "yellow","orange","green"]

    #speeds = [x for x in range(1,3)] #pythonic

    # loop N times
    for i in range(Config.population_count):
        # add a "person" to our list of people
        # create an "instance" of our class
        people.append(Person(Config.width, Config.height, random.choice(colors),Config.sprite_width,Config.sprite_height,Config.sprite_speed)) #random.choice(speeds)

        # Add last person to our sprites list
        # list[-1] give you the last item
        sprites_list.add(people[-1])  

    clock=pygame.time.Clock()

    # Run until the user asks to quit
    running = True

    ## this is our simulation object??
    while running:

        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            # handle MOUSEBUTTONUP
            if event.type == pygame.MOUSEBUTTONUP:
                pos = pygame.mouse.get_pos()
                #print(pos)
                people.append(Person(Config.width, Config.height, random.choice(colors),15,15,1,pos[0],pos[1])) #random.choice(speeds)

                # Add last person to our sprites list
                # list[-1] give you the last item
                sprites_list.add(people[-1]) 


        # Fill the background with blackish
        screen.fill((30, 30, 30))

        sprites_list.draw(screen)

        # loop through each person
        # and call a move method
        for p in people:
            p.move()
            # loop through each person
            # and check for collision (could be better)
            for sp in people:
                if not p == sp:  #and sp.state == 'infected':
                    p.collide(sp,25)

        # Flip the display
        pygame.display.flip()

        #Number of frames per secong e.g. 60
        clock.tick(40)

        Config.myClock += 1


    # Done! Time to quit.
    pygame.quit()
