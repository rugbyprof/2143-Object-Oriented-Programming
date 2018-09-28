#include <SFML/Graphics.hpp>
#include <iostream>

#define CELLSIZE 10

struct lifeCell : public sf::Drawable {
	sf::RectangleShape rect;
	bool alive;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		target.draw(rect);
	}
};

/**
* Starter class to represent game of life
*/
class gameOfLife  {
private:
	lifeCell **World;				// double pointer to a lifeCell (defined above)
	int Rows;						// num rows in game board
	int Cols;						// num cols in game board
	sf::RenderWindow &WindowRef;	// reference to sfml window so we can draw to it.

	/**
	* Creates the game board, resets it (0's it out), then randomly populates it.
	*/
	void init() {
		
		World = new lifeCell *[Rows];

		for (int i = 0; i < Rows; i++) {
			World[i] = new lifeCell[Cols];
		}

		resetBoard();
		randomlyPopulate();
	}

public:
	/**
	* GameOfLife Constructor extends sfml WindowRef
	* @param:
	*    sf::RenderWindow : a reference to our sfml window
	*
	*/
	gameOfLife(sf::RenderWindow &thatWindow) : WindowRef(thatWindow){
		Rows = 30;
		Cols = 20;
		init();
	}

	/**
	* GameOfLife Constructor extends sfml WindowRef
	* @param:
	*    sf::RenderWindow : a reference to our sfml window
	*    int rows : num of rows in board
	*    int cols : num of cols in board
	*
	*/
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


/**
* Not used in GOL but this is an example of a function that makes a 2D array
* of sfml rectangle shapes.
* @params:
*    int rows - number of rows in 2D array
*    int cols - numberof cols in 2D array
* @returns: **RectangleShape (pointer)
*/
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


int main() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "Game of Life");

	int frameRate = 5;
	int frameCount = 0;

	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	gameOfLife Gol(window,width/CELLSIZE,height/CELLSIZE);


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


		if (frameCount % frameRate == 0) {
			window.display();
		}

		
		frameCount++;
	}
	return 0;
}
