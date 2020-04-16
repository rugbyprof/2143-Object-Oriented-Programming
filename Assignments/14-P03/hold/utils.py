
import sys
import math
from geometry import x,y

def LOG( *args ):
    """Print something on stderr and flush"""
    for msg in args:
        sys.stderr.write( str(msg) )
        sys.stderr.write(" ")
    sys.stderr.flush()


def LOGN( *args ):
    """Print something on stdeer, with a trailing new line, and flush"""
    LOG( *args )
    LOG("\n")


def load_points( stream ):
    points = []
    for line in stream:
        if line.strip()[0] != "#":
            p = tuple([float(i) for i in line.split(",")])
            assert(len(p)==2)
            points.append( p )
    return points


def write_points( points, stream ):
    for p in points:
        stream.write( "%f,%f\n" % ( x(p),y(p) ) )


def load_segments( stream ):
    segments = []
    for line in stream:
        if line.strip()[0] != "#":
            seg = line.strip().split()
            assert(len(seg)==2)
            edge = []
            for p in seg:
                point = tuple([float(i) for i in p.split(",")])
                assert(len(point)==2)
                edge.append( point )
            segments.append( edge )
    return segments


def write_segments( segments, stream ):
    for seg in segments:
        for p in seg:
            stream.write( "%f,%f " % ( x(p),y(p) ) )
        stream.write( "\n" )


def load_matrix( stream ):
    matrix = {}
    for line in stream:
        if line.strip()[0] != "#":
            skey,svals = line.split(":")
            key = tuple((float(i) for i in skey.split(',')))
            col = {}
            for stri in svals.split():
                sk,sv = stri.split("=")
                value = float(sv)
                k = tuple((float(i) for i in sk.split(",")))
                col[k] = value
            matrix[key] = col
    assert(len(matrix) == len(matrix[key]))
    return matrix


def write_matrix( mat, stream):
    for row in mat:
        key = "%f,%f:" % row
        line = key
        for k in mat[row]:
            val = mat[row][k]
            line += "%f,%f=%f " % (k[0],k[1],val)
        stream.write( line + "\n" )


def vertices_of( segments ):
    vertices = set()
    for start,end in segments:
        vertices.add(start)
        vertices.add(end)
    return vertices


def tour(lst):
    # consecutive pairs in lst  + last-to-first element
    for a,b in zip(lst, lst[1:] + [lst[0]]):
        yield (a,b)


