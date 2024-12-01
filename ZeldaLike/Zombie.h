#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Player.h"
#include <cmath>
#include <iostream>

class Player;

enum class ZombieState {
    Idle,
    Chasing,
    Attacking
};

class Zombie
{
public:
    Zombie(const char* path, sf::Vector2f startPosition);
    void draw(sf::RenderWindow& window);
    void moveToPlayer(sf::Vector2f playerPosition, sf::Time deltaTime);
    void updateState(sf::Vector2f playerPosition);
    void takeDamage(int damage);
    void attack(Player& player);
    bool checkCollision(const sf::FloatRect& playerBounds);
    bool isAlive = true;
    sf::FloatRect getBounds() const;
    void update(Player& player, sf::Time deltaTime);
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::FloatRect mBounds;
    int hp;
    int currentHp;
    int atk;  
    float speed; 
    float rayon;  
    ZombieState state;
    sf::Clock attackClock;  
    sf::Time attackCooldown;  
    sf::Time lastAttackTime;  
};

#endif
