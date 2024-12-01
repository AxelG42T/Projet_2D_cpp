#ifndef OPTIONS_H__
#define OPTIONS_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Options
{
public:
    Options(sf::RenderWindow& window);
    void draw();
    int processEvents(sf::Event& event);


private:
    sf::RenderWindow& mWindow;
    std::vector<sf::Text> mOptions;
    sf::Font mFont;
    int mSelectedOption;
    int mVolume;
};
#endif