//
//  Test.hpp
//  SnakeGame
//
//  Created by Mark Hale on 9/23/22.
//

#ifndef Test_hpp
#define Test_hpp
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Fruit.hpp"

class Test{
    //testing window creation
    sf::RenderWindow window;
    
    //testing sprite setup
    sf::Texture texture;
    sf::Image background;
    sf::Sprite sprite;
    
public:
    Test( );
    Test( std::string word );
    void SnakeTest( );
};

#endif /* Test_hpp */
