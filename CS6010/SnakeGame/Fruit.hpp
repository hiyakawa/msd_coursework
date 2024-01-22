//
//  Fruit.hpp
//  SnakeGame
//
//  Group members: Muyuan Zhang, Mark Hale
//

#pragma once
#ifndef Fruit_hpp
#define Fruit_hpp
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <time.h>//currently unused

class Fruit{
private:
    sf::RectangleShape fruit;
    sf::Texture texture;
    sf::Image background;
    sf::Sprite apple;
    
public:
    Fruit( );
    Fruit( std::string file );
    
    void setColor( );
    void setPosition( ) ;
    void draw( sf::RenderWindow& window );
    
    sf::Sprite getSprite( );
    sf::Rect<float> getGlobalBounds( );
};
#endif /* Fruit_hpp */
