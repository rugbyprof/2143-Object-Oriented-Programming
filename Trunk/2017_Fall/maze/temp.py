import copy
import math
import random

from python.common.svg import Svg


def coordinate_to_string(i, j):
    return str(i) + "," + str(j)


def generate_graph(x, y):
    graph = {}

    edges = []

    for i in range(2 * x):
        for j in range(y):
            if (i + j) % 2 != 0:
                continue
            id = coordinate_to_string(i, j)
            paths = set()

            lower_i = i - 1 >= 0
            upper_i = i + 1 < (x * 2)
            lower_j = j - 1 >= 0
            lower_i2 = i - 2 >= 0
            upper_j = j + 1 < y
            upper_i2 = i + 2 < (x * 2)

            if lower_i and lower_j:
                edges.append((id, coordinate_to_string(i - 1, j - 1)))
                paths.add(coordinate_to_string(i - 1, j - 1))
            if lower_i and upper_j:
                edges.append((id, coordinate_to_string(i - 1, j + 1)))
                paths.add(coordinate_to_string(i - 1, j + 1))
            if upper_i and lower_j:
                edges.append((id, coordinate_to_string(i + 1, j - 1)))
                paths.add(coordinate_to_string(i + 1, j - 1))
            if upper_i and upper_j:
                edges.append((id, coordinate_to_string(i + 1, j + 1)))
                paths.add(coordinate_to_string(i + 1, j + 1))
            if upper_i2:
                edges.append((id, coordinate_to_string(i + 2, j)))
                paths.add(coordinate_to_string(i + 2, j))
            if lower_i2:
                edges.append((id, coordinate_to_string(i - 2, j)))
                paths.add(coordinate_to_string(i - 2, j))

            graph[id] = paths

    return graph, edges


def draw_graph(width, height, size=600, edges=None):
    svg = Svg()

    medges = copy.deepcopy(edges)

    one_height = size / height
    one_width = size / width

    _size = min(one_height, one_width)

    current_y = _size / 2

    if medges is not None:
        froms = map(lambda x: (x[1], x[0]), edges)
        for fr in froms:
            medges.append(fr)

    # for fr in medges:
    #     print(fr)

    for i in range(2 * height):
        current_x = _size / 2

        for j in range(width):
            if (i + j) % 2 == 0:
                center = (current_x, current_y)
                gaps = []
                if medges is not None:
                    gaps = get_gaps(i, j, medges)
                svg.add_hexagon(center, _size / 2, gaps, "none", 3)
            current_x += (_size - _size / 4)

        current_y += math.sqrt((_size / 2) ** 2 - (_size / 4) ** 2)

    svg.save("canvas")


def get_gaps(i, j, edges):
    gaps = []
    id = coordinate_to_string(i, j)
    o_x, o_y = id.split(",")
    froms = filter(lambda x: x[0] == id, edges)
    for fr in list(froms):
        or_x, or_y = int(o_x), int(o_y)
        str_x, str_y = fr[1].split(",")
        d_x, d_y = int(str_x), int(str_y)
        if or_y == d_y:
            if or_x > d_x:
                gaps.append(4)
            else:
                gaps.append(1)
        if or_x > d_x and or_y > d_y:
            gaps.append(3)
        if or_x > d_x and or_y < d_y:
            gaps.append(5)
        if or_x < d_x and or_y > d_y:
            gaps.append(2)
        if or_x < d_x and or_y < d_y:
            gaps.append(0)
    return gaps


def carve_paths(edges):
    result_edges = []
    sets = {}

    while len(edges) > 0:
        edge = random.sample(edges, 1)[0]
        o_id, d_id = edge

        edges.remove(edge)

        if o_id not in sets.keys():
            sets[o_id] = set()
            sets[o_id].add(o_id)
        if d_id not in sets.keys():
            sets[d_id] = set()
            sets[d_id].add(d_id)

        set_o = sets[o_id]
        set_d = sets[d_id]

        if len(set_o.intersection(set_d)) == 0:
            new_set = set_o | set_d
            sets[o_id] = new_set
            sets[d_id] = new_set
            result_edges.append(edge)

    return result_edges


g, e = generate_graph(25, 25)

draw_graph(25, 25, 1000, edges=carve_paths(e))