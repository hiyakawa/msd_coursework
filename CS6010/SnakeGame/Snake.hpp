//
//  Snake.hpp
//  SnakeGame
//
//  Group members: Muyuan Zhang, Mark Hale
//

#pragma once
#include "Fruit.hpp"
#include <SFML/Graphics.hpp>

class Snake {
private:
    bool isGameOver;
    sf::Image sAvatar;
    sf::Texture texture;
    sf::Sprite snake;
    
public:
    Snake( );
    Snake( std::string file );
    
    void setColor( );
    void setPosition( ) ;
    void draw( sf::RenderWindow& window );
    
    void move( sf::RenderWindow& window );
    void move( sf::RenderWindow& window, char direction );
    bool gameOver( sf::RenderWindow& window );
    friend bool eatMe ( Snake& snake, Fruit& apple );
    
    sf::Sprite getSprite( );
    sf::Rect<float> getGlobalBounds( );
};
