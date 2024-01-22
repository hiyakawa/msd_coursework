//
//  main.cpp
//  SnakeGame
//
//  Group members: Muyuan Zhang, Mark Hale
//

#include "Snake.hpp"
#include "SnakeGame.hpp"
#include <SFML/Audio.hpp>
#include "Fruit.hpp"
#include "Test.hpp"
#include <iostream>

int main( int argc, const char * argv[] ) {
    //game instantiation
    SnakeGame game;
    game.MakeGame( );
    
    //test calls
    //Test test;
    //Test testing( "test" );
    //test.SnakeTest( );
    
    return 0;
}
