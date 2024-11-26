#include "command_handler.h"
#include <SFML/Window.hpp>

void CommandHandler::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angleY -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angleY += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        angleX -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        angleX += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
        angleZ += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
        angleZ -= 1.0f;
    }
}
