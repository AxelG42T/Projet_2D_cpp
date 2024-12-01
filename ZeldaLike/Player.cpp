#include "Player.h"

Player::Player(const std::string& spriteSheetPath) : hp(100), currentHp(100), atk(20), mSpeed(200.0f), mCurrentDirection(None), mCurrentColumn(0), mCurrentAction(), mFrameCount(4), mFrameDuration(sf::milliseconds(100)), mIsAttacking(false), mAttackDuration(sf::milliseconds(400)), mIsHitboxActive(false)
{
    if (!mTexture.loadFromFile(spriteSheetPath)) {
    }

    mSprite.setTexture(mTexture);
    mCurrentFrame = sf::IntRect(0, 0, 16, 32);
    mSprite.setTextureRect(mCurrentFrame);
    mSprite.setPosition(150, 100); 

}

void Player::update(sf::Time deltaTime, const Map& gameMap, sf::Vector2u tileSize, Collision& collisionMap, std::vector<Zombie>& enemies)
{
    if (mIsAttacking) {
        if (mAttackClock.getElapsedTime() > mAttackDuration) {
            mIsAttacking = false;
            mIsHitboxActive = false;
            mAttackHitbox = sf::FloatRect();
            mCurrentColumn = 0;
        }
        else {
            setSpriteForAttack(mCurrentDirection);
            checkCollisionsWithEnemies(enemies); 
            return; 
        }
    }

    float distance = mSpeed * deltaTime.asSeconds();
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        movement.y -= distance;
        mCurrentDirection = Up;
        mCurrentAction = Moving;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += distance;
        mCurrentDirection = Down;
        mCurrentAction = Moving;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        movement.x -= distance;
        mCurrentDirection = Left;
        mCurrentAction = Moving;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += distance;
        mCurrentDirection = Right;
        mCurrentAction = Moving;
    }

    if (movement != sf::Vector2f(0.f, 0.f))
    {
        setSpriteForDirection(mCurrentDirection);
        sf::FloatRect futureBounds = mSprite.getGlobalBounds();
        futureBounds.left += movement.x;
        futureBounds.top += movement.y;

        if (!collisionMap.checkCollision(futureBounds)) {
            mSprite.move(movement);
        }
    }
}




void Player::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
    if (mIsHitboxActive) {
        sf::RectangleShape hitboxShape;
        hitboxShape.setPosition(mAttackHitbox.left, mAttackHitbox.top);
        hitboxShape.setSize(sf::Vector2f(mAttackHitbox.width, mAttackHitbox.height));
        hitboxShape.setFillColor(sf::Color(255, 0, 0, 255));
        window.draw(hitboxShape);
    }
}

void Player::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space && !mIsAttacking) {
            mIsAttacking = true;
            mCurrentAction = Attacking;
            mAttackClock.restart();
        }

        if (!mIsAttacking) {
            if (event.key.code == sf::Keyboard::Z) {
                mCurrentDirection = Up;
            }
            else if (event.key.code == sf::Keyboard::S) {
                mCurrentDirection = Down;
            }
            else if (event.key.code == sf::Keyboard::Q) {
                mCurrentDirection = Left;
            }
            else if (event.key.code == sf::Keyboard::D) {
                mCurrentDirection = Right;
            }
        }
    }
    if (event.type == sf::Event::KeyReleased && !mIsAttacking) {
        mCurrentDirection = None;
    }
}

sf::Vector2f Player::getPosition() const
{
    return mSprite.getPosition();
}

void Player::checkCollisionsWithEnemies(std::vector<Zombie>& enemies) {
    if (mIsHitboxActive) {
        for (auto& enemy : enemies) {
            if (mAttackHitbox.intersects(enemy.getBounds())) {
                std::cout << "Hit enemy!" << std::endl;
                enemy.takeDamage(atk); 
            }
        }
    }
}


void Player::setSpriteForDirection(Direction direction)
{
    int spriteWidth = 16; 
    int spriteHeight = 32;

    if (mAnimationClock.getElapsedTime() > mFrameDuration) {
        mCurrentColumn = (mCurrentColumn + 1) % mFrameCount; 
        mAnimationClock.restart();
    }

    switch (direction) {
    case Up:
        mCurrentFrame = sf::IntRect(mCurrentColumn * spriteWidth, spriteHeight * 2, spriteWidth, spriteHeight);
        break;
    case Down:
        mCurrentFrame = sf::IntRect(mCurrentColumn * spriteWidth, 0, spriteWidth, spriteHeight);
        break;
    case Left:
        mCurrentFrame = sf::IntRect(mCurrentColumn * spriteWidth, spriteHeight * 3, spriteWidth, spriteHeight);
        break;
    case Right:
        mCurrentFrame = sf::IntRect(mCurrentColumn * spriteWidth, spriteHeight * 1, spriteWidth, spriteHeight);
        break;
    case None:
        break;
    }
    mSprite.setTextureRect(mCurrentFrame);
}

void Player::setSpriteForAttack(Direction direction) {
    int spriteWidth = 32;  
    int spriteHeight = 32; 
    int attackRow = 0;   
    sf::Vector2f position = mSprite.getPosition();

    switch (direction) {
    case Up:
        attackRow = 5;
        mAttackHitbox = sf::FloatRect(position.x, position.y - spriteHeight, spriteWidth, spriteHeight / 2);
        break;
    case Down:
        attackRow = 4;
        mAttackHitbox = sf::FloatRect(position.x, position.y + spriteHeight, spriteWidth, spriteHeight / 2);
        break;
    case Left:
        attackRow = 7;
        mAttackHitbox = sf::FloatRect(position.x - spriteWidth, position.y, spriteWidth / 2, spriteHeight);
        break;
    case Right:
        attackRow = 6;
        mAttackHitbox = sf::FloatRect(position.x + spriteWidth, position.y, spriteWidth / 2, spriteHeight);
        break;
    default:
        attackRow = 4;
        break;
    }
    mIsHitboxActive = true;

    if (mAnimationClock.getElapsedTime() > mFrameDuration) {
        mCurrentColumn = (mCurrentColumn + 1) % mFrameCount;
        mAnimationClock.restart();
    }
    mCurrentFrame = sf::IntRect(mCurrentColumn * spriteWidth, attackRow * spriteHeight, spriteWidth, spriteHeight);
    mSprite.setTextureRect(mCurrentFrame);
}


void Player::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp <= 0) {
        currentHp = 0;
        std::cout << "Le joueur est mort !" << std::endl;
    }
}

sf::FloatRect Player::getBounds() const
{
    return mSprite.getGlobalBounds();
}



