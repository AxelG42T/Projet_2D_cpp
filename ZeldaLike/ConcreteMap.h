#ifndef CONCRETEMAP_H__
#define CONCRETEMAP_H__

#include "Map.h"

class ConcreteMap : public Map {

public:
	bool load(const std::string& imagePath) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Texture mTexture; 
	sf::Sprite mSprite;
};
#endif 
