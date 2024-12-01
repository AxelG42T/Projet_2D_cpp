#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw();
    int processEvents(sf::Event& event);

private:
    sf::RenderWindow& mWindow;
    std::vector<sf::Text> mOptions;
    sf::Font mFont;
    int selectedIndex = 0;
};

#endif
