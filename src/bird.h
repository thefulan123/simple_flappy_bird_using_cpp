#ifndef BIRD_H
#define BIRD_H

#include <SDL2/SDL.h>

class Bird {
public:
    Bird();
    void reset();
    void flap();
    void update();
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    float getY() const { return y; }

private:
    float x, y;
    float velocity;
    float rotation;
};

#endif
