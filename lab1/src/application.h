#pragma once

#include <SDL2/SDL.h>
#include "rectangle.h"
#include "input_handler.h"

class Application {
private:
    SDL_Window* window{nullptr};
    SDL_Renderer* renderer{nullptr};
    bool running = true;
    Rectangle rect;
    InputHandler inputHandler;

public:
    Application();
    ~Application();

    bool init();
    void run();
    void cleanup();

private:
    void handleInput();
    void render();
};