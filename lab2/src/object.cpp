#include "object.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Object3D::Object3D(float size) : _size(size) {
    lights.push_back({glm::vec3(-13, 36, 24), glm::vec3(0.0f, 0.0f, 1.0f)});
    lights.push_back({glm::vec3(-26, -36, -24), glm::vec3(0.0f, 1.0f, 0.0f)});
}

void Object3D::draw() {
    float half = _size / 2.0f;

    glm::vec3 vertices[6][4] = {
        {{-half, -half, -half}, {half, -half, -half}, {half, half, -half}, {-half, half, -half}},
        {{-half, -half, half}, {half, -half, half}, {half, half, half}, {-half, half, half}},
        {{-half, -half, -half}, {-half, half, -half}, {-half, half, half}, {-half, -half, half}},
        {{half, -half, -half}, {half, half, -half}, {half, half, half}, {half, -half, half}},
        {{-half, half, -half}, {half, half, -half}, {half, half, half}, {-half, half, half}},
        {{-half, -half, -half}, {half, -half, -half}, {half, -half, half}, {-half, -half, half}}
    };

    glm::vec3 normals[6] = {
        {0.0f, 0.0f, -1.0f},
        {0.0f, 0.0f, 1.0f},
        {-1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}
    };

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(rotationMatrix));

    for (int i = 0; i < 6; i++) {
        glm::vec3 totalIntensity = {0, 0, 0};
        for (const auto& light : lights) {

            glm::vec4 lightPosition = rotationMatrix * glm::vec4(light.position, 1.0f);
            glm::vec3 lightDir = glm::normalize(glm::vec3(lightPosition) - vertices[i][0]);

            float dotProduct = glm::dot(glm::normalize(normals[i]), lightDir);
            float intensity = std::max(0.0f, dotProduct);
            totalIntensity += intensity * light.color;
        }

        totalIntensity = glm::clamp(totalIntensity, glm::vec3(0.0f), glm::vec3(1.0f));
        glColor3f(totalIntensity.x, totalIntensity.y, totalIntensity.z);

        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            glVertex3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z);
        }
        glEnd();
    }

    glPopMatrix();
}

void Object3D::rotateCube(float angleX, float angleY, float angleZ) {
    _angleX = angleX;
    _angleY = angleY;
    _angleZ = angleZ;
}

void Object3D::addLight(const Light& light) {
    lights.push_back(light);
}
