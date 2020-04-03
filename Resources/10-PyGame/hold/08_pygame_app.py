import sys

import pygame

from pygame.locals import *

WINDOW_SIZE = (500,500)

pygame.init()

FPS_RATE = 30

BACKGROUND = pygame.Color(0,0,0)

def singleton(cls):
    instances = {}
    def getinstance():
        if cls not in instances:
            instances[cls] = cls()
        return instances[cls]
    return getinstance

def dir_clamp(val):
    if val >= 1:
        return 1
    elif val <= -1:
        return -1
    else:
        return 0

def tuple_map(op, t1, t2):
    def inner(iop, it1, it2):
        for index, t in enumerate(it1):
            yield iop(it1[index], it2[index])

    if op is None:
        op = lambda x,y: x or y
    if None in (t1, t2):
        raise ValueError("tuples cannot be None.")
    if len(t1) is not len(t2):
        raise ValueError("tuples must have matching length.")

    return tuple(inner(op, t1, t2))


@singleton
class Game(object):

    def __init__(self, debug = False):
        self.window = self.create_window(tuple_map(lambda x,y: x+y, WINDOW_SIZE, (1,1)))

        self.debug = debug
        
        self.running = True
        self.timer = pygame.time.Clock()
        self.max_fps = FPS_RATE
        self.objects = []

        self.title = "My Game"

        self.listeners = {}

        self.on_event(QUIT, self.shutdown)
        self.on_event(KEYDOWN, self.quit_pressed)


    def run(self):

        self.setup()

        while self.running:
            self.elapsed = self.timer.tick(self.max_fps) / 1000

            self.window.fill(BACKGROUND)
            
            # draw stuff to the screen.
            map(lambda d: d.draw(self.window), self.objects)

            pygame.display.update()

            # process game events.
            for event in pygame.event.get():
                if self.debug:
                    print >> sys.stderr, repr(event)
                if event.type in self.listeners.keys():
                    self.emit(event.type, event)

            # update all the objects.
            map(lambda o: o.update(self.elapsed), self.objects)
            

        self.teardown()

    def delta_time(self):
        if hasattr(self, "elapsed") and self.elapsed is not None:
            return self.elapsed

    def create_window(self, size):
        return pygame.display.set_mode(size)

    def update_title(self, title):
        if title == "":
            title = self.title
        else:
            title = "%s - %s" % (self.title, title)
        pygame.display.set_caption(title)

    def setup(self):
        self.update_title("")

    def shutdown(self, evt):
        self.running = False

    def quit_pressed(self, evt):
        if evt.key in (K_ESCAPE, K_q):
            pygame.event.post(pygame.event.Event(QUIT))

    def teardown(self):
        pygame.quit()

    def emit(self, evt_type, evt):
        for l, args in self.listeners[evt_type]:
            l(evt, *args)

    def on_event(self, evt_type, cb, *args):
        if evt_type not in self.listeners.keys():
            self.listeners[evt_type] = []
        self.listeners[evt_type].append((cb, args))

def main(args):

    app = Game()

    app.run()


if __name__ == "__main__":
    main(sys.argv[1:])