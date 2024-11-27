#pragma once

#include <SFML/Window.hpp>
#include "object.h"
#include "camera.h"
#include "command_handler.h"

class CubeApp {
private:
    sf::Window window;
    Object3D cube;
    Camera camera;
    CommandHandler commandHandler;
    float angleX, angleY, angleZ;
    float radius, height, angle;

    void setPerspective(float fov, float aspect, float zNear, float zFar);
public:
    CubeApp();
    void run();
};
