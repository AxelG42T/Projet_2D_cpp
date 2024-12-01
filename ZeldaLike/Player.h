#ifndef PLAYER_H__
#define PLAYER_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Collision.h"
#include "Zombie.h"

class Zombie;

class Player
{
public:
	Player(const std::string& spriteSheetPath);
	void update(sf::Time deltaTime, const Map& gameMap, sf::Vector2u tileSize, Collision& collisionMap, std::vector<Zombie>& enemies);
	void draw(sf::RenderWindow& window);
	void handleInput(sf::Event event);
	sf::Vector2f getPosition() const;
	void checkCollisionsWithEnemies(std::vector<Zombie>& enemies);
	void takeDamage(int damage);
	sf::FloatRect getBounds() const;
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::FloatRect mAttackHitbox;
	bool mIsHitboxActive;
	float mSpeed;
	int hp;
	int currentHp;
	int atk;
	sf::IntRect mCurrentFrame;
	enum Direction { Up, Down, Left, Right, None };
	Direction mCurrentDirection;
	void setSpriteForDirection(Direction direction);
	void setSpriteForAttack(Direction direction);
	
	sf::Clock mAnimationClock;   
	int mCurrentColumn;          
	int mFrameCount;             
	sf::Time mFrameDuration;
	enum ActionState {
		Moving,
		Attacking 
	};
	ActionState mCurrentAction;
	bool mIsAttacking;
	sf::Clock mAttackClock;
	sf::Time mAttackDuration;

};
#endif