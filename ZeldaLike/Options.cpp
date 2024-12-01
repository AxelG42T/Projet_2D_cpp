#include "Options.h"

Options::Options(sf::RenderWindow& window) : mWindow(window), mSelectedOption(0), mVolume(5) {
    if (!mFont.loadFromFile("../assets/Font/alagard.TTF")) {
    }

   std::vector<std::string> options = {"Volume", "Retour"};

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(mFont);
        text.setString(options[i] + (i == 0 ? " : " + std::to_string(mVolume) : ""));
        text.setCharacterSize(40);
        text.setFillColor(i == mSelectedOption ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(300.f, 200.f + i * 60.f);
        mOptions.push_back(text);
    }
}

void Options::draw() {
    for (const auto& option : mOptions) {
        mWindow.draw(option);
    }
}

int Options::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            mSelectedOption = (mSelectedOption > 0) ? mSelectedOption - 1 : mOptions.size() - 1;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            mSelectedOption = (mSelectedOption < mOptions.size() - 1) ? mSelectedOption + 1 : 0;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            return mSelectedOption;
        }
        else if (mSelectedOption == 0 && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)) {
            mVolume += (event.key.code == sf::Keyboard::Right) ? 1 : -1;
            mVolume = std::max(0, std::min(mVolume, 10));
            mOptions[0].setString("Volume : " + std::to_string(mVolume));
        }

        for (size_t i = 0; i < mOptions.size(); ++i) {
            mOptions[i].setFillColor(i == mSelectedOption ? sf::Color::Yellow : sf::Color::White);
        }
    }
    return -1;
}
