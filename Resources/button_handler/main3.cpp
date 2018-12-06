#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Group.h"


class DrawGroup : public Group {
private:
	Tile smiley;
	sf::RectangleShape rectangle;
	float angle;
public:

	DrawGroup() {
		smiley.resetTile(128, 128, "./smiley.png");
		smiley.setOrigin(64, 64);
		smiley.setPosition(150, 150);
		smiley.setSize(32, 32);

		rectangle.setSize(sf::Vector2f(75, 75));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setOutlineThickness(2);
		rectangle.setOutlineColor(sf::Color(0, 255, 0));
		rectangle.setOrigin(50, 50);
		rectangle.setPosition(150, 150);

		angle = .05;

		this->push_back(rectangle);
		this->push_back(smiley);
	}

	void setSmiley(string texture) {
		smiley.setTileTexture(texture);
	}

	void update() {
		rectangle.rotate(angle);
		angle += .001;
	}
};

class ButtonClass : public Tile {
private:
	int originalWidth;
	int originalHeight;
public:
	ButtonClass(int x, int y,int osizex,int osizey,int sizex,int sizey) {
		originalWidth = osizex;
		originalHeight = osizey;
		resetTile(osizex, osizey, "./normal.png");
		setSize(sizex, sizey);
		setOrigin(osizex/2, osizey/2);
		setPosition(x, y);
		
	}

	void pressButton() {
		setTileTexture("./pressed.png");
	}

	void releaseButton() {
		setTileTexture("./normal.png");
	}

	void hoverButton(){
		std::cout<<"hovering"<<std::endl;
		setTileTexture("./pressed.png");
		//resetTile(originalWidth, originalHeight, "./pressed.png");
	}
};

class ButtonHandler {
private:
	vector<ButtonClass> buttonArray;
	bool mouseLeft;
	bool mouseRight;
	int mouseX;
	int mouseY;
public:
	ButtonHandler() {
		_init();
	}

	ButtonHandler(ButtonClass &button){
		buttonArray.push_back(button);
		_init();
	}

	ButtonHandler(vector<ButtonClass> &buttons){
		buttonArray = buttons;
		_init();
	}

	void addButton(ButtonClass &button) {
		buttonArray.push_back(button);
	}


	void setMouseState(sf::RenderWindow &w,sf::Mouse &m){
		sf::Vector2i position = m.getPosition(w);

		mouseLeft = m.isButtonPressed(sf::Mouse::Left);
		mouseRight = m.isButtonPressed(sf::Mouse::Right);
		mouseX = position.x;
		mouseY = position.y;
		_updateButtons();
	}

private:
	void _init(){
		mouseLeft = false;
		mouseRight = false;
		mouseX = 0;
		mouseY = 0;
	}

	void _updateButtons() {
		for (int i = 0; i < buttonArray.size(); i++) {
			std::cout<<"checking button: "<<i<<std::endl;
			if(buttonArray[i].intersectsWith(mouseX,mouseY)){
				buttonArray[i].hoverButton();
			}
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Smiley Face");
	sf::Mouse mouse;

	//DrawGroup DG;
	ButtonClass button1(100,100,440,417,64,64);
	ButtonClass button2(170,170,440,417,64,64);

	ButtonHandler bHandler;

	bHandler.addButton(button1);
	bHandler.addButton(button2);

	bool leftPressed;
	bool rightPressed;  
	sf::Vector2i position; 


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		bHandler.setMouseState(window,mouse);

		window.clear();
		window.draw(button1);
		window.draw(button2);
		window.display();
	}

	return 0;
}
