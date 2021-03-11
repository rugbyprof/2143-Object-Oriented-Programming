#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Player.hpp"

class Game {
    sf::RenderWindow *m_window;   // window to draw to
    Player *          m_player;   // player instance
    bool              m_running;  // is running boolean
    int               m_width;
    int               m_height;
    sf::Vector2f      m_pos;
    void              processEvents();             // process things that happen
    void              update(sf::Time deltaTime);  // update based on deltaTime
    void              render();                    // render screen
public:
    Game();  // default constructor
    Game(sf::RenderWindow *);
    void run();  // run game method
};

/**
 * Default constructor inits all values with default values ... duh.
 */
Game::Game() {
    this->m_width = 800;
    this->m_height = 600;
    this->m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "SFML Game Template");
    this->m_player = new Player;
    this->m_running = true;

    sf::Vector2f pos(m_width / 2, m_height / 2);
    this->m_player->setPosition(pos);
}

/**
 * @brief Construct a new Game:: Game object
 * 
 * @param t_window 
 */
Game::Game(sf::RenderWindow *t_window) {
    this->m_window = t_window;
    this->m_running = true;
    this->m_player = new Player;

    sf::Vector2u size = m_window->getSize();
    this->m_height = size.y;
    this->m_width = size.x;
    m_pos = sf::Vector2f(size.x / 2, size.y / 2);
    m_player->setPosition(m_pos);
}

/**
 * 
 */
void Game::run() {
    sf::Clock clock;
    sf::Time  lastStep;
    sf::Time  fixedStep = sf::seconds(1.f / 60);

    // Implements the "Minimum time step" model
    // Game runs as fast as it can, passing last delta to update()
    while (m_running) {
        processEvents();
        lastStep = clock.restart();
        while (lastStep > fixedStep) {
            lastStep -= fixedStep;
            update(fixedStep);
        }
        update(lastStep);
        render();
    }
    m_window->close();
}

void Game::processEvents() {
    sf::Event event;
    
    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_running = false;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape){
                    m_running = false;
                }

                
                m_player->toggleMoving(event.key.code);
                
                
                //std::cout<<event.key.code<<std::endl;

                
            default:
                break;
        }
        if(m_player->isMoving()){
            std::cout<<"1"<<std::endl;
        }else{
            std::cout<<"0"<<std::endl;
        }
        if (m_player->isMoving()){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                m_player->move(sf::Vector2f(0, -1));
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                m_player->move(sf::Vector2f(0, 1));
            }
        }
    }
    //player.processEvents();
}

void Game::update(sf::Time deltaTime) {
    m_player->update(deltaTime);
}

/**
 * 
 * 
 */
void Game::render() {
    m_window->clear();
    m_window->draw(*m_player);
    m_window->display();
}
