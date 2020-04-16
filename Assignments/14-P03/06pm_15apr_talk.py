#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random
import sys

"""
LECTURE material from 15 april at 12pm

dictionary {} key value pairs
list [] collection of anything
tuple () a "set" immutable


L = [10,"hello","goodbye",3.14159,[0,1,2,3,4]] # container

print(L[4][2])

Data = {"infected":3456789,"immune":9,"susceptible":74747474,"dead_names":["terry","whoever"]}

print(Data["dead_names"][0])

x,y = (34,78)


L = [10,"hello","goodbye",3.14159,[0,11,21,31,41]]

i = 0
mylist = []
while i < 10:
    mylist.append(i)
    i += 1

print(mylist)

i = 0
for item in L[4]:
    print(f"Item {i}: value {item}")
    i += 1

Data = {
    "infected":3456789,
    "immune":9,
    "susceptible":74747474,
    "dead_names":["terry","whoever"]
}

x,y = (34,78) # immutable

print(Data["infected"])

if not "recovered" in Data:
    Data["recovered"] = 0

Data["recovered"] += 1

for item in Data:
    print(Data[item])

for k,v in Data.items():
    print(k,v)


sys.exit()
"""

WIDTH = 640
HEIGHT = 480


class Person(pygame.sprite.Sprite):
    """
    This class represents the ball.
    It derives from the "Sprite" class in Pygame
    """
 
    def __init__(self,screen_width,screen_height,width=15,height=15):
        """ Constructor. Pass in the color of the block,
        and its size. """

    
         # Call the parent class (Sprite) constructor
        super().__init__()

        # self.state = "susceptible"

        self.screen_width = screen_width
        self.screen_height = screen_height

        self.width = width
        self.height = height

        self.dx = random.choice([-1,1])
        self.dy = random.choice([-1,1])

        self.speed = 7


        # self.color = color

        # Create an image of the block, and fill it with a color.
        # This could also be an image loaded from the disk.

        self.image = pygame.image.load("./images/pac_orange_30x30.png") 

        self.image = pygame.transform.scale(self.image, (self.width, self.height))
 
        # Fetch the rectangle object that has the dimensions of the image.
        # Update the position of this object by setting the values
        # of rect.x and rect.y

        self.x = int(random.random()*self.screen_width)
        self.y = int(random.random()*self.screen_height)

        self.rect = self.image.get_rect(center=(self.x,self.y))
    
    def move(self):
        self.checkOnScreen()
        self.rect.x += self.dx * self.speed
        self.rect.y += self.dy * self.speed

    def checkOnScreen(self):
        
        if self.rect.x <= 0 or self.rect.x >= self.screen_width:
            self.dx *= -1

        if self.rect.y <= 0 or self.rect.y >= self.screen_height:
            self.dy *= -1



pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([WIDTH, HEIGHT])

sprites_list = pygame.sprite.Group()

# Run until the user asks to quit
running = True

people = []

for i in range(250):
    people.append(Person(WIDTH,HEIGHT))
    sprites_list.add(people[-1]) # Add person to sprites list

# game loop
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((30, 30, 30))

    red = 0
    green = 0
    blue = 255

    sprites_list.draw(screen)

    for p in people:
        p.move()

    # Draw a solid blue circle in the center
    #pygame.draw.circle(screen, (red, green, blue), (250, 250), 75)

    # Flip the display
    pygame.display.flip()


# Done! Time to quit.
pygame.quit()
