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

public:
	ButtonClass(int x, int y,int osizex,int osizey,int sizex,int sizey) {
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
};

class ButtonHandler {
private:
	vector<ButtonClass> buttonArray;
public:
	ButtonHandler() {

	}

	void addButton(ButtonClass &button) {
		buttonArray.push_back(button);
	}

	void checkPressAll(int x,int y) {
		for (int i = 0; i < buttonArray.size(); i++) {
			
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Smiley Face");

	//DrawGroup DG;
	ButtonClass button1(100,100,440,417,64,64);
	ButtonClass button2(170,170,440,417,64,64);

	//ButtonHandler handler;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			button1.pressButton();
			button2.pressButton();
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			button1.releaseButton();
			button2.releaseButton();
		}

		window.clear();
		window.draw(button1);
		window.draw(button2);
		window.display();
	}

	return 0;
}
