#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : mWindow(window) {
    if (!mFont.loadFromFile("../assets/Font/alagard.TTF")) {
    }

    std::vector<std::string> options = { "Jouer", "Options", "Quitter" };
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(mFont);
        text.setString(options[i]);
        text.setCharacterSize(40);
        text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(300.f, 200.f + i * 60.f);
        mOptions.push_back(text);
    }
}

void Menu::draw() {
    for (const auto& option : mOptions) {
        mWindow.draw(option);
    }
}

int Menu::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : mOptions.size() - 1;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex < mOptions.size() - 1) ? selectedIndex + 1 : 0;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            return selectedIndex;
        }

        for (size_t i = 0; i < mOptions.size(); ++i) {
            mOptions[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        }
    }
    return -1;
}
