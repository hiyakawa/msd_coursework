//
//  SnakeGame.hpp
//  SnakeGame
//
//  Group members: Muyuan Zhang, Mark Hale
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Fruit.hpp"

class SnakeGame{
private:
    sf::Texture texture;
    sf::Image background;
    sf::Sprite treeSprite;
    sf::Sprite newSprite;
    int score;

public:
    SnakeGame( );
    SnakeGame( std::string file, sf::Sprite& sprite, sf::Window& window );
    void MakeGame( );
    void renderWindow( sf::RenderWindow& window, Snake& snake, Fruit& fruit );
    void endGame( sf::RenderWindow& window );
};
