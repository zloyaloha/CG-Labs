#include "command_handler.h"
#include <SFML/Window.hpp>

void CommandHandler::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angleY -= 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angleY += 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        angleX -= 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        angleX += 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
        angleZ += 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
        angleZ -= 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        angle -= 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        angle += 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        height -= 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        height += 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        radius += 0.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        radius -= 0.3f;
    }
}
