#pragma once
#include <math.h>

#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::Drawable {
    // Follow with, override, to make sure the function is overridden
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Sprite   m_player;
    sf::Vector2f m_velocity;
    sf::Vector2f m_direction;
    sf::Texture  m_texture;
    sf::Time     m_deltaTime;
    bool         m_isMoving;
    int          m_rotation;
    int          m_gameWidth;
    int          m_gameHeight;
    int          m_speed;
    bool         m_moving;
    int          m_prev_key;
public:
    Player();                               // default constructor
    // Player(const Player &);              // copy constructor
    // Player &operator=(const Player &);   // overload assignment
    void setPosition(sf::Vector2f);         //
    void processEvents();
    void update(sf::Time);
    void move(sf::Vector2f);
    bool isMoving();
    void setMoving(bool);
    void toggleMoving(int);
};

Player::Player() {
    if (!m_texture.loadFromFile("Ship.png", sf::IntRect(0, 0, 99, 75))) {
        std::cout << "Error: Could not load ship resource!" << std::endl;
        exit(0);
    }
    m_player.setTexture(m_texture);
    m_player.setPosition(sf::Vector2f(100, 100));
    m_speed = 10;
    m_moving = false;
    m_prev_key = 0;
}

void Player::setPosition(sf::Vector2f pos) {
    sf::IntRect r = m_player.getTextureRect();
    this->m_player.setPosition(pos.x - r.width / 2, pos.y - r.height / 2);
}

bool Player::isMoving(){
    return m_moving;
}

void Player::setMoving(bool t_moving){
    m_moving = t_moving;
}

void Player::toggleMoving(int key){
    //std::cout<<key<<std::endl;

    if(m_moving == true){
        m_moving = false;
    }else{
        m_moving = true;
    }
}

void Player::processEvents() {
    m_rotation = 0;
}

void Player::update(sf::Time deltaTime) {
    float seconds = deltaTime.asSeconds();
    //std::cout<<seconds<<std::endl;
    //m_player.move(sf::Vector2f(1,1));
}

/**
 * direction =  (0,0) not moving
 *              (1,0) x = right
 *              (0,1) y = down
 *              (-1,0) x = left
 *              (0,-1) y = up
 */
void Player::move(sf::Vector2f direction) {
    m_direction.x *= m_speed;
    m_direction.y *= m_speed;
    m_player.move(m_direction);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_player, states);
}