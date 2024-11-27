#include "camera.h"

Camera::Camera(float radius, float height, float angle)
    : _radius(radius), _height(height), _angle(angle) {}

void Camera::update() {
    float cameraX = _radius * cosf(glm::radians(_angle));
    float cameraZ = _radius * sinf(glm::radians(_angle));

    glm::vec3 cameraPos = glm::vec3(cameraX, _height, cameraZ);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f); // смотрим в центр сцены
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, target, up);
    glLoadMatrixf(glm::value_ptr(viewMatrix));
}

void Camera::rotate(float deltaAngle) {
    _angle = deltaAngle;
}

void Camera::changeHeight(float deltaHeight) {
    _height = deltaHeight;
}

void Camera::changeRadius(float deltaRadius) {
    _radius = deltaRadius;
    if (_radius < 0.1f) _radius = 0.1f;
}