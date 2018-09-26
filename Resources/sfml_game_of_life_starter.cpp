#include <SFML/Graphics.hpp>
#include <iostream>

#define CELLSIZE 10

struct lifeCell : public sf::Drawable {
	sf::RectangleShape rect;
	bool alive;
	//sf::Color color;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		target.draw(rect);
	}
};

class gameOfLife  {
private:
	lifeCell **World;
	int Rows;
	int Cols;
	sf::RenderWindow &WindowRef;

	void init() {
		
		World = new lifeCell *[Rows];

		for (int i = 0; i < Rows; i++) {
			World[i] = new lifeCell[Cols];
		}

		resetBoard();
		randomlyPopulate();
	}

public:
	gameOfLife(sf::RenderWindow &thatWindow) : WindowRef(thatWindow){
		Rows = 30;
		Cols = 20;
		init();
	}

	gameOfLife(sf::RenderWindow &thatWindow, int rows,int cols) : WindowRef(thatWindow) {
		Rows = rows;
		Cols = cols;
		init();
	}

	void resetBoard() {
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < Cols; j++) {
				World[i][j].rect.setSize(sf::Vector2f(CELLSIZE, CELLSIZE));
				World[i][j].alive = 0;
				//World[i][j].color = sf::Color::Black;
				World[i][j].rect.setPosition((i + 1)*CELLSIZE, (j + 1)*CELLSIZE);
			}
		}
	}

	void randomlyPopulate(int max_life = 30) {
		int count = 0;
		int r, c;
		while (count < max_life) {
			r = rand() % Rows;
			c = rand() % Cols;
			if (World[r][c].alive == 0) {
				World[r][c].alive = 1;
				World[r][c].rect.setFillColor(sf::Color::Green);
				//World[r][c].color = sf::Color::Green;
				count++;
			}
		}
	}

	void printBoard() {
		int x = 0;
		int y = 0;
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < Cols; j++) {
				if (World[i][j].alive) {
					y = (i + 1) * CELLSIZE;
					x = (j + 1) * CELLSIZE;
					WindowRef.draw(World[i][j].rect);
				}
			}
		}
	}

};



sf::RectangleShape** makeWorld(int rows, int cols) {
	sf::RectangleShape **World;

	World = new sf::RectangleShape *[rows];

	for (int i = 0; i < rows; i++) {
		World[i] = new sf::RectangleShape[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			World[i][j].setSize(sf::Vector2f(10, 10));
		}
	}

	return World;
}



void print2d(int**world, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << world[i][j];
		}
		std::cout << std::endl;
	}
}


struct directionType {
	int x;
	int y;
	directionType() {
		x = 1;
		y = 1;
	}
};

directionType direction(sf::CircleShape shape, sf::Vector2u winSize) {
	sf::Vector2f position = shape.getPosition();

	directionType d;

	if (position.x >= winSize.x) {
		d.x = -1;
	}
	if (position.y >= winSize.y) {
		d.y = -1;
	}

	if (position.x <= 0) {
		d.x = 1;
	}
	if (position.y <= 0) {
		d.y = 1;
	}

	return d;
}

void moveShape(sf::CircleShape& shape,int x,int y, sf::Vector2u window) {
	directionType d = direction(shape,window);
	std::cout << d.x << "," << d.y << std::endl;
	shape.move(x*d.x, y*d.y);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	//sf::CircleShape shape(20.f);
	//shape.setFillColor(sf::Color(150, 50, 250));
	//shape.setOutlineThickness(5);
	//shape.setOutlineColor(sf::Color(250, 150, 100));

	int frameRate = 5;
	int frameCount = 0;

	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	gameOfLife Gol(window,width/CELLSIZE,height/CELLSIZE);

	//sf::Vector2f position = shape.getPosition();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		Gol.resetBoard();
		Gol.randomlyPopulate();
		Gol.printBoard();

		//moveShape(shape, 1, 1, size);
		
		//window.draw(shape);

		if (frameCount % frameRate == 0) {
			window.display();
		}

		frameCount++;
	}
	return 0;
}