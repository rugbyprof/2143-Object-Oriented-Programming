#include <SFML/Graphics.hpp>

#include <iostream> 

#define CELLSIZE 10

using namespace sf;

struct golCell {
  bool isAlive;
  int neighborCount;
  RectangleShape Rect;
  int Width;
  int Height;

  golCell(){
      Width = CELLSIZE;
      Height = CELLSIZE;
      Rect.setSize(sf::Vector2f(Width, Height));
      Rect.setFillColor(Color::Green);
      Rect.setOutlineColor(Color::Black);
      Rect.setOutlineThickness(1);
  }

  void setCellPos(int x,int y){
      Rect.setPosition(x*Width, y*Height);
  }

};

struct gameOfLife{
    int pixelWidth;
    int pixelHeight;
    int cellRows;
    int cellCols;

    RenderWindow Window;
    golCell** World;
    gameOfLife(int width,int height) {
        pixelWidth = width;
        pixelHeight = height;
        cellRows = int(pixelWidth/CELLSIZE);
        cellCols = int(pixelHeight/CELLSIZE);

        std::cout<<cellRows<<","<<cellCols<<std::endl;

        Window.create(VideoMode(pixelWidth, pixelHeight), "Game of Life");

        World = new golCell*[cellRows];

        for(int i=0;i<height;i++){
            World[i] = new golCell[cellCols];
            for(int j=0;j<cellCols;j++){
                World[i][j].setCellPos(i,j);
            }
        }
    }

    void drawWorld(){        
        Window.clear();
        // for(int i=0;i<cellRows;i++){
        //     for(int j=0;j<cellCols;j++){
        //         Window.draw(World[i][j].Rect);
        //     }
        // }
        drawGrid();
        Window.display();
    }

    void drawGrid(){
        VertexArray lines(LinesStrip, 2);
        lines[0].position = Vector2f(100, 100);
        lines[1].position = Vector2f(200, 200);
        lines[2].position = Vector2f(300, 300);
        lines[3].position = Vector2f(400, 400);

        Window.draw(lines);
    }
};




int main(){

    gameOfLife Gol(500,500);

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