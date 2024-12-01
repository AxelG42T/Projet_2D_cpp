#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(const char* path, sf::Vector2f startPosition)
    : hp(100), currentHp(100), atk(10), speed(50.f), rayon(50.f), state(ZombieState::Idle),
    attackCooldown(sf::seconds(1.f)), isAlive(true)
{
    if (!texture.loadFromFile(path)) {
    }
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
    lastAttackTime = sf::Time::Zero;
}

void Zombie::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Zombie::moveToPlayer(sf::Vector2f playerPosition, sf::Time deltaTime) {
    if (state == ZombieState::Chasing) {
        sf::Vector2f direction = playerPosition - sprite.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction /= length;
            sprite.move(direction * speed * deltaTime.asSeconds());
        }
    }
}

void Zombie::updateState(sf::Vector2f playerPosition) {
    float distance = std::sqrt(std::pow(playerPosition.x - sprite.getPosition().x, 2) +
        std::pow(playerPosition.y - sprite.getPosition().y, 2));
    if (distance <= rayon) {
        state = ZombieState::Attacking;
    }
    else if (distance <= 200.f) {
        state = ZombieState::Chasing;
    }
    else {
        state = ZombieState::Idle;
    }
}

void Zombie::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp <= 0) {
        currentHp = 0;
        std::cout << "Zombie éliminé !" << std::endl;
        isAlive = false;
    }
}

void Zombie::attack(Player& player) {
    if (state == ZombieState::Attacking && lastAttackTime + attackCooldown <= attackClock.getElapsedTime()) {
        sf::FloatRect playerBounds = player.getBounds();
        if (sprite.getGlobalBounds().intersects(playerBounds)) {
            player.takeDamage(atk);
            std::cout << "Zombie attaque le joueur !" << std::endl;
            lastAttackTime = attackClock.getElapsedTime();
        }
    }
}

bool Zombie::checkCollision(const sf::FloatRect& playerBounds) {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

sf::FloatRect Zombie::getBounds() const {
    return sprite.getGlobalBounds();
}

void Zombie::update(Player& player, sf::Time deltaTime) {
    if (!isAlive) return;

    updateState(player.getPosition());
    moveToPlayer(player.getPosition(), deltaTime);
    attack(player);
}
