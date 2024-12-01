#include "Map.h"

bool Map::load(const std::string& imagePath)
{
    if (!mTexture.loadFromFile(imagePath)) {
        return false;
    }
    mSprite.setTexture(mTexture);
    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite);
}

