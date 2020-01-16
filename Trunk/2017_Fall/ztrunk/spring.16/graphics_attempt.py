from graphics import *

def main():
    win = GraphWin("My Circle", 700, 500,autoflush=False)
    c = Circle(Point(50,50), 10)
    c.draw(win)
    
    x = 0
    y = 0
    while not win.checkMouse():
        c.move(5,5)
        update()
        c.undraw()
        c.draw(win)
    
    win.getMouse() # Pause to view result
    win.close()    # Close window when done

main()