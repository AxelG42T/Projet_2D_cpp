#ifndef GAME_H__
#define	GAME_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Zombie.h"
#include "Map.h"
#include "Collision.h"
#include "ConcreteMap.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    sf::RenderWindow& mWindow;
    sf::View mView;
    Player mPlayer;
    std::vector<Zombie> mZombie;
    std::unique_ptr<Map> map;
    Collision mCollision;
};

#endif
