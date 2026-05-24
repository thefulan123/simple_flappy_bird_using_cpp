#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "bird.h"
#include "pipe.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void renderMenu();
    void renderGameOver();
    void renderScore();
    void renderGround();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    GameState state;
    Bird bird;
    PipeManager pipeManager;
    int score;
    Uint32 lastFrameTime;
};

#endif
