#include <SFML/Graphics.hpp>
#include <iostream>

#define CELLSIZE 10

using namespace sf;

/**
* lifeCell : A single instance of a cell in a Game of Life array
* @Extends:
*   sf::Drawable
* @Data-Elements:
* 	RectangleShape rect;	// sfml rectangle type
* 	bool alive;		// is cell alive or not
* @Methods:
* 	void draw(RenderTarget& target, RenderStates state) const
*/
struct lifeCell : public Drawable {
	RectangleShape rect;
	bool alive;
protected:
	/**
	* void draw: draws an SFML shape to an SFML window.
	*/
	void draw(RenderTarget& target, RenderStates state) const // means this method won't change 
								  // anything...	
	{
		target.draw(rect);
	}
};

/**
* Starter class to represent game of life
*/
class gameOfLife {
private:
	lifeCell **World;				// double pointer to a lifeCell (defined above)
	int Rows;					// num rows in game board
	int Cols;					// num cols in game board
	RenderWindow &WindowRef;	// reference to sfml window so we can draw to it.

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
	*    RenderWindow : a reference to our sfml window
	*
	*/
	gameOfLife(RenderWindow &thatWindow) : WindowRef(thatWindow) {
		Rows = 30;
		Cols = 20;
		init();
	}

	/**
	* GameOfLife Constructor extends sfml WindowRef
	* @param:
	*    RenderWindow : a reference to our sfml window
	*    int rows : num of rows in board
	*    int cols : num of cols in board
	*
	*/
	gameOfLife(RenderWindow &thatWindow, int rows, int cols) : WindowRef(thatWindow) {
		Rows = rows;
		Cols = cols;
		init();
	}


	/**
	* Function: resetBoard
	* 	Sets the size of each rectangle to CELLSIZE (necessary?)
	*       Also sets each cell to NOT alive
	* @param:
	*	None
	* @returns:
	*       None
	*/
	void resetBoard() {
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < Cols; j++) {
				World[i][j].rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
				World[i][j].alive = 0;
				World[i][j].rect.setPosition((i + 1)*CELLSIZE, (j + 1)*CELLSIZE);
			}
		}
	}

	/**
	* Function: randomlyPopulate
	* 	Sets max_life number of cells to alive
	* @param:
	*	int max_life
	* @returns:
	*       None
	*/
	void randomlyPopulate(int max_life = 30) {
		int count = 0;
		int r, c;
		while (count < max_life) {
			r = rand() % Rows;
			c = rand() % Cols;
			if (World[r][c].alive == 0) {
				World[r][c].alive = 1;
				World[r][c].rect.setFillColor(Color::Green);
				count++;
			}
		}
	}

	/**
	* Function: printBoard
	* 	Prints board to an sfml window
	* @param:
	*	None
	* @returns:
	*       None
	*/
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
RectangleShape** makeWorld(int rows, int cols) {
	RectangleShape **World;

	World = new RectangleShape *[rows];

	for (int i = 0; i < rows; i++) {
		World[i] = new RectangleShape[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			World[i][j].setSize(Vector2f(10, 10));
		}
	}

	return World;
}

/**
* directionType : A single instance of a cell in a Game of Life array
* Data-Elements:
* 	int x;	// x direction (positive = right)
* 	int y;	// y direction (positive = down)
* Methods:
* 	None
*/
struct directionType {
	int x;
	int y;
	directionType() {
		x = 1;
		y = 1;
	}
};

/**
* directionType direction:
* @params:
*    int rows - number of rows in 2D array
*    int cols - numberof cols in 2D array
* @returns: **RectangleShape (pointer)
*/
directionType direction(CircleShape shape, Vector2u winSize) {
	Vector2f position = shape.getPosition();

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
	RenderWindow window(VideoMode(600, 600), "Game of Life");

	int frameRate = 5;
	int frameCount = 0;

	Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	gameOfLife Gol(window, width / CELLSIZE, height / CELLSIZE);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
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
