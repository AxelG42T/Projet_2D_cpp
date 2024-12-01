#include "Game.h"

Game::Game(sf::RenderWindow& window): mWindow(window), mPlayer("../assets/Tileset/character.png"), mCollision({ 32, 32 }), map(std::make_unique<ConcreteMap>()) 
{
    mView.setSize(800, 600);
    mView.setCenter(mPlayer.getPosition());
    mView.zoom(0.4f);

    if (!map->load("../assets/Map/map.png")) {
        std::cerr << "Erreur : Impossible de charger la carte." << std::endl;
    }
}

void Game::run()
{
    sf::Music music;
    if (!music.openFromFile("../assets/Music/music.wav")) {

    }
    music.play();
    music.setLoop(true);
    Collision collision({ 32, 32 });
    collision.loadFromFile("../assets/Map/CollisionData.txt"); 
    for (int i = 0; i < 5; ++i) {
        mZombie.emplace_back("../assets/Tileset/pinkbat_idle_right_anim.gif", sf::Vector2f(rand() % 1920, rand() % 1080));
    }

    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            mWindow.setView(sf::View(visibleArea));
        }
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            mWindow.close();
        }
        mPlayer.handleInput(event);
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2u tileSize(32, 32);
    mPlayer.update(deltaTime, *map, { 32, 32 }, mCollision, mZombie);

    for (auto& zombie : mZombie) {
        zombie.updateState(mPlayer.getPosition());
        zombie.moveToPlayer(mPlayer.getPosition(), deltaTime);
        zombie.attack(mPlayer);
    }
    mPlayer.checkCollisionsWithEnemies(mZombie);
    mView.setCenter(mPlayer.getPosition());
    mWindow.setView(mView);
}

void Game::render()
{
    mWindow.clear();
    map->draw(mWindow, sf::RenderStates::Default);
    mCollision.draw(mWindow);
    for (auto& zombie : mZombie) {
    zombie.draw(mWindow);
    }
    mPlayer.draw(mWindow);
    mWindow.display();
}