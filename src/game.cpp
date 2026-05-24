#include "game.h"
#include "config.h"
#include <iostream>
#include <sstream>

Game::Game() : window(nullptr), renderer(nullptr), running(false),
               state(GameState::MENU), score(0), lastFrameTime(0) {}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(GAME_TITLE.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Game::run() {
    running = true;
    lastFrameTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        lastFrameTime = currentTime;

        handleEvents();
        update();
        render();

        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < 1000 / FPS) {
            SDL_Delay((1000 / FPS) - frameTime);
        }
    }
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }

        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                case SDLK_UP:
                    if (state == GameState::MENU || state == GameState::GAME_OVER) {
                        state = GameState::PLAYING;
                        bird.reset();
                        pipeManager.reset();
                        score = 0;
                    } else if (state == GameState::PLAYING) {
                        bird.flap();
                    }
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

void Game::update() {
    if (state != GameState::PLAYING) return;

    bird.update();
    pipeManager.update();

    if (bird.getY() + BIRD_SIZE >= SCREEN_HEIGHT - GROUND_HEIGHT ||
        bird.getY() <= 0 ||
        pipeManager.checkCollision(bird.getRect())) {
        state = GameState::GAME_OVER;
    }

    for (auto& pipe : pipeManager.getPipes()) {
        if (!pipe.scored && pipe.x + PIPE_WIDTH < BIRD_X) {
            pipe.scored = true;
            score++;
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    if (state == GameState::MENU) {
        renderMenu();
    } else if (state == GameState::PLAYING) {
        pipeManager.render(renderer);
        bird.render(renderer);
        renderGround();
        renderScore();
    } else if (state == GameState::GAME_OVER) {
        pipeManager.render(renderer);
        bird.render(renderer);
        renderGround();
        renderScore();
        renderGameOver();
    }

    SDL_RenderPresent(renderer);
}

void Game::renderMenu() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    const char* title = "FLAPPY BIRD";
    const char* instr1 = "Tekan SPACE untuk mulai";
    const char* instr2 = "Tekan ESC untuk keluar";

    for (const char* c = title; *c; c++) {
        SDL_Rect r;
        r.x = SCREEN_WIDTH / 2 - 80 + (c - title) * 16;
        r.y = SCREEN_HEIGHT / 2 - 60;
        r.w = 12;
        r.h = 18;
        SDL_RenderFillRect(renderer, &r);
    }

    for (const char* c = instr1; *c; c++) {
        SDL_Rect r;
        r.x = SCREEN_WIDTH / 2 - 110 + (c - instr1) * 8;
        r.y = SCREEN_HEIGHT / 2;
        r.w = 7;
        r.h = 10;
        SDL_RenderFillRect(renderer, &r);
    }

    for (const char* c = instr2; *c; c++) {
        SDL_Rect r;
        r.x = SCREEN_WIDTH / 2 - 110 + (c - instr2) * 8;
        r.y = SCREEN_HEIGHT / 2 + 30;
        r.w = 7;
        r.h = 10;
        SDL_RenderFillRect(renderer, &r);
    }
}

void Game::renderGameOver() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
    const char* text = "GAME OVER";

    for (const char* c = text; *c; c++) {
        SDL_Rect r;
        r.x = SCREEN_WIDTH / 2 - 80 + (c - text) * 16;
        r.y = SCREEN_HEIGHT / 2 - 80;
        r.w = 12;
        r.h = 18;
        SDL_RenderFillRect(renderer, &r);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    const char* restart = "Tekan SPACE untuk restart";
    for (const char* c = restart; *c; c++) {
        SDL_Rect r;
        r.x = SCREEN_WIDTH / 2 - 120 + (c - restart) * 8;
        r.y = SCREEN_HEIGHT / 2 - 40;
        r.w = 7;
        r.h = 10;
        SDL_RenderFillRect(renderer, &r);
    }
}

void Game::renderScore() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    std::string scoreStr = std::to_string(score);

    int startX = SCREEN_WIDTH / 2 - (scoreStr.length() * 12) / 2;
    for (size_t i = 0; i < scoreStr.length(); i++) {
        SDL_Rect r;
        r.x = startX + i * 16;
        r.y = 40;
        r.w = 10;
        r.h = 16;
        SDL_RenderFillRect(renderer, &r);
    }
}

void Game::renderGround() {
    SDL_SetRenderDrawColor(renderer, 139, 90, 43, 255);
    SDL_Rect ground = {0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT};
    SDL_RenderFillRect(renderer, &ground);

    SDL_SetRenderDrawColor(renderer, 100, 60, 20, 255);
    SDL_Rect line = {0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, 3};
    SDL_RenderFillRect(renderer, &line);
}
