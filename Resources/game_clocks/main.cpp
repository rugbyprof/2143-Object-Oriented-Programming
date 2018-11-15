#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <limits>

#include "Tile.h"
#include "Group.h"

using namespace std;

// https://d2trtkcohkrm90.cloudfront.net/images/emoji/apple/ios-11/128/slightly-smiling-face.png

const int HOUR = 3600;
const int MINUTE = 60;

class TimeFormat{
public:
    TimeFormat(){}

    int getNumDigits(long seconds){
        int digits = 0;
        int divisor = 1;

        while((seconds / divisor) > 0){
            digits++;
            divisor *= 10;
        }
        return digits-1;
    }

    string HHMMSS(int seconds){

        int iSeconds=0;
        int iHours=0;
        int iMinutes=0;
        string negate = "";

        if(seconds < 0){
            negate = "-";
            seconds *= -1;
            iSeconds = seconds;
        }else{
            iSeconds = seconds;
        }

        iHours = getHours(iSeconds);
        iSeconds = remHours(iSeconds);
        iMinutes = getMinutes(iSeconds);
        iSeconds = remMinutes(iSeconds);
        
        string sHours = to_string(iHours);
        string sMinutes = to_string(iMinutes);
        string sSeconds = to_string(iSeconds);

        if(iHours < 10){
            sHours = "0" + sHours;
        }

        if(iMinutes < 10){
            sMinutes = "0" + sMinutes;
        }

        if(iSeconds < 10){
            sSeconds = "0" + sSeconds;
        }

        return negate + sHours + ":" + sMinutes + ":" + sSeconds;
    }

    int getHours(int seconds){
        return seconds / HOUR;
    }

    int remHours(int seconds){
        return seconds % HOUR;
    }

    int getMinutes(int seconds){
        return seconds / MINUTE;
    }

    int remMinutes(int seconds){
        return seconds % MINUTE;
    }

};

class Counter : public TimeFormat, public sf::Clock{
private:
    long StartVal;      // Starting clock value (e.g 0, -100 , 1000 , 867, etc.)
    long StopVal;       // Stopping value (when clock is finished) (e.g 0, -100 , 1000 , 867, etc.)
    string Format;      // Format to return clock: HH:MM , MM:SS, SS, SSS, SSSS , MM:SS:mm (default SS)
    bool Finished;      // Has clock reached its limit
    string ClockString; // String version of clock value 
    bool Increment;


    void _init(long start,long stop,string format){
        StartVal = start;
        StopVal = stop;
        Format = format;
        Increment = true;  
        if(start>stop){
            Increment = false;
        }

        restart(); // sf::Clock method
    }

public:
    Counter(){
        _init(0,LONG_MAX,"SS");
    }

    Counter(long start,long stop,string format="SS"){
        _init(start,stop,format);
    }

    void setLimits(long start,long stop){
        StartVal = start;
        StopVal = stop;
        _init(start,stop,Format);
    }

    string getCurrent(){
        
        if(Finished){
            return ClockString;
        }

        long current;

        if(Increment){
                      // sf::Clock method
            current = getElapsedTime().asSeconds() + StartVal;
            if (current >= StopVal){
                Finished = true;
            }
        }else{
                                // sf::Clock method
            current = StartVal - getElapsedTime().asSeconds();
            if (current <= StopVal){
                Finished = true;
            }
        }
                      //Timeformat method
        ClockString = HHMMSS(current);

        return ClockString;
    }

    bool isFinished(){
        return Finished;
    }
};




class DrawMe : public Group, public Tile{
private:
    sf::RectangleShape rectangle;
    float angle;
    float dx;
    float dy;
public:
    DrawMe(){
        //Tile methods
        Tile::initTile(128,128,"./smiley.png");
        Tile::setPosition(sf::Vector2f(100.0, 100.0));
        Tile::setSize(64,64);
        Tile::setOrigin(64.0,64.0);

        rectangle.setSize(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setOrigin(50,50);
        rectangle.setPosition(100, 100);

        angle = .01;
        
        this->push_back(rectangle);
        this->push_back(smiley);

        dx = 12.5;
        dy = 12.5;

    }

    void changeSmiley(string image){
        Tile::setTileTexture(image);
    }

    void update(int width,int height){

        int buffer = 25;

        sf::Vector2f pos = Tile::getPosition();

        rectangle.rotate(angle);

        if(pos.x > (width-buffer) || pos.x < (0 + buffer)){
            dx = dx * -1;
        }

        if(pos.y > (height-buffer) || pos.y < (0 + buffer)){
            dy = dy * -1;
        }

        Tile::move(dx,dy);



        angle += .0001;
    }
};

class GameClock{
private:
    sf::Text text;          // var to hold clock digits
    sf::Clock gameClock;    // SFML clock type
    sf::Time startTime;
    sf::Font font;
    sf::Color textColor;
    int fontSize;
public:
    GameClock(){
        gameClock.restart();
        if (!font.loadFromFile("Segment7Standard.otf")) {
            cout << "Error loading font 'Segment7Standard.otf'...";
            exit(0);
        }

        fontSize = 48;

        textColor = sf::Color(0, 255, 0); // green

        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("0");

        text.setCharacterSize(fontSize); // in pixels, not points!

        text.setFillColor(textColor);

        text.setStyle(sf::Text::Bold);

    }

    void printClock(sf::RenderWindow &window,int gameWidth, int gameHeight){

        int itime = gameClock.getElapsedTime().asSeconds();
        string stime = to_string(itime);

        text.setString(stime);

        float textWidth = text.getLocalBounds().width;
        float textHeight = text.getLocalBounds().height;

        sf::Vector2f coord(gameWidth / 2,gameHeight / 2);
        sf::Vector2f origin(textWidth / 2.0f, textHeight / 2.0f);

        text.setOrigin(origin);
        text.setPosition(coord);

        window.draw(text);
    }
};

int main()
{
    int wWidth=sf::VideoMode::getDesktopMode().width / 2;
    int wHeight=sf::VideoMode::getDesktopMode().height / 2;

    sf::RenderWindow window(sf::VideoMode(wWidth,wHeight), "SFML Smiley!");

    Counter C(4000,-3);
    DrawMe D;
    GameClock G;

    
    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //         D.changeSmiley("./surprised.png");
    //     }

    //     if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //         D.changeSmiley("./smiley.png");
    //     }

    //     cout<<C.getCurrent()<<endl;

    //     window.clear();
    //     window.draw(D);
    //     G.printClock(window,wWidth,wHeight);
    //     D.update(wWidth,wHeight);

    //     window.display();
    // }


    TimeFormat T;
    cout<<T.getNumDigits(99494949494)<<endl;

    return 0;
}