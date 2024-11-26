#pragma once

class CommandHandler {
private:
    float& angleX;
    float& angleY;
    float& angleZ;

public:
    CommandHandler(float& x, float& y, float& z)
        : angleX(x), angleY(y), angleZ(z) {}

    void handleInput();
};

