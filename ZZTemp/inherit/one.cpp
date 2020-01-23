#include <SFML/Graphics.hpp>

using namespace sf;

struct golCell {
  bool isAlive;
  int neighborCount;
  RectangleShape* rect;

  golCell(){
      rect = new RectangleShape;
  }
};

struct gameOfLife{
    int Width;
    int Height;
    RenderWindow &WindowRef;
    gameOfLife(int width,int height,RenderWindow& window) : WindowRef(window) {
        Width = width;
        Height = height;
    }
};


int main(){

    RenderWindow window(VideoMode(200, 200), "Game of Life");

    gameOfLife Gol(400,400,window);
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}