#include <math.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//https://en.sfml-dev.org/forums/index.php?topic=12278.0
class Ball : public sf::Drawable {
public:
    Ball(int w, int h) {
        width = w;   // window width
        height = h;  // window height

        dx = 1;  // direction x
        dy = 1;  // direction y

        x = (rand() % int(width));   // starting loc x
        y = (rand() % int(height));  // starting loc y

        for (float i = .001; i < .03; i += .001) {
            speeds.push_back(i);
        }

        std::random_shuffle(speeds.begin(), speeds.end());

        s = speeds[0];

        std::cout << s << std::endl;

        if (rand() % 2 == 0) {  // randome direction x
            dx *= -1;
        }
        if (rand() % 2 == 1) {  // random direction y
            dy *= -1;
        }

        // define a circle with radius = 200
        circle = new sf::CircleShape(15.f);

        circle->setFillColor(sf::Color::Green);

        // set the radius to whatever
        circle->setRadius(15.f);

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

    sf::FloatRect getBounds() {
        return circle->getGlobalBounds();
    }

    void changeDirection(sf::FloatRect other) {
        sf::FloatRect thisrec = this->getBounds();

        float oleft = other.left;
        float owidth = other.width;
        float oheight = other.height;
        float otop = other.top;
        float obottom = other.top - other.height;
        float oright = other.left - other.width;

        float tleft = thisrec.left;
        float twidth = thisrec.width;
        float theight = thisrec.height;
        float ttop = thisrec.top;
        float tbottom = thisrec.top - thisrec.height;
        float tright = thisrec.left - thisrec.width;

        float diff_top = abs(ttop - obottom);
        float diff_bot = abs(tbottom - otop);
        float diff_left = abs(tleft - oright);
        float diff_right = abs(tright - oleft);

        std::cout << diff_top << "," << diff_bot << "," << diff_left << "," << diff_right << std::endl;

        if (diff_top < 1 || diff_bot < 1) {
            dy *= -1;
        }
        if (diff_left < 1 || diff_right < 1) {
            dy *= -1;
        }
    }

private:
    sf::CircleShape *    circle;  // reference to our "ball"
    float                x;       // x location
    float                y;       // y location
    float                dx;      // "change" in x
    float                dy;      // "change" in y
    float                width;
    float                height;
    float                s;  // speed
    sf::Vector2f         position;
    std::vector< float > speeds;

    /**
     * virtual = A virtual function a member function which is declared within base class and is re-defined (Overriden) by derived class.
     * function draw:
     *     draw an SFML object to some window
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //states.transform *= getTransform();
        target.draw(*circle, states);
    }

    float randomSpeed() {
        std::random_shuffle(speeds.begin(), speeds.end());
        return speeds[0];
    }
};

std::ostream &operator<<(std::ostream &os, sf::FloatRect rhs) {
    float bottom = rhs.top - rhs.height;
    float right = rhs.left - rhs.width;

    os << "{top: " << rhs.top << ", bottom:" << bottom << ", left: " << rhs.left << ", right: " << right << "}";
    return os;
}

int main() {
    int window_width = 600;
    int window_height = 600;
    int max_balls = 7;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Ball example!");

    Ball **Barray = new Ball *[max_balls];

    for (int i = 0; i < max_balls; i++) {
        Barray[i] = new Ball(window_width, window_height);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < max_balls; i++) {
            Barray[i]->update();
        }

        // http://www.cplusplus.com/forum/beginner/140606/
        // site discusses collisions on "sides" of object
        for (int i = 0; i < max_balls; i++) {
            sf::FloatRect rec1 = Barray[i]->getBounds();
            for (int j = 0; j < max_balls; j++) {
                if (i == j) {
                    continue;
                }
                sf::FloatRect rec2 = Barray[j]->getBounds();
                if (rec1.intersects(rec2)) {
                    Barray[i]->changeDirection(rec2);
                    //Barray[j]->changeDirection(rec1);
                    std::cout << rec1 << std::endl;
                    std::cout << rec2 << std::endl
                              << std::endl;
                }
            }
        }

        window.clear();
        for (int i = 0; i < max_balls; i++) {
            window.draw(*Barray[i]);
        }
        window.display();
    }

    return 0;
}