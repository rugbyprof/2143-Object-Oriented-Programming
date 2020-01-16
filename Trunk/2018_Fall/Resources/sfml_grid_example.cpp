#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

struct Cell {
  bool isAlive;
  int neighborCount;
  RectangleShape Rect;
  int Width;
  int Height;
  bool dirty;

  Cell(int size = 16) {
    Width = size;
    Height = size;
    std::cout << Width << " " << Height << std::endl;
    Rect.setSize(sf::Vector2f((float)Width, (float)Height));
    Rect.setFillColor(Color::Red);
    Rect.setOutlineColor(Color::Black);
    Rect.setOutlineThickness(1);
    dirty = false;
  }

  void setCellPos(int x, int y) {
    std::cout << x << " " << y << std::endl;
    Rect.setPosition((float)x, (float)y);
  }

  void setRectSize(int w, int h) {
    Rect.setSize(sf::Vector2f((float)w, (float)h));
  }

  void setCellColor(Color C) { Rect.setFillColor(C); }
};

struct Character {
  sf::Sprite sprite;
  sf::Texture texture;

  Character(std::string file) {
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
  }
};

struct Grid {
  int Width;
  int Height;
  int CellSize;

  int CellWidth;
  int CellHeight;

  int NumRows;
  int NumCols;

  int PlayerRow;
  int PlayerCol;

  Character *c;

  RenderWindow Window;
  Cell*** World;
  Grid(int width, int height, int cellsize) {
    Width = width;
    Height = height;

    if (Width % cellsize != 0 || Height % cellsize != 0) {
      std::cout << "Error: Grid's Width and Height must be divisible by "
                   "CellSize! Exiting..."
                << std::endl;
      exit(0);
    }

    CellWidth = cellsize;
    CellHeight = cellsize;
    CellSize = cellsize;

    NumRows = (float)Width / (float)CellHeight;
    NumCols = (float)Height / (float)CellWidth;

    // std::cout<<CellWidth<<" "<<CellHeight<<std::endl;
    // std::cout<<NumRows<<" "<<NumCols<<std::endl;

    Window.create(VideoMode(Width, Height), "Grid Example");

    World = new Cell**[NumRows];

    for (int i = 0; i < NumRows; i++) {
      World[i] = new Cell*[NumCols];

      for (int j = 0; j < NumCols; j++) {
        World[i][j] = new Cell(CellSize);
        World[i][j]->setCellPos(i * CellHeight, j * CellWidth);
        World[i][j]->dirty = true;
      }
    }
    c = new Character("person2_128.png");
  }

  void changeRandomCell() {
    int r = rand() % NumRows;
    int c = rand() % NumCols;
    int i = rand() % 6;

    World[r][c]->dirty = true;
    switch (i) {
      case 0:
        World[r][c]->setCellColor(Color::Blue);
        break;
      case 1:
        World[r][c]->setCellColor(Color::Cyan);
        break;
      case 2:
        World[r][c]->setCellColor(Color::Green);
        break;
      case 3:
        World[r][c]->setCellColor(Color::Magenta);
        break;
      case 4:
        World[r][c]->setCellColor(Color::Red);
        break;
      case 5:
        World[r][c]->setCellColor(Color::White);
        break;
      case 6:
        World[r][c]->setCellColor(Color::Yellow);
        break;
    }
  }

  void setPlayerPosition(int r, int c) {
    PlayerRow = r;
    PlayerCol = c;
    World[PlayerRow][PlayerCol]->setCellColor(Color::Blue);
    World[PlayerRow][PlayerCol]->dirty = true;
  }

  void randomlyMove() {
    World[PlayerRow][PlayerCol]->setCellColor(Color::Red);
    World[PlayerRow][PlayerCol]->dirty = true;
    if (rand() % 2 == 0) {
      ++PlayerRow;
    } else {
      --PlayerRow;
    }

    if (rand() % 2 == 0) {
      ++PlayerCol;
    } else {
      --PlayerCol;
    }
    World[PlayerRow][PlayerCol]->setCellColor(Color::Blue);
    World[PlayerRow][PlayerCol]->dirty = true;
  }

  // void buildGrid(){
  //     sf::Vertex line[2];
  //     line[0].position = sf::Vector2f(10, 0);
  //     line[0].color  = sf::Color::Red;
  //     line[1].position = sf::Vector2f(20, 0);
  //     line[1].color = sf::Color::Red;
  // }

  void drawGrid() {
    Window.clear();

    for (int i = 0; i < NumRows; i++) {
      for (int j = 0; j < NumCols; j++) {
        if (World[i][j]->dirty) {
          Window.draw(World[i][j]->Rect);
          World[i][j]->dirty = false;
        }
      }
    }
    Window.draw(c->sprite);
    Window.display();
  }
};

int main() {
  Grid G(1040, 1040, 16);
  int i = 0;

  G.setPlayerPosition(50, 50);
  while (G.Window.isOpen()) {
    Event event;
    while (G.Window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        G.Window.close();
      }
    }

    if (i % 1000 == 0) {
      G.drawGrid();
      G.randomlyMove();
    }

    ++i;
  }

  return 0;
}