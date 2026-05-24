#include "bird.h"
#include "config.h"
#include <cmath>

Bird::Bird() {
    reset();
}

void Bird::reset() {
    x = BIRD_X;
    y = SCREEN_HEIGHT / 2;
    velocity = 0;
    rotation = 0;
}

void Bird::flap() {
    velocity = FLAP_STRENGTH;
}

void Bird::update() {
    velocity += GRAVITY;
    if (velocity > BIRD_MAX_VEL) velocity = BIRD_MAX_VEL;
    y += velocity;

    if (velocity < -2) rotation = -25;
    else if (velocity > 2) rotation = 25;
    else rotation = 0;
}

void Bird::render(SDL_Renderer* renderer) {
    SDL_Rect rect = getRect();

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 200, 100, 0, 255);
    SDL_RenderDrawLine(renderer, x + BIRD_SIZE / 2, y + BIRD_SIZE / 2,
                       x + BIRD_SIZE + 8, y + BIRD_SIZE / 2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect eye = {static_cast<int>(x + BIRD_SIZE - 6), static_cast<int>(y) + 4, 4, 4};
    SDL_RenderFillRect(renderer, &eye);
}

SDL_Rect Bird::getRect() const {
    return {static_cast<int>(x), static_cast<int>(y), BIRD_SIZE, BIRD_SIZE};
}
