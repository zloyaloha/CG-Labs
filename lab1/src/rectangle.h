#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>

class Rectangle {
    private:
        float pos_x, pos_y;
        float width, height;
        float angle;
        float scale_x, scale_y;
        SDL_Color color;
    public:
        Rectangle() = default;
        void setPosition(float new_x, float new_y);
        void setSize(float new_width, float new_height);
        void setAngle(float new_angle);
        void setScale(float new_scale_x, float new_scale_y);
        void setColor(const SDL_Color& new_color);

        float getPositionX();
        float getPositionY();
        float getWidth();
        float getHeight();
        float getAngle();
        float getScaleX();
        float getScaleY();
        SDL_Color getColor();

        void resetColor(float delta);
        void draw(SDL_Renderer* renderer) const;
};