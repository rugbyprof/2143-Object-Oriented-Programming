#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


//https://en.sfml-dev.org/forums/index.php?topic=12278.0
class Ball : public sf::Drawable {
public:
    Ball(int w, int h) {
        width = w;  // window width
        height = h; // window height

        dx = 1; // direction x
        dy = 1; // direction y

        x = (rand() % int(width));  // starting loc x
        y = (rand() % int(height)); // starting loc y

        for(float i=.001;i < .03; i+= .001){
            speeds.push_back(i);
        }

        std::random_shuffle ( speeds.begin(), speeds.end() );

        s = speeds[0];

        std::cout<<s<<std::endl;


        if (rand() % 2 == 0) { // randome direction x
            dx *= -1;
        }
        if (rand() % 2 == 1) { // random direction y
            dy *= -1;
        }

        // define a circle with radius = 200
        circle = new sf::CircleShape(5.f);

        circle->setFillColor(sf::Color::Green);

        // set the radius to whatever
        circle->setRadius(5.f);

        // change the number of sides (points) to 100
        //circle->setPointCount(100);

        circle->setPosition(sf::Vector2f(x, y));

    }

    void update() {

        position = circle->getPosition();

        // std::cout<<"pos: "<<position.x<<","<<position.y<<std::endl;
        // std::cout<<"coor: "<<x<<","<<y<<std::endl;

        if (position.x >= width) {
            //circle->setPosition(width,position.y);
            dx = dx * -1;
        }

        if (position.y >= height) {
            //circle->setPosition(position.x,height);
            dy = dy * -1;
        }

        if (position.x < 0) {
            //position.x = 0;
            dx = dx * -1;
        }

        if (position.y < 0) {
            //position.y = 0;
            dy = dy * -1;
        }

        x = position.x + (s * dx);
        y = position.y + (s * dy);

        // std::cout<<"dx"<<(d * dx)<<std::endl;
        // std::cout<<"dy"<<(d * dy)<<std::endl;

        //circle->move(sf::Vector2f(x, y));
        circle->setPosition(sf::Vector2f(x, y));
    }

private:
    sf::CircleShape *circle; // reference to our "ball"
    float x;                 // x location
    float y;                 // y location
    float dx;                // "change" in x
    float dy;                // "change" in y
    float width;
    float height;
    float s; // speed
    sf::Vector2f position;
    std::vector<float> speeds;

    /**
     * virtual = A virtual function a member function which is declared within base class and is re-defined (Overriden) by derived class.
     * function draw:
     *     draw an SFML object to some window
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //states.transform *= getTransform();
        target.draw(*circle, states);
    }

    float randomSpeed(){
        std::random_shuffle ( speeds.begin(), speeds.end() );
        return speeds[0];
    }
};

int main() {
    int window_width = 600;
    int window_height = 600;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Ball example!");

    Ball **Barray = new Ball *[50];


    for (int i = 0; i < 50; i++) {
        Barray[i] = new Ball(window_width, window_height);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < 50; i++) {
            Barray[i]->update();
        }

        window.clear();
        for (int i = 0; i < 50; i++) {
            window.draw(*Barray[i]);
        }
        window.display();
    }

    return 0;
}