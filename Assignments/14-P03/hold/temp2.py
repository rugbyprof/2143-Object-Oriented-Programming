#!/usr/bin/env python3

import pygame
import sys


class Sprite(pygame.sprite.Sprite):
    def __init__(self, pos):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.Surface([20, 20])
        self.image.fill((255, 0, 0))
        self.rect = self.image.get_rect()

        self.rect.center = pos

def main():
    pygame.init()
    clock = pygame.time.Clock()
    fps = 50
    bg = [255, 255, 255]
    size =[200, 200]


    screen = pygame.display.set_mode(size)

    player = Sprite([40, 50])
    player.move = [pygame.K_LEFT, pygame.K_RIGHT, pygame.K_UP, pygame.K_DOWN]
    player.vx = 5
    player.vy = 5


    wall = Sprite([100, 60])

    wall_group = pygame.sprite.Group()
    wall_group.add(wall)

    player_group = pygame.sprite.Group()
    player_group.add(player)

    # I added loop for a better exit from the game
    loop = 1
    while loop:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                loop = 0

        key = pygame.key.get_pressed()

        for i in range(2):
            if key[player.move[i]]:
                player.rect.x += player.vx * [-1, 1][i]

        for i in range(2):
            if key[player.move[2:4][i]]:
                player.rect.y += player.vy * [-1, 1][i]

        screen.fill(bg)

        # first parameter takes a single sprite
        # second parameter takes sprite groups
        # third parameter is a do kill command if true
        # all group objects colliding with the first parameter object will be
        # destroyed. The first parameter could be bullets and the second one
        # targets although the bullet is not destroyed but can be done with
        # simple trick bellow
        hit = pygame.sprite.spritecollide(player, wall_group, True)

        if hit:
            # if collision is detected call a function in your case destroy
            # bullet
            player.image.fill((255, 255, 255))

        player_group.draw(screen)
        wall_group.draw(screen)

        pygame.display.update()
        clock.tick(fps)

    pygame.quit()
    # sys.exit


if __name__ == '__main__':
    main()