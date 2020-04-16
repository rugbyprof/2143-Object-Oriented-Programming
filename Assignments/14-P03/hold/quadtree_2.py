#!/usr/bin/env python3

import utils
import geometry
from geometry import x,y

# import enum

def as_box( quadrant ):
    """"Convert a quadrant of the form: ((x_min,y_min),width) to a box: ((x_min,y_min),(x_max,y_max))."""
    width = quadrant[1]
    minp = quadrant[0]
    maxp = tuple(xy+width for xy in minp)
    assert( x(minp) <= x(maxp) and y(minp) <= y(maxp) )
    return (minp,maxp)


def as_rect( quadrant ):
    """"Convert a quadrant of the form: ((x_min,y_min),width) to a rectangle: ((x0,y0),(x1,y1),(x2,y2),(x3,y3))."""
    qx,qy = quadrant[0]
    w = quadrant[1]
    return [(qx,qy),(qx+w,qy),(qx+w,qy+w),(qx,qy+w)]


class QuadTree(object):

    def __init__( self, points = [] ):
        """Build a quadtree on the given set of points.

        Points must be an iterable containing 2-tuples of the form: (x,y)"""

        # Initialize the root quadrant as the box around the points
        self.root, self.quadrants = self.init( points = points )

        # Each leaf of the quadtree may contains one resident point.
        self.residents = { self.root: None }

        # Each node of the quadtree may contains four children.
        self.children = { self.root: [] }

        # Status of quadrants
        # class Status(enum.Enum):
        class Status:
            Leaf = 1
            Node = 2
            Empty = 3
            Out = 4
        self.Status = Status()

        # Choose one of the two available functions for walking the tree:
        # self.walk = self.recursive_walk
        self.walk = self.iterative_walk

        # Generate the complete tree.
        self.build( points )


    def init( self, quadrant = None, box = None, points = None ):
        """Initialize the root quadrant with the given quadrant, the given box or the given set of points."""

        if len([k for k in (box,points,quadrant) if k]) > 1:
            raise BaseException("ERROR: you should specify a box, a quadrant or points")

        # Initialize the root quadrant as the given box
        if box:
            minp,maxp = box
            width = max( x(maxp)-x(minp), y(maxp)-y(minp) )

        # Initialize the root quadrant as the box around the points
        elif points:
            minp,maxp = geometry.box( points )
            width = max( x(maxp)-x(minp), y(maxp)-y(minp) )

        # Initialize the root quadrant as the given origin point and width
        elif quadrant:
            minp = quadrant[0]
            width = quadrant[1]

        assert( x(minp) <= x(minp)+width and y(minp) <= y(minp)+width )

        # There is always the root quadrant in the list of available ones.
        root = (minp,width)
        quadrants = [ root ]

        return root,quadrants


    def status( self, point, quadrant ):
        """Return Status.Empty if the given point can be appended in the given quadrant."""

        assert(point is not None)
        assert(len(point) == 2)
        assert(quadrant is not None)
        assert(len(quadrant) == 2)

        box = as_box( quadrant )

        # if the point lies inside the given quadrant
        if geometry.in_box( point, box):
            if self.residents[quadrant]:
                # external: a quadrant that already contains a point
                assert( not self.children[quadrant] )
                return self.Status.Leaf
            elif self.children[quadrant]:
                # internal: a quadrant that contains other quadrants
                return self.Status.Node
            else:
                # empty: there is not point yet in this quadrant
                return self.Status.Empty
        else:
            # point is out of the quadrant
            return self.Status.Out


    def split( self, quadrant ):
        """Split an existing quadrant in four children quadrants.

        Move the existing resident to the correct child."""

        # We cannot split a quadrant if it already have sub-quadrants
        if quadrant != self.root:
            assert( not self.children[quadrant] )

        qx, qy = quadrant[0]
        w = quadrant[1] / 2

        # For each four children quadrant's origins
        self.children[quadrant] = []
        for origin in ( (qx,qy), (qx,qy+w), (qx+w,qy+w), (qx+w,qy) ):
            # Create a child quadrant of half its width
            q = (origin, w)
            self.quadrants.append(q)
            # Default resident to None, because we will test for this key later on.
            self.residents[q] = None

            # Add this new child to the current parent.
            self.children[quadrant].append(q)
            # This new quadrant has no child.
            self.children[q] = []

        # Move the resident to the related children node
        p = self.residents[quadrant]
        if p is not None:
            # Find the suitable children quadrant
            for child in self.children[quadrant]:
                if self.status(p,child) == self.Status.Empty:
                    self.residents[child] = p
                    break
            # Forget we had resident here
            # Do not pop the key, because we have tests on it elsewhere
            self.residents[quadrant] = None


    def append( self, point, quadrant = None ):
        """Try to inset the given point in the existing quadtree, under the given quadrant.

        The default quadrant is the root one.
        Returns True if the point was appended, False if it is impossible to append it."""

        # Default to the root quadrant
        if not quadrant:
            quadrant = self.root
        assert(quadrant in self.quadrants)

        # The point should not be out of the root quadrant
        assert( self.status(point,self.root) != self.Status.Out )

        # FIXME use a recursive walk and prune branches with the Out status.
        for q in self.walk(quadrant):
            status = self.status( point, q )
            if status == self.Status.Leaf:
                # Create sub-quadrants
                self.split(q)
                # Try to attach the point in children quadrants, recursively
                for child in self.children[q]:
                    if self.append( point, child ):
                        return True
            elif status == self.Status.Empty:
                # add the point as an resident of the quadrant q
                self.residents[q] = point
                return True
        return False


    def build( self, points ):
        """Append all the given points in the quadtree."""
        for p in points:
            self.append(p)
        assert( len(points) == len(self) )


    def iterative_walk( self, at_quad = None ):

        # Default to the root quadrant
        if not at_quad:
            at_quad = self.root

        # First, consider the root quadrant
        yield at_quad

        # then children of the root quadrant
        quads = list(self.children[at_quad])
        for child in quads:
            yield child
            # then children of the current child
            quads.extend( self.children[child] )


    def recursive_walk( self, at_quad = None ):

        # Default to the root quadrant
        if not at_quad:
            at_quad = self.root

        yield at_quad
        for child in self.children[at_quad]:
            for q in self.recursive_walk(child):
                yield q


    def repr( self, quadrant = None, depth = 0 ):
        """Return a string representing the quadtree in a JSON-like format."""

        # Default to the root quadrant
        if not quadrant:
            quadrant = self.root

        head = "  "*depth
        r = head+"{"
        quadrep = '"origin" : %s, "width" : %f' % quadrant
        if self.residents[quadrant]: # external
            r += ' "resident" : %s, \t%s },\n' % (self.residents[quadrant],quadrep)
        elif self.children[quadrant]: # internal
            r += ' "children_ids" : %s, \t%s, "children" : [\n' % (self.children[quadrant],quadrep)
            for child in self.children[quadrant]:
                r += self.repr(child, depth+1)
            r+="%s]},\n" % head
        else: # empty
            r += ' "resident" : (), \t\t\t%s},\n' % (quadrep)
        return r


    def points( self ):
        """Return the set of points attached to the quadtree.

        In a random order."""
        return [p for p in self.residents.values() if p is not None]


    def covers( self, this, that ):
        """Return true if the given quadrants does intersects each other."""

        # Convert quadrants ((x,y),w) as box ((a,b),(c,d)).
        this_box = as_box(this)
        that_box = as_box(that)

        # Convert boxes as list of edges.
        this_segments = tuple(utils.tour(as_rect(this)))
        that_segments = tuple(utils.tour(as_rect(that)))

        # If at least one of the segment of "this" intersects with "that".
        intersects = any( geometry.segment_intersection(s0,s1) for s0 in this_segments for s1 in that_segments )

        # Transform nested list of segments in flat list of points without any duplicates.
        this_points = as_rect(this)
        that_points = as_rect(that)

        # If all the points of "this" are inside "that".
        # Note: what we would want to test here is if ALL the points are comprised,
        #       as the case where at least one is already tested by the "intersects" stage.
        #       But we use an "any" anyway, because it is sufficient in this case and
        #       that testing all the points takes more time.
        this_in = any( geometry.in_box(p,this_box) for p in that_points )
        that_in = any( geometry.in_box(p,that_box) for p in this_points )

        return intersects or this_in or that_in


    def query( self, query_quad, at_quad = None ):
        """Return all the points (currently attached to the quad tree) that are located within the query_quad quadrant."""
        if not at_quad:
            at_quad = self.root

        query_box = as_box(query_quad)

        # If we ask for a quadrant that intersects with the current one.
        if self.covers( query_quad, at_quad ):
            # If the current quadrant contains sub-quadrants.
            if len(self.children[at_quad]) > 0:
                # Then go explore them.
                points = []
                for quad in self.children[at_quad]:
                    points += self.query(query_quad,quad)
                return points
            else:
                # Else, just return the point within the current quadrant.
                resident = self.residents[at_quad]
                if resident:
                    if geometry.in_box(resident,query_box):
                        # In a list, because we will concatenate.
                        return [resident]
        # If there is no intersection, there is no points.
        return []


    # Pythonesque API:

    def __getitem__( self, quadrant ):
        """Return all the points that are located within the given quadrant.

        Ex.: points = quad[quad.root] # get all the points"""
        return self.query(quadrant,self.root)


    def __iter__(self):
        """Iterate over the attached points."""
        return iter(self.points())


    def __call__(self, points):
        """Append all the given points in the quadtree."""
        self.build(points)


    def __len__(self):
        """Return the number of points attached to the quad tree."""
        return len(self.points())


    def __repr__(self):
        """Return a string representing the quadtree in a JSON-like format."""
        return self.repr()


if __name__ == "__main__":

    import sys
    import math
    import random

    import utils
    import uberplot
    import matplotlib.pyplot as plot

    if len(sys.argv) == 2:
        seed = sys.argv[1]
    else:
        seed = None

    random.seed(seed)

    n=200
    points = [ ( round(random.uniform(-n,n),2),round(random.uniform(-n,n),2) ) for i in range(n) ]

    quad = QuadTree( points )
    # print(quad)
    # sys.stderr.write( "%i points in the quadtree / %i points\n" % (len(quad), len(points)) )


    fig = plot.figure()

    ax = fig.add_subplot(111)
    ax.set_aspect('equal')

    # Plot the whole quad tree and its points.
    # Iterating over the quadtree will generate points, thus list(quad) is equivalent to quad.points()
    uberplot.scatter_points( ax, list(quad), facecolor="green", edgecolor="None")

    for q in quad.quadrants:
        edges = list( utils.tour(as_rect(q)) )
        uberplot.plot_segments( ax, edges, edgecolor = "blue", alpha = 0.1, linewidth = 2 )

    # Plot a random query on the quad tree.
    # Remember a quadrant is ( (orig_y,orig_y), width )
    minp = ( round(random.uniform(-n,n),2), round(random.uniform(-n,n),2) )
    rand_quad = ( minp, round(random.uniform(0,n),2) )
    # Asking for a quadrant will query the quad tree and return the corresponding points.
    uberplot.scatter_points( ax, quad[rand_quad], facecolor="None", edgecolor="red", alpha=0.5, linewidth = 2 )
    edges = list( utils.tour(as_rect(rand_quad)) )
    uberplot.plot_segments( ax, edges, edgecolor = "red", alpha = 0.5, linewidth = 2 )

    plot.show()

    assert(len(points) == len(quad))
