from argparse import ArgumentParser, RawDescriptionHelpFormatter
from functools import partial
import sys
import random

import pyglet
import numpy as np

from pyglet2d import Shape


VELOCITY_RANGE = (-5000, 5000)
VELOCITY_INCREMENT = 50
ANGULAR_VELOCITY_STD = 3 * np.pi / 2
RADIUS_RANGE = (100, 200)
RADIUS_INCREMENT = 5/4
MAX_POLYGON_VERTICES = 12
BUFFER = 5


def draw(window, shapes):
    window.clear()
    for shape in shapes:
        shape.draw()


def update(window, shapes, dt):
    for shape in shapes:
        shape.update(dt)

    bounce(window, shapes)


def bounce(window, shapes):
    circle = shapes[0]
    new_velocity = None
    new_position = None
    if max(p[0] for p in circle.vertices) > window.width + 1:
        new_velocity = circle.velocity * [-1, 1]
        new_position = circle.center - [BUFFER, 0]

    elif min(p[0] for p in circle.vertices) < -1:
        new_velocity = circle.velocity * [-1, 1]
        new_position = circle.center + [BUFFER, 0]

    elif max(p[1] for p in circle.vertices) > window.height + 1:
        new_velocity = circle.velocity * [1, -1]
        new_position = circle.center - [0, BUFFER]

    elif min(p[1] for p in circle.vertices) < -1:
        new_velocity = circle.velocity * [1, -1]
        new_position = circle.center + [0, BUFFER]

    if new_velocity is not None:
        change_color(shapes)
        change_shape(shapes)
        change_angular_velocity(shapes)
        for shape in shapes:
            shape.velocity = new_velocity
            shape.position = new_position


def change_direction(shapes):
    new_velocity = VELOCITY_RANGE[0] + np.random.sample(2) * np.diff(VELOCITY_RANGE)
    for shape in shapes:
        shape.velocity = new_velocity


def change_color(shapes):
    new_color = tuple(random.randrange(256) for _ in range(3))
    for shape in shapes:
        shape.color = new_color


def change_shape(shapes):
    chosen_shape = random.choice([shape for shape in shapes if not shape.enabled])
    for shape in shapes:
        shape.enable(shape is chosen_shape)


def change_angular_velocity(shapes):
    for shape in shapes:
        shape.angular_velocity = ANGULAR_VELOCITY_STD * np.random.normal()


def bigger(shapes):
    for shape in shapes:
        shape.scale(RADIUS_INCREMENT)


def smaller(shapes):
    for shape in shapes:
        shape.scale(1/RADIUS_INCREMENT)


def faster(shapes):
    velocity = shapes[0].velocity
    if velocity[0] == 0:
        velocity = VELOCITY_INCREMENT * np.sign(np.random.sample(2) - 0.5)
    else:
        velocity += VELOCITY_INCREMENT * np.sign(velocity)
    for shape in shapes:
        shape.velocity = velocity


def slower(shapes):
    velocity = shapes[0].velocity
    if np.abs(velocity[0]) < VELOCITY_INCREMENT:
        velocity *= 0
    else:
        velocity -= VELOCITY_INCREMENT * np.sign(velocity)

    for shape in shapes:
        shape.velocity = velocity


EVENTS = {
    pyglet.window.key.UP: bigger,
    pyglet.window.key.DOWN: smaller,
    pyglet.window.key.RIGHT: faster,
    pyglet.window.key.LEFT: slower,
    pyglet.window.key.C: change_color,
    pyglet.window.key.SPACE: change_shape,
    pyglet.window.key.V: change_direction,
}


def on_key_press(shapes, symbol, modifiers):
    EVENTS.get(symbol, lambda x: None)(shapes)


def main(screen=None):
    if screen:
        screens = pyglet.canvas.get_display().get_screens()
        window = pyglet.window.Window(screen=screens[screen], fullscreen=True)
    else:
        window = pyglet.window.Window(fullscreen=True)

    radius = np.diff(RADIUS_RANGE) * np.random.sample() + RADIUS_RANGE[0]
    shape_kwargs = {'velocity':  np.random.sample(2) * np.diff(VELOCITY_RANGE) + VELOCITY_RANGE[0]}
    center = [window.width/2, window.height/2]
    shapes = [Shape.circle(center, radius, **shape_kwargs)]
    shapes.extend(Shape.regular_polygon(center, radius, verts,
                                        start_angle=np.random.random() * 2 * np.pi / verts, **shape_kwargs)
                  for verts in range(3, MAX_POLYGON_VERTICES + 1))
    change_angular_velocity(shapes)
    for shape in shapes[1:]:
        shape.enable(False)

    window.set_handlers(on_draw=partial(draw, window, shapes),
                        on_key_press=partial(on_key_press, shapes))
    pyglet.clock.schedule(partial(update, window, shapes))
    pyglet.app.run()

if __name__ == '__main__':
    controls = """\
Controls:
    UP/DOWN: Change object size.
    LEFT/RIGHT: Change object speed.
    C: Change object color.
    SPACE: Change object shape.
    V: Randomize object velocity.
    ESCAPE: Quit.
    """
    parser = ArgumentParser(description='Graphics test for pyglet2d.',
                            epilog=controls,
                            formatter_class=RawDescriptionHelpFormatter)
    parser.add_argument('--screen', type=int,
                        help='Screen to output to.')

    args = parser.parse_args()
    main(**vars(args))
    sys.exit()