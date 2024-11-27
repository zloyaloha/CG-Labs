#pragma once

class CommandHandler {
private:
    float& angleX;
    float& angleY;
    float& angleZ;
    float& angle;
    float& radius;
    float& height;

public:
    CommandHandler(float& x, float& y, float& z, float& cameraCircle, float& cameraRaduis, float& cameraHeight)
        : angleX(x), angleY(y), angleZ(z), angle(cameraCircle), radius(cameraRaduis), height(cameraHeight) {}

    void handleInput();
};

