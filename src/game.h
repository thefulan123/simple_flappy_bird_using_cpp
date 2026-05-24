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
    void renderBackground();
    void renderMenu();
    void renderScore();
    void renderGameOver();
    void renderGround();
    void renderPanel(int x, int y, int w, int h, SDL_Color color);

    void drawChar(int x, int y, char c, int size, SDL_Color color);
    void drawText(int x, int y, const char* text, int size, SDL_Color color);
    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    GameState state;
    Bird bird;
    PipeManager pipeManager;
    int score;
    int highScore;
    int blinkCounter;
    Uint32 lastFrameTime;
};

#endif
