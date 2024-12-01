#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Map.h"
#include "Menu.h"
#include "Options.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zelda-like Menu");
    Menu menu(window);
    Options options(window);
    bool inMenu = true;
    bool inOptions = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (inOptions)
                {
                    inOptions = false;
                    inMenu = true;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (inMenu) {
                int menuSelection = menu.processEvents(event);

                if (menuSelection == 0) {
                    inMenu = false;
                    Game game(window);
                    game.run();
                    inMenu = true; 
                }
                else if (menuSelection == 1) {
                    inMenu = false;
                    inOptions = true;
                }
                else if (menuSelection == 2) {
                    window.close();
                }
            }
            else if (inOptions) {
                int optionSelection = options.processEvents(event);
                if (optionSelection == 1) {
                    inOptions = false;
                    inMenu = true;
                }
            }
        }

        window.clear();
        if (inMenu) {
            menu.draw();
        }
        else if (inOptions) {
            options.draw();
        }
        window.display();
    }
    return 0;
}
