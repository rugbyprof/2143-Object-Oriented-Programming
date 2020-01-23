#include <SFML/Graphics.hpp>

using namespace sf;

struct golCell {
  bool isAlive;
  int neighborCount;
  
  int Width;
  int Height;

  golCell(){
      Width = 10;
      Height = 10;

  }


};

struct gameOfLife{
    int Width;
    int Height;
    RenderWindow Window;
    golCell** World;
    RectangleShape Rect;
    gameOfLife(int width,int height) {
        Width = width;
        Height = height;
        Window.create(VideoMode(Width, Height), "Game of Life");

        World = new golCell*[height];

        for(int i=0;i<height;i++){
            World[i] = new golCell[width];
        }
    }

    void drawWorld(){        
        Window.clear();
        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){
                Rect.setPosition(i*Width, j*Height);
                Rect.setSize(sf::Vector2f(Width, Height));
                Rect.setFillColor(Color::Green);
                Rect.setOutlineColor(Color::Black);
                Rect.setOutlineThickness(1);
                Window.draw(Rect);
            }
        }
        Window.display();
    }
};



int main(){

    gameOfLife Gol(1000,1000);

    while (Gol.Window.isOpen())
    {
        Event event;
        while (Gol.Window.pollEvent(event))
        {
            Gol.drawWorld();
            if (event.type == Event::Closed)
                Gol.Window.close();
        }


    }

    return 0;
}