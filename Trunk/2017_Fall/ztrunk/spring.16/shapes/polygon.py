import math
from line import Line


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def distance(self, p2):
        return math.sqrt((self.x-p2.x)**2 + (self.y-p2.y)**2)

class Polygon:
    def __init__(self):
        self.vertices = []
    def add_point(self, point):
        self.vertices.append((point))
    def perimeter(self):
        perimeter = 0
        points = self.vertices + [self.vertices[0]]
        for i in range(len(self.vertices)):
            perimeter += points[i].distance(points[i+1])
        return perimeter


class Polygon(object):
    def __init__(self):
        self.map={}
        self.sides = 0
        
    def add_line(self, l1):
        if len(self.map) ==0:
            self.map[l1.p1]=l1
            self.sides += 1
        else:
            if not l1.p1 in self.map.keys():
                self.map[l1.p1] = l1
                self.sides += 1 
    def iscomplete(self):
        if l1.p2 is 
        return True
