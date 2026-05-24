#include "pipe.h"
#include "config.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

PipeManager::PipeManager() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    reset();
}

void PipeManager::reset() {
    pipes.clear();
    frameCounter = 0;
    score = 0;
}

void PipeManager::update() {
    frameCounter++;

    if (frameCounter >= PIPE_SPAWN_INTERVAL) {
        frameCounter = 0;
        int gapY = std::rand() % (SCREEN_HEIGHT - GROUND_HEIGHT - PIPE_GAP - 100) + 80;
        pipes.push_back({SCREEN_WIDTH, gapY, false});
    }

    for (auto& pipe : pipes) {
        pipe.x -= PIPE_SPEED;
    }

    pipes.erase(
        std::remove_if(pipes.begin(), pipes.end(),
            [](const Pipe& p) { return p.x + PIPE_WIDTH < 0; }),
        pipes.end()
    );
}

void PipeManager::render(SDL_Renderer* renderer) {
    for (const auto& pipe : pipes) {
        // Pipe top
        SDL_Rect topPipe = {pipe.x, 0, PIPE_WIDTH, pipe.gapY};
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderFillRect(renderer, &topPipe);

        // Top pipe edge
        SDL_Rect topEdge = {pipe.x - 4, pipe.gapY - 20, PIPE_WIDTH + 8, 20};
        SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
        SDL_RenderFillRect(renderer, &topEdge);

        // Pipe bottom
        int bottomY = pipe.gapY + PIPE_GAP;
        SDL_Rect bottomPipe = {pipe.x, bottomY, PIPE_WIDTH, SCREEN_HEIGHT - bottomY};
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderFillRect(renderer, &bottomPipe);

        // Bottom pipe edge
        SDL_Rect bottomEdge = {pipe.x - 4, bottomY, PIPE_WIDTH + 8, 20};
        SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
        SDL_RenderFillRect(renderer, &bottomEdge);
    }
}

bool PipeManager::checkCollision(const SDL_Rect& birdRect) const {
    for (const auto& pipe : pipes) {
        SDL_Rect topPipe = {pipe.x, 0, PIPE_WIDTH, pipe.gapY};
        SDL_Rect bottomPipe = {pipe.x, pipe.gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT};

        if (SDL_HasIntersection(&birdRect, &topPipe) ||
            SDL_HasIntersection(&birdRect, &bottomPipe)) {
            return true;
        }
    }
    return false;
}
