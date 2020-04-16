#
#  Author: Nathan Moore
#  Date: 2013-06-24
#
#  An implimentation of a quadtree
#
#  There are a few things I'd like to do a little differently:
#    * Not creating deeper QuadTreeNodes if the rectangle doesn't fit in one
#    * Maybe removing deeper node levels when empty
#


class RectData:
    '''Stores data in a rectangular shape. The data can be anything.'''
    def __init__(self, x, y, w, h, data):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.data = data
        self.parent = None


class _QuadTreeNode:
    '''Nodes in the quadtree implimentation. Rectangles are stored in the node
that the rectangle can fully fit inside.'''
    def __init__(self, level, x, y, w, h):
        self.nodes = []
        self.data = []
        self.level = level
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def contains(self, rect):
        '''Checks if a rectangle fits inside this node.'''
        return (rect.x >= self.x) and (rect.y >= self.y) and (
            rect.x + rect.w < self.x + self.w) and (rect.y + rect.h <
                                                    self.y + self.h)

    def add(self, rect):
        '''
           Adds a rectangle to the quadtree. If it fits in deeper node, it recurses
           up and tells that node to add it, else it adds the rectangle to this node.
        '''

        # Creates child nodes for the four quadrants if they don't exist and we're
        # not currently at the deepest depth level.
        if self.level != 0 and len(self.nodes) == 0:
            # Upper left
            self.nodes.append(
                _QuadTreeNode(self.level - 1, self.x, self.y, self.w / 2,
                              self.h / 2))
            # Upper right
            self.nodes.append(
                _QuadTreeNode(self.level - 1, self.x + self.w / 2, self.y,
                              self.w / 2, self.h / 2))
            # Lower left
            self.nodes.append(
                _QuadTreeNode(self.level - 1, self.x, self.y + self.h / 2,
                              self.w / 2, self.h / 2))
            # Lower right
            self.nodes.append(
                _QuadTreeNode(self.level - 1, self.x + self.w / 2,
                              self.y + self.h / 2, self.w / 2, self.h / 2))

        inserted = False
        for n in self.nodes:
            if n.contains(rect):
                # If the rectangle fits in a deeper node, tell that node to add it.
                inserted = True
                n.add(rect)

        if not inserted:
            # If the rectangle was not added to a child node, add it to this node.
            self.data.append(rect)
            rect.parent = self

    def remove(self, rect):
        '''Removes the rectangle from the quadtree.'''

        # Only try to remove the rectangle if it belongs to this node
        if rect.parent is not self:
            return

        # Clear the rectangles parent and remove it from this node's data
        rect.parent = None
        self.data.remove(rect)

    def clear(self):
        '''Recursively clears the quadtree.'''

        # Tell child nodes to clear
        for n in self.nodes:
            n.clear()

        # Since this node will be removed, rectangles shouldn't point to it any more.
        for d in self.data:
            d.parent = None

        # Clear the data and the child nodes.
        self.data = []
        self.nodes = []

    def querry(self, x, y, w, h):
        '''
           Recursively iterate through rectangles that intersect with the specified
           querry rectangle.
        '''

        # Recursively check child nodes
        for n in self.nodes:
            for d in n.querry(x, y, w, h):
                # Yield the rectangles that had been yielded by child nodes
                yield d

        # Check rectangles in data to see if they intersect
        for d in self.data:
            # We're going to check if the distance between the centers of the two
            # rectangles are less than the sum of half the rectangle's size to see if
            # they overlap with eachother.
            dw = d.w / 2
            dh = d.h / 2
            dx = d.x + dw
            dy = d.y + dh
            if (abs(dx - x) < dw + w) and (abs(dy - y) < dh + h):
                # Since this rectangle intesects with the querry rectangle, yield it.
                yield d


class QuadTree:
    '''The quadtree container for adding, removing, and interacting with rectangles.'''
    def __init__(self, maxLevel, w, h):
        self.root = _QuadTreeNode(maxLevel, 0, 0, w, h)
        self.w = w
        self.h = h

    def add(self, rect):
        '''Add a RectData to the quadtree'''
        if self.root.contains(rect):
            self.root.add(rect)
            return True
        return False

    def remove(self, rect):
        '''Remove a RectData from the quadtree'''
        if rect.parent is not None:
            rect.parent.remove(rect)

    def clear(self):
        '''Clear the quadtree'''
        self.root.clear()

    def querry(self, x, y, w, h):
        '''
          Querry the quadtree to see what rectangles intersect with the specified
          querry rectangle shape.  Iterator for the rectangles it finds.
        '''
        for rect in self.root.querry(x + w / 2, y + h / 2, w / 2, h / 2):
            yield rect


if __name__=='__main__':

    pass