#include "rectangle.h"
#include <iostream>

void Rectangle::setPosition(float new_x, float new_y) {
    pos_x = new_x; pos_y = new_y;
}

void Rectangle::setSize(float new_width, float new_height) {
    width = new_width; height = new_height;
}

void Rectangle::setAngle(float new_angle) {
    angle = new_angle;
}

void Rectangle::setScale(float new_scale_x, float new_scale_y) {
    scale_x = new_scale_x; scale_y = new_scale_y;
}

void Rectangle::setColor(const SDL_Color& new_color) {
    color = new_color;
}

void Rectangle::resetColor(float delta) {
    delta = fmod(delta, 360);
    color.r = 255 * (0.5f + 0.5f * std::sin(delta * 3.14159f / 180.0f)); // Красный
    color.g = 255 * (0.5f + 0.5f * std::sin((delta + 120) * 3.14159f / 180.0f)); // Зеленый
    color.b = 255 * (0.5f + 0.5f * std::sin((delta + 240) * 3.14159f / 180.0f)); // Синий
}

float Rectangle::getPositionX() {
    return pos_x;
}

float Rectangle::getPositionY() {
    return pos_y;
}

float Rectangle::getWidth() {
    return width;
}

float Rectangle::getHeight() {
    return height;
}

float Rectangle::getAngle() {
    return angle;
}

float Rectangle::getScaleX() {
    return scale_x;
}

float Rectangle::getScaleY() {
    return scale_y;
}


void Rectangle::draw(SDL_Renderer* renderer) const {
    float halfWidth = (width * scale_x) / 2.0f;
    float halfHeight = (height * scale_y) / 2.0f;

    SDL_FPoint vertices[4] = {
        {-halfWidth, -halfHeight},
        { halfWidth, -halfHeight},
        { halfWidth,  halfHeight},
        {-halfWidth,  halfHeight}
    };

    SDL_FPoint transformed[4];
    float radAngle = angle * M_PI / 180.0f;
    float cosA = std::cos(radAngle);
    float sinA = std::sin(radAngle);

    for (int i = 0; i < 4; ++i) {
        float rotatedX = vertices[i].x * cosA - vertices[i].y * sinA;
        float rotatedY = vertices[i].x * sinA + vertices[i].y * cosA;

        transformed[i].x = rotatedX + pos_x;
        transformed[i].y = rotatedY + pos_y;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        SDL_RenderDrawLineF(renderer, transformed[i].x, transformed[i].y,
                                        transformed[next].x, transformed[next].y);
    }
} 