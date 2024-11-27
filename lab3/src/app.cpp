#include "app.h"
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <cmath>

CubeApp::CubeApp()
    : window(sf::VideoMode(800, 600), "Custom Perspective", sf::Style::Default, sf::ContextSettings(32)),
      cube(1), commandHandler(angleX, angleY, angleZ, angle, radius, height), camera(radius, height, angle),
      angleX(0.0f), angleY(0.0f), angleZ(0.0f), radius(5.0), height(2.0), angle(0.0) {
    window.setVerticalSyncEnabled(true);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    setPerspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void CubeApp::setPerspective(float fov, float aspect, float zNear, float zFar) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0); // Угол 45°, соотношение 4:3, ближняя плоскость 0.1, дальняя 100.0
    glMatrixMode(GL_MODELVIEW);
}

void CubeApp::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        commandHandler.handleInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef(30, 1.0f, 0.0f, 0.0f);
        glRotatef(45, 0.0f, 1.0f, 0.0f);
        camera.rotate(angle); camera.changeHeight(height); camera.changeRadius(radius);
        camera.update();
        cube.rotateCube(angleX, angleY, angleZ);
        cube.draw();

        window.display();
    }
}
