#include "input_handler.h"

void InputHandler::handleInput(Rectangle& rect, bool& running) {
    SDL_Event event;
    float delta = 5.0f;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    rect.setPosition(rect.getPositionX(), rect.getPositionY() - 10.0f);
                    rect.resetColor(rect.getPositionY());
                    break;
                case SDLK_s:
                    rect.setPosition(rect.getPositionX(), rect.getPositionY() + 10.0f);
                    rect.resetColor(rect.getPositionY());
                    break;
                case SDLK_a:
                    rect.setPosition(rect.getPositionX() - 10.0f, rect.getPositionY());
                    rect.resetColor(rect.getPositionX());
                    break;
                case SDLK_d:
                    rect.setPosition(rect.getPositionX() + 10.0f, rect.getPositionY());
                    rect.resetColor(rect.getPositionX());
                    break;
                case SDLK_q:
                    rect.setAngle(rect.getAngle() - 5.0f);
                    rect.resetColor(rect.getAngle());
                    break;
                case SDLK_e:
                    rect.setAngle(rect.getAngle() + 5.0f);
                    rect.resetColor(rect.getAngle());
                    break;
                case SDLK_z:
                    rect.setScale(rect.getScaleX() - 0.1f, rect.getScaleY() - 0.1f);
                    rect.resetColor(rect.getScaleX());
                    break;
                case SDLK_x:
                    rect.setScale(rect.getScaleX() + 0.1f, rect.getScaleY() + 0.1f);
                   rect.resetColor(rect.getScaleX());
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }
}
