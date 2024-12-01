#ifndef COLLISION_H__
#define COLLISION_H__



#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Collision {
private:
    std::vector<std::vector<int>> mCollisionData;
    sf::Vector2u mTileSize;
    std::vector<sf::FloatRect> mCollisions;
public:
    Collision(sf::Vector2u tileSize);
    void loadFromFile(const std::string& filePath);
    bool checkCollision(const sf::FloatRect& playerBounds);
    void draw(sf::RenderWindow& window);   
};
#endif
