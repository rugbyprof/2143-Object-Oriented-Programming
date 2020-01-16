class Skittle(object):
    """A Skittle object has a color to describe it."""
    def __init__(self, color):
        self.color = color

class Bag(object):
    """A Bag is a collection of Skittles. All bags share the
    number of Bags ever made (sold) and each bag keeps track of
    its Skittles in a list.
    """

    number_sold = 0

    def __init__(self):
        self.skittles = []
        Bag.number_sold += 1

    def tag_line(self):
        """Print the Skittles tag line."""
        print("Taste the rainbow!")

    def print_bag(self):
        print([s.color for s in self.skittles])

    def take_skittle(self):
        """Take the first skittle in the bag (from the front of
        the skittles list).
        """
        return self.skittles.pop(0)

    def add_skittle(self, s):
        """Add a skittle to the bag."""
        self.skittles.append(s)

    def take_color(self, color):
        """Remove a skittle of specified color from bag and return"""

        i = 0
        for s in self.skittles:
            if s.color == color:
                break
            i += 1
        
        if i == len(self.skittles):
            return None

        return self.skittles.pop(i)

    def take_all(self):
        """Remove each skittle from bag and print color"""
        """adapted from micah's solution"""

        while len(self.skittles) > 0:
            print(self.skittles.pop().color)

johns_bag = Bag()
johns_bag.print_bag()
# []

for color in ['blue', 'red', 'green', 'red']:
    johns_bag.add_skittle(Skittle(color))
johns_bag.print_bag()
# ['blue', 'red', 'green', 'red']

s = johns_bag.take_skittle()
print(s.color)
# blue

print(johns_bag.number_sold)
# 1

print(Bag.number_sold)
# 1

soumyas_bag = Bag()
soumyas_bag.print_bag()
# []

print(johns_bag.print_bag())
# ['red', 'green', 'red']

print(Bag.number_sold)
# 2

print(soumyas_bag.number_sold)
# 2

print(johns_bag.take_color('dsd'))

johns_bag.take_all()