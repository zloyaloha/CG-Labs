#pragma once

#include <SDL2/SDL.h>
#include "rectangle.h"

class InputHandler {
public:
    void handleInput(Rectangle& rect, bool& running);
};

