//
//  Snake.cpp
//  SnakeGame
//
//  Group members: Muyuan Zhang, Mark Hale
//

#include "Snake.hpp"
#include <iostream>
#include "Fruit.hpp"

//global variable used for snake object's directional heading
char cardinalDirection;

//default constructor that instantiates the fields of the class member variables
Snake::Snake( std::string sImage ){
    //initialization of snake object
    sAvatar.loadFromFile( sImage );
    //snake shape, texture, and setting of initial position
    texture.loadFromImage( sAvatar );
    snake.setTexture( texture );
    snake.setScale( 0.1, 0.1 );
    snake.setPosition( 200.0, 500.0 );
    
    //stops the first while loop ie closes the initial window and opens the game-over window
    isGameOver = false;
    //resets the cardinal direction upon game restart
    cardinalDirection = ' ';
}
//draws the snake object to the window
void Snake::draw( sf::RenderWindow& window ){
    window.draw( snake );
}
//keeps snake object moving in the direction it was last heading
void Snake::move( sf::RenderWindow& window ){
    Snake::move( window, cardinalDirection );
}
//changes snake directional orientation based upon hearing keystrokes
void Snake::move( sf::RenderWindow& window, char direction ){
    //orients snake object with window
    float xAxis = snake.getPosition( ).x;
    float yAxis = snake.getPosition( ).y;
    float width = window.getSize( ).x;
    float height = window.getSize( ).y;
    cardinalDirection = direction;
    //checks whether the x-axis and y-axis of the snake object are within the window
    if( xAxis < width && xAxis > 0 && yAxis < height && yAxis > 0 ){
        //uses keystroke input to excute directional change "down"
        if( direction == 'd' ){
            if( yAxis < height ){
                snake.move( sf::Vector2f( 0.0, 0.15 ) );
            }
        }
        //uses keystroke input to excute directional change "up"
        else if( direction == 'u' ){
            if( yAxis > 0 ){
                snake.move( sf::Vector2f( 0.0, -0.15 ) );
            }
        }
        //uses keystroke input to excute directional change "right"
        else if( direction == 'r' ){
            if( xAxis < width ){
                snake.move( sf::Vector2f( 0.15, 0.0 ) );
            }
        }
        //uses keystroke input to excute directional change "left"
        else if( direction == 'l' ){
            if( xAxis > 0 ){
                snake.move( sf::Vector2f( -0.15, 0.0 ) );
            }
        }
    }
    //out of bounds end game condition
    else {
        isGameOver = true;
        gameOver( window );
    }
}
//terminates while loop in order to display "game over" window
bool Snake::gameOver( sf::RenderWindow& window ){
    window.clear( sf::Color::Black );
    //triggers next while loop
    return isGameOver;
}
//detects a collision with an apple object
bool eatMe( Snake& snake, Fruit& apple ){
    return( snake.getSprite( ).getGlobalBounds( ).intersects( apple.getSprite( ).getGlobalBounds( ) ) );
}
//returns snake bounds for use in eatMe( )
sf::Sprite Snake::getSprite( ){
    return snake;
}
//returns global bounds for use in eatMe( )
sf::Rect<float> Snake::getGlobalBounds( ){
    return snake.getGlobalBounds( );
}
