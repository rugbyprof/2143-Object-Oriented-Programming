#!/usr/bin/env python

from __future__ import division 
import math

epsilon = 1e-6
# epsilon = 0

def x( point ):
    return point[0]

def y( point ):
    return point[1]


def mid( xy, pa, pb ):
    return ( xy(pa) + xy(pb) ) / 2.0

def middle( pa, pb ):
    return mid(x,pa,pb),mid(y,pa,pb)


def euclidian_distance( ci, cj, graph = None):
    return math.sqrt( float( x(ci) - x(cj) )**2 + float( y(ci) - y(cj) )**2 )


def linear_equation( p0, p1 ):
    """Return the linear equation coefficients of a line given by two points.
       Use the general form: c=a*x+b*y """
    assert( len(p0) == 2 )
    assert( len(p1) == 2 )

    a = y(p0) - y(p1)
    b = x(p1) - x(p0)
    c = x(p0) * y(p1) - x(p1) * y(p0)
    return a, b, -c


def is_null( x, e = epsilon ):
    return -e <= x <= e


def is_vertical( leq ):
    a,b,c = leq
    return is_null(b)


def is_point( segment ):
    """Return True if the given segment is degenerated (i.e. is a single point)."""
    return segment[0] == segment[1]


def collinear( p, q, r, e = epsilon ):
    """Returns True if the 3 given points are collinear.

    Note: there is a lot of algorithm to test collinearity, the most known involving linear algebra.
    This one has been found in Jonathan Shewchuk's "Lecture Notes on Geometric Robustness".
    It is maybe the most elegant one: just arithmetic on x and y, without ifs, sqrt or risk of divide-by-zero error.
    """
    # Without epsilon comparison, this would ends as:
    # return (x(p)-x(r)) * (y(q)-y(r)) == (x(q)-x(r)) * (y(p)-y(r))
    return abs((x(p)-x(r)) * (y(q)-y(r)) - (x(q)-x(r)) * (y(p)-y(r))) <= e


def line_intersection( seg0, seg1 ):
    """Return the coordinates of the intersection point of two lines given by pairs of points, or None."""

    # Degenerated segments
    def on_line(p,seg):
        if collinear(p,*seg):
            return p
        else:
            return None

    # Segments degenerated as a single points,
    if seg0[0] == seg0[1] == seg1[0] == seg1[1]:
        return seg0[0]
    # as two different points,
    elif is_point(seg0) and is_point(seg1) and seg0 != seg1:
        return None
    # as a point and a line.
    elif is_point(seg0) and not is_point(seg1):
        return on_line(seg0[0],seg1)
    elif is_point(seg1) and not is_point(seg0):
        return on_line(seg1[0],seg0)


    leq0 = linear_equation(*seg0)
    leq1 = linear_equation(*seg1)

    # Collinear lines.
    if leq0 == leq1:
        return None

    # Vertical line
    def on_vertical( seg, leq ):
        a,b,c = leq
        assert( not is_null(b) )
        assert( is_null( x(seg[0])-x(seg[1]) ) )
        px = x(seg[0])
        # Remember that the leq form is c=a*x+b*y, thus y=(c-ax)/b
        py = (c-a*px)/b
        return px,py

    if   is_vertical(leq0) and not is_vertical(leq1):
        return on_vertical( seg0, leq1 )
    elif is_vertical(leq1) and not is_vertical(leq0):
        return on_vertical( seg1, leq0 )
    elif is_vertical(leq0) and is_vertical(leq1):
        return None

    # Generic case.
    a0,b0,c0 = leq0
    a1,b1,c1 = leq1

    d  = a0 * b1 - b0 * a1
    dx = c0 * b1 - b0 * c1
    dy = a0 * c1 - c0 * a1
    if not is_null(d):
        px = dx / d
        py = dy / d
        return px,py
    else:
        # Parallel lines
        return None


def box( points ):
    """Return the min and max points of the bounding box enclosing the given set of points."""
    minp = min( [ x(p) for p in points ] ), min( [ y(p) for p in points ] )
    maxp = max( [ x(p) for p in points ] ), max( [ y(p) for p in points ] )
    return minp,maxp


def in_box( point, box, exclude_edges = False ):
    """Return True if the given point is located within the given box."""
    pmin,pmax = box
    if exclude_edges:
        return x(pmin)-epsilon <  x(point) <  x(pmax)+epsilon and y(pmin)-epsilon <  y(point) <  y(pmax)+epsilon
    else:
        return x(pmin)-epsilon <= x(point) <= x(pmax)+epsilon and y(pmin)-epsilon <= y(point) <= y(pmax)+epsilon


def segment_intersection( seg0, seg1 ):
    """Return the coordinates of the intersection point of two segments, or None."""
    assert( len(seg0) == 2 )
    assert( len(seg1) == 2 )

    p = line_intersection(seg0,seg1)

    if p is None:
        return None
    else:
        if in_box(p,box(seg0)) and in_box(p,box(seg1)):
            return p
        else:
            return None


if __name__ == "__main__":
    import sys
    import random
    import utils
    import uberplot
    import matplotlib.pyplot as plot

    # intersections demo
    if len(sys.argv) > 1:
        scale = 100
        nb = int(sys.argv[1])
        points = [ (scale*random.random(),scale*random.random()) for i in range(nb)]
    else:
        points = [
                (10,0),
                (-190,0),
                (10,200),
                (110,100),
                (110,-100),
                (-90,100),
                (-90,-100),
                ]

    segments = []
    for p0 in points:
        for p1 in points:
            if p0 != p1:
                segments.append( (p0,p1) )

    seg_inter = []
    line_inter = []
    for s0 in segments:
        for s1 in segments:
            if s0 != s1:
                s = segment_intersection( s0, s1 )
                if s is not None:
                    seg_inter.append(s)
                l = line_intersection( s0, s1 )
                if l is not None:
                    line_inter.append(l)


    fig = plot.figure()

    ax = fig.add_subplot(121)
    uberplot.plot_segments( ax, segments, linewidth=0.5, edgecolor = "blue" )
    uberplot.scatter_points( ax, points,     edgecolor="blue", facecolor="blue",  s=120, alpha=1, linewidth=1 )
    uberplot.scatter_points( ax, line_inter, edgecolor="none", facecolor="green", s=60,  alpha=0.5 )
    uberplot.scatter_points( ax, seg_inter,  edgecolor="none", facecolor="red",   s=60,  alpha=0.5 )
    ax.set_aspect('equal')


    # collinear test demo
    if len(sys.argv) > 1:
        scale = 100
        nb = int(sys.argv[1])
        triangles = []
        for t in range(nb):
            triangles.append( [ [scale*random.random(),scale*random.random()] for i in range(3)] )
            # forced collinear
            t = [ [scale*random.random(),scale*random.random()] for i in range(2)]
            triangles.append( [t[0],t[1],t[0]] )

    else:
        triangles = [
                [(-60.45085, -24.898983), (-68.54102, -30.776835), (-58.54102, -30.776835)],
                [(-68.54102, -0.0), (-65.45085, -9.510565), (-58.54102, -0.0)],
                [(-65.45085, 9.510565), (-68.54102, -0.0), (-58.54102, -0.0)],
                [(-68.54102, 30.776835), (-60.45085, 24.898983), (-58.54102, 30.776835)],
                [(-58.54102, -0.0), (-65.45085, -9.510565), (-55.45085, -9.510565)],
                [(-65.45085, -9.510565), (-57.36068, -15.388418), (-55.45085, -9.510565)],
                [(-65.45085, 9.510565), (-58.54102, -0.0), (-55.45085, 9.510565)],
                [(-65.45085, 9.510565), (-65.45085, 9.510565), (-55.45085, 9.510565)], # is collinear
            ]

    ax = fig.add_subplot(122)

    for triangle in triangles:
        status="green"
        if collinear(*triangle):
            status="red"
        uberplot.plot_segments( ax, utils.tour(triangle), edgecolor = status )

    # ax.set_aspect('equal')
    ax.axis('auto')


    plot.show()

