from graphics import *
import random

width = 500
height = 500
win = GraphWin("Card Game",width,height,autoflush=True)

buffer = 10

win.setCoords(0,0,width,height)
#t = Text(Point(width/2,height/2), "Centered Text")
#t.draw(win)
# adjust = 0
# for i in range(5):
#     p = Polygon(Point(buffer+adjust,buffer+adjust), Point(width-buffer-adjust,buffer+adjust), Point(width-buffer-adjust,height-buffer-adjust),Point(buffer+adjust,height-buffer-adjust))
#     p.draw(win)
#     adjust += 5

start_y = height+200
offset = 0
loops = 1000
for i in range(loops):

    aRectangle = Rectangle(Point(0,0), Point(width,height))
    aRectangle.setFill("white")
    aRectangle.draw(win)
    cardImage = Image(Point(width/4,start_y-offset), './card_images/100x/queen_of_hearts2.gif')
    cardImage.draw(win)

    offset += 25
    cardImage.undraw()
    aRectangle.undraw()
    update()
    
	    

win.getMouse()
p.setFill("red")
p.setOutline("blue")
p.setWidth(2)
s = ""
