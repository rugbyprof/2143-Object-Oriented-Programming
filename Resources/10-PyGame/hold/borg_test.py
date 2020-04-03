
import pygame
import random

pygame.init()


class Borg(object):
    _shared_state = {}
    def __init__(self):
        self.__dict__ = self._shared_state

    def __setitem__(self, key, value):
        self._shared_state[key] = value

    def __getitem__(self,key):
        return self._shared_state[key]



class Game(dict):
    def __init__(self):
        self.sharedState = Borg()

    def addShared(self,key,value):
        self.sharedState[key] = value

    def drawCircle(self):
        self.sharedState['pygame'].draw.circle(self.sharedState['screen'], (255, green, blue), (100, 250), 25)


if __name__=="__main__":

    screen = pygame.display.set_mode([500, 500])

    game = Game()
    game.addShared('pygame',pygame)
    game.addShared('screen',screen)
    
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

        game.drawCircle()

        # Flip the display
        pygame.display.flip()


    # Done! Time to quit.
    pygame.quit()




