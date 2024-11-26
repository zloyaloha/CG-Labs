#pragma once

#include <SFML/Window.hpp>
#include "object.h"
#include "command_handler.h"

class CubeApp {
private:
    sf::Window window;
    Object3D cube;
    CommandHandler commandHandler;
    float angleX, angleY, angleZ;

    void setPerspective(float fov, float aspect, float zNear, float zFar);
    void setupLight();
public:
    CubeApp();
    void run();
};
