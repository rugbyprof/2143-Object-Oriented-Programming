import sys
import math
import itertools
import operator

AVG_EARTH_RADIUS = 6371  # in km


def haversine(point1, point2, miles=True):
    """ Calculate the great-circle distance between two points on the Earth surface.
    :input: two 2-tuples, containing the latitude and longitude of each point
    in decimal degrees.
    Example: haversine((45.7597, 4.8422), (48.8567, 2.3508))
    :output: Returns the distance bewteen the two points.
    The default unit is kilometers. Miles can be returned
    if the ``miles`` parameter is set to True.
    """
    # unpack latitude/longitude
    lat1 = point1.y
    lng1 = point1.x
    lat2 = point2.y
    lng2 = point2.x

    # convert all latitudes/longitudes from decimal degrees to radians
    lat1, lng1, lat2, lng2 = map(radians, (lat1, lng1, lat2, lng2))

    # calculate haversine
    lat = lat2 - lat1
    lng = lng2 - lng1
    d = sin(lat * 0.5) ** 2 + cos(lat1) * cos(lat2) * sin(lng * 0.5) ** 2
    h = 2 * AVG_EARTH_RADIUS * asin(sqrt(d))
    if miles:
        return h * 0.621371  # in miles
    else:
        return h  # in kilometers
        
def bearing(pointA, pointB):
    """
    Calculates the bearing between two points.
    The formulae used is the following:
        θ = atan2(sin(Δlong).cos(lat2),
                  cos(lat1).sin(lat2) − sin(lat1).cos(lat2).cos(Δlong))
    :Parameters:
      - `pointA: The tuple representing the latitude/longitude for the
        first point. Latitude and longitude must be in decimal degrees
      - `pointB: The tuple representing the latitude/longitude for the
        second point. Latitude and longitude must be in decimal degrees
    :Returns:
      The bearing in degrees
    :Returns Type:
      float
    """
    if (type(pointA) != tuple) or (type(pointB) != tuple):
        raise TypeError("Only tuples are supported as arguments")

    lat1 = math.radians(pointA[0])
    lat2 = math.radians(pointB[0])

    diffLong = math.radians(pointB[1] - pointA[1])

    x = math.sin(diffLong) * math.cos(lat2)
    y = math.cos(lat1) * math.sin(lat2) - (math.sin(lat1)
            * math.cos(lat2) * math.cos(diffLong))

    initial_bearing = math.atan2(x, y)

    # Now we have the initial bearing but math.atan2 return values
    # from -180° to + 180° which is not what we want for a compass bearing
    # The solution is to normalize the initial bearing as shown below
    initial_bearing = math.degrees(initial_bearing)
    compass_bearing = (initial_bearing + 360) % 360

    return compass_bearing
    
def cardinal(d):
    '''
    note: this is highly approximate...
    '''
    dirs = ["N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
            "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"]
            
    dirs = ["N", "N", "N", "E", "E", "E", "S", "S", "S", "S", "S", "W", "W", "W", "N", "N"]
            
    ix = int((d + 11.25)/22.5 - 0.02) 
    
    return dirs[ix % 16]    

def most_common(L):
    # get an iterable of (item, iterable) pairs
    SL = sorted((x, i) for i, x in enumerate(L))
    # print 'SL:', SL
    groups = itertools.groupby(SL, key=operator.itemgetter(0))
    # auxiliary function to get "quality" for an item
    def _auxfun(g):
        item, iterable = g
        count = 0
        min_index = len(L)
        for _, where in iterable:
            count += 1
            min_index = min(min_index, where)
        # print 'item %r, count %r, minind %r' % (item, count, min_index)
        return count, -min_index
    # pick the highest-count/earliest item
    return max(groups, key=_auxfun)[0]
                 
if __name__=='__main__':
       
    if len(sys.argv) < 2:
        sys.exit()
    else:
    
        lines = []
        u = {}
        v = {}

        with open(sys.argv[1]) as f:
            for line in f:
                line = line.strip()
                id,lls = line.split(':')
                lls = eval(lls.strip())
                
                u[id] = (lls[0][1],lls[0][0])
                v[id] = (lls[1][1],lls[1][0])
                    
        keep = set()
        max_diff = 0
        del_id = -1
        
        while len(u.keys()) > 0:
        
            """
            Build sets with relative position to each other
            """                
            setu = {}
            
            for i in u.keys():
                setu[i] = set()
                for j in u.keys():
                    if not i == j:
                        c = cardinal(bearing(u[j], u[i]))
                        setu[i].add((c,j))   
                        
            setv = {}
            
            for i in v.keys():
                setv[i] = set()
                for j in v.keys():
                    if not i == j:
                        c = cardinal(bearing(v[j], v[i]))
                        setv[i].add((c,j))
                        
            print("\nshowing complete sets")
            for s in setu.keys():
                print(s,setu[s])
                print(s,setv[s])

        

            for s in setu.keys():
                print(s,setu[s] - setv[s])
                diff = len(setu[s] - setv[s])
                print(diff)
                if diff == 0:
                    keep.add(s)
                elif diff > max_diff:
                    max_diff = diff
                    rem_id = s
                
            if max_diff > 0:
                print(max_diff,rem_id)
                
                del u[rem_id]
                del v[rem_id]
            
            max_diff = 0
            rem_id = -1
            
            for s in keep:
                u.pop(s, None)
                v.pop(s, None)
       
                
        print()
        print(sorted(keep))
            
            
            
                    
        
