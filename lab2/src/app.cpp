#include "app.h"
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <cmath>

CubeApp::CubeApp()
    : window(sf::VideoMode(800, 600), "Custom Perspective", sf::Style::Default, sf::ContextSettings(32)),
      cube(1), commandHandler(angleX, angleY, angleZ),
      angleX(0.0f), angleY(0.0f), angleZ(0.0f) {
    window.setVerticalSyncEnabled(true);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    setPerspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void CubeApp::setPerspective(float fov, float aspect, float zNear, float zFar) {
    float f = 1.0f / tan(fov * 0.5f * 3.14159265f / 180.0f);
    float perspective[16] = {
        f / aspect, 0.0f,  0.0f,                          0.0f,
        0.0f,       f,     0.0f,                          0.0f,
        0.0f,       0.0f,  (zFar + zNear) / (zNear - zFar), -1.0f,
        0.0f,       0.0f,  (2.0f * zFar * zNear) / (zNear - zFar), 0.0f
    };
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(perspective);
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
        cube.rotateCube(angleX, angleY, angleZ);
        cube.draw();

        window.display();
    }
}
