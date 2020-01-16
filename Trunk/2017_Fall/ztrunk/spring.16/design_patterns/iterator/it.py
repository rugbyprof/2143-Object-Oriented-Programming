# Util/TypedIterator.py

class TypedIterator(Iterator):
    def __init__(self, it, type):
        self.imp = it
        self.type = type

    def hasNext(self):
        return imp.hasNext()

    def remove(self): imp.remove()
    def next(self):
        obj = imp.next()
        if(not type.isInstance(obj))
            throw ClassCastException(
              "TypedIterator for type " + type +
              " encountered type: " + obj.getClass())
        return obj
        
        
        
        
d = {'one':1,'two':2,'three':3}
di = TypedIterator(d,dict)

