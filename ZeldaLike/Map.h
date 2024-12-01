#ifndef MAP_H__
#define MAP_H__

#include <SFML/Graphics.hpp>
#include <vector>

class Map : public sf::Transformable, public sf::Drawable
{
private:
    sf::Texture mTexture;
    sf::Sprite mSprite;

public:
    virtual bool load(const std::string& imagePath) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

#endif;