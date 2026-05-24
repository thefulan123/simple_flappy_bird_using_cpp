#ifndef PIPE_H
#define PIPE_H

#include <SDL2/SDL.h>
#include <vector>

struct Pipe {
    int x;
    int gapY;
    bool scored;
};

class PipeManager {
public:
    PipeManager();
    void reset();
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& birdRect) const;
    int getScore() const { return score; }
    std::vector<Pipe>& getPipes() { return pipes; }

private:
    std::vector<Pipe> pipes;
    int frameCounter;
    int score;
};

#endif
