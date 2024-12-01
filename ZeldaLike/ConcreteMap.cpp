#include "ConcreteMap.h"

bool ConcreteMap::load(const std::string& imagePath)
{
    if (!mTexture.loadFromFile(imagePath)) {
        return false;
    }
    mSprite.setTexture(mTexture);
    return true;
}

void ConcreteMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

