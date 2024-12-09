#include "object.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Object3D::Object3D(float size) : _size(size) {
    lights.push_back({glm::vec3(-5, 6, 9), glm::vec3(0.0f, 0.0f, 1.0f)});
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

    // Применяем вращение для нормалей и вершин
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));

    for (int i = 0; i < 6; i++) {
        glm::vec3 totalIntensity = {0, 0, 0};

        glm::vec3 rotatedNormal = glm::normalize(glm::mat3(rotationMatrix) * normals[i]);

        for (const auto& light : lights) {
            glm::vec3 transformedVertex = glm::vec3(rotationMatrix * glm::vec4(vertices[i][0], 1.0f));
            glm::vec3 lightDir = glm::normalize(glm::vec3(light.position) - transformedVertex);

            float dotProduct = glm::dot(glm::normalize(rotatedNormal), lightDir);
            float intensity = std::max(0.0f, dotProduct);
            totalIntensity += intensity * light.color;
        }

        totalIntensity = glm::clamp(totalIntensity, glm::vec3(0.0f), glm::vec3(1.0f));

        // Устанавливаем цвет для грани
        glColor3f(totalIntensity.x, totalIntensity.y, totalIntensity.z);

        // Отрисовываем грань куба
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            glm::vec3 rotatedVertex = glm::vec3(rotationMatrix * glm::vec4(vertices[i][j], 1.0f));
            glVertex3f(rotatedVertex.x, rotatedVertex.y, rotatedVertex.z);
        }
        glEnd();
    }

    glPopMatrix();

    // Отрисовываем источники света
    for (const auto& light : lights) {
        glPushMatrix();
        glColor3f(light.color.r, light.color.g, light.color.b); // Цвет сферы соответствует цвету света
        glTranslatef(light.position.x, light.position.y, light.position.z); // Перемещаемся в позицию света

        GLUquadric* quad = gluNewQuadric();
        gluSphere(quad, 1.0, 16, 16); // Сфера радиуса 1 с детализацией 16x16
        gluDeleteQuadric(quad);

        glPopMatrix();
    }
}


void Object3D::rotateCube(float angleX, float angleY, float angleZ) {
    std::cout << _angleX << ' ' << _angleY << ' ' << _angleZ << std::endl;
    _angleX = angleX;
    _angleY = angleY;
    _angleZ = angleZ;
}

void Object3D::addLight(const Light& light) {
    lights.push_back(light);
}
