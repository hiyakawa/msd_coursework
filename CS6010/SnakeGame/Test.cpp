//
//  Test.cpp
//  SnakeGame
//
//  Created by Mark Hale on 9/23/22.
//

#include "Test.hpp"
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "SnakeGame.hpp"
#include "Fruit.hpp"

//default constructor
Test::Test( ){
}

//tests constructor
Test::Test( std::string word ){
    window.create( sf::VideoMode( 800, 600 ), "My window" );
    background.loadFromFile( "/Users/computer/MSD/cs6010-labs/Day20/SnakeGame/SnakeGame/Sprites/app.png" );
    texture.loadFromImage( background );
    sprite.setTexture( texture );
    sprite.setScale( 1.1, 1.0 );
    sprite.setPosition( window.getSize( ).x - sprite.getGlobalBounds( ).width* 1.25, window.getSize( ).y - sprite.getGlobalBounds( ).height* 1.2 );
    
    //testing draw simple shape onto screen
    sf::RectangleShape square;
    square.scale( 10.0, 10.0 );
    square.setSize( sf::Vector2f( 10.0, 10.0 ) );
    square.setFillColor( sf::Color::Red );
    square.setPosition( 300.0, 400.0 );
    
    //testing while loop runs and displays properly
    while ( window.isOpen( ) ) {
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed ){
                window.close( );
            }
        }
        window.clear( sf::Color::Cyan );
        window.draw( square );
        window.display( );
    }
}

//tests SnakeGame constructor and methods
void Test::SnakeTest( ){
    SnakeGame sg;
    sg.MakeGame( );
}
