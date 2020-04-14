#!/usr/bin/env python3

import random
import pygame as pg


class Entity(pg.sprite.Sprite):

    def __init__(self, pos):
        super().__init__()
        #self.image = pg.Surface((30, 30))
        self.image = pg.image.load('pacman-30x30.png')
        #self.image.fill(pg.Color('dodgerblue1'))
        self.rect = self.image.get_rect(center=pos)
        #self.stretchedImage = pg.transform.scale(self.ghost, (40, 40))

    def move_down(self):
        self.rect.y += 2


def main():
    pg.init()
    screen = pg.display.set_mode((640, 480))
    clock = pg.time.Clock()
    all_sprites = pg.sprite.Group()
    for _ in range(20):
        pos = random.randrange(630), random.randrange(470)
        all_sprites.add(Entity(pos))

    # Select a random sprite from the all_sprites group.
    selected_sprite = random.choice(all_sprites.sprites())

    done = False
    while not done:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                done = True
            elif event.type == pg.KEYDOWN:
                if event.key == pg.K_r:
                    selected_sprite = random.choice(all_sprites.sprites())

        all_sprites.update()
        # Use the selected sprite in the game loop.
        selected_sprite.move_down()

        screen.fill((30, 30, 30))
        all_sprites.draw(screen)
        # Draw a rect over the selected sprite.
        pg.draw.rect(screen, (255, 128, 0), selected_sprite.rect, 2)

        pg.display.flip()
        clock.tick(30)


if __name__ == '__main__':
    main()
    pg.quit()