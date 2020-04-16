#!/usr/bin/env python3

#  Author: Nathan Moore
#  Date: 2013-06-24
#
#  Tests the quadtree implimentation
#
#  Return adds a random rectangle
#  Click and drag to select rectangles
#  Backspace removes selected rectangles
#  Delete clears the quadtree



import pygame
import random

from quadtree import QuadTree, RectData
from config import Config

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

        # direction x and direction y
        self.dx = random.choice([-1, 1])
        self.dy = random.choice([-1, 1])

        self.image = pygame.image.load(Config.sprite_images[self.color])
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

        self.rect = self.image.get_rect(center=(x, y))

    def move(self):
        """move : moves our sprite around the screen
        """
        self.check_bounds()

        # add speed pixels to current location
        # multiplied by direction
        self.rect.x += self.speed * self.dx
        self.rect.y += self.speed * self.dy

def draw_quadtree(surface, node):
    for n in node.nodes:
        draw_quadtree(surface, n)
        pygame.draw.rect(surface, (192,192,192), pygame.Rect(n.x, n.y, n.w+1, n.h+1), 1)
        for d in n.data:
            pygame.draw.rect(surface, d.data, pygame.Rect(d.x, d.y, d.w, d.h))
    for d in node.data:
        pygame.draw.rect(surface, d.data, pygame.Rect(d.x, d.y, d.w, d.h))
            
    
if __name__ == "__main__":
    display = pygame.display.set_mode((640, 640))
    clock = pygame.time.Clock()
    
    mdown = False
    mx1 = 0
    my1 = 0
    mx2 = 0
    my2 = 0
    selected = []
    
    quadtree = QuadTree(8, 640, 640)
    
    keep_going = True
    while keep_going:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                keep_going = False
                
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN:
                    x = random.randint(0,600)
                    y = random.randint(0,600)
                    w = random.randint(3,40)
                    h = random.randint(3,40)
                    color = (random.randint(64,250), random.randint(64,250), random.randint(64,250))
                    quadtree.add(RectData(x, y, w, h, color))
                    
                    mx1,my1,mx2,my2 = (0,0,0,0)
                    mdown = False
                    selected = []
                    
                if event.key == pygame.K_BACKSPACE:
                    for d in selected:
                        quadtree.remove(d)
                    selected = []
                    
                if event.key == pygame.K_DELETE:
                    quadtree.clear()
                    mx1,my1,mx2,my2 = (0,0,0,0)
                    mdown = False
                    selected = []
                    
                    
            if event.type == pygame.MOUSEBUTTONDOWN:
                mdown = True
                mx1, my1 = event.pos
                
            if event.type == pygame.MOUSEBUTTONUP:
                mdown = False
                
                if mx2 < mx1:
                    mx1,mx2 = mx2,mx1
                
                if my2 < my1:
                    my1,my2 = my2,my1
                    
                selected = [rect for rect in quadtree.querry(mx1, my1, mx2-mx1, my2-my1)]
        
        if mdown:
            mx2, my2 = pygame.mouse.get_pos()
            
        display.fill((255,255,255))
        draw_quadtree(display, quadtree.root)
        
        pygame.draw.rect(display, (255,0,0), pygame.Rect(mx1, my1, mx2-mx1, my2-my1), 1)
        
        for d in selected:
            pygame.draw.rect(display, (0,0,0), pygame.Rect(d.x, d.y, d.w, d.h), 2)
        
        pygame.display.flip()
        
        clock.tick(60)
