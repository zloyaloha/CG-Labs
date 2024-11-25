#include "application.h"

Application::Application() {
    rect.setPosition(400.0, 300.0);
    rect.setScale(1.0, 1.0);
    rect.setAngle(0.);
    rect.setSize(100.0, 100.0);
    rect.setColor({255,0,0,255});
}

Application::~Application() {
    cleanup();
}

bool Application::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    window = SDL_CreateWindow("Rectangle Transformations",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_SHOWN);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer != nullptr;
}

void Application::run() {
    while (running) {
        handleInput();
        update();
        render();
    }
}

void Application::cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::handleInput() {
    inputHandler.handleInput(rect, running);
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    rect.draw(renderer);

    SDL_RenderPresent(renderer);
}
