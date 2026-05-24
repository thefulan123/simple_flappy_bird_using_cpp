#include "game.h"
#include "config.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>

Game::Game() : window(nullptr), renderer(nullptr), running(false),
               state(GameState::MENU), score(0), highScore(0),
               blinkCounter(0), lastFrameTime(0) {}

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

    std::ifstream file("highscore.dat");
    if (file.is_open()) {
        file >> highScore;
        file.close();
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
                    if (state == GameState::MENU) {
                        running = false;
                    } else {
                        state = GameState::MENU;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update() {
    blinkCounter++;

    if (state == GameState::MENU) {
        bird.update();
        if (bird.getY() > SCREEN_HEIGHT / 2 + 20) {
            bird.flap();
        }
        return;
    }

    if (state != GameState::PLAYING) return;

    bird.update();
    pipeManager.update();

    if (bird.getY() + BIRD_SIZE >= SCREEN_HEIGHT - GROUND_HEIGHT ||
        bird.getY() <= 0 ||
        pipeManager.checkCollision(bird.getRect())) {
        state = GameState::GAME_OVER;

        if (score > highScore) {
            highScore = score;
            std::ofstream file("highscore.dat");
            if (file.is_open()) {
                file << highScore;
                file.close();
            }
        }
    }

    for (auto& pipe : pipeManager.getPipes()) {
        if (!pipe.scored && pipe.x + PIPE_WIDTH < BIRD_X) {
            pipe.scored = true;
            score++;
        }
    }
}

void Game::render() {
    renderBackground();

    if (state == GameState::MENU) {
        pipeManager.render(renderer);
        renderGround();
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

void Game::renderBackground() {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 6; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 30 + i * 10);
        SDL_Rect cloud = {50 + i * 70, 40 + (i % 3) * 30, 60, 25};
        SDL_RenderFillRect(renderer, &cloud);
    }
}

void Game::renderMenu() {
    int cx = SCREEN_WIDTH / 2;

    renderPanel(cx - 150, 50, 300, 320, COLOR_DARK_BG);

    drawText(cx - 80, 70, "FLAPPY BIRD", 3, COLOR_GOLD);

    drawText(cx - 48, 120, "-= GAME =-", 2, COLOR_WHITE);

    bird.render(renderer);

    if (highScore > 0) {
        std::string hs = "HI: " + std::to_string(highScore);
        drawText(cx - 55, 240, hs.c_str(), 1, COLOR_GOLD);
    }

    if ((blinkCounter / BLINK_INTERVAL) % 2 == 0) {
        drawText(cx - 105, 280, "TEKAN SPACE UNTUK MAIN", 1, COLOR_WHITE);
    }

    drawText(cx - 60, 320, "ESC UNTUK KELUAR", 1, COLOR_WHITE);

    drawText(cx - 70, 350, "thefulan123", 1, COLOR_WHITE);
}

void Game::renderGameOver() {
    int cx = SCREEN_WIDTH / 2;
    int cy = SCREEN_HEIGHT / 2;

    renderPanel(cx - 140, cy - 120, 280, 240, COLOR_DARK_BG);

    drawText(cx - 72, cy - 100, "GAME OVER", 2, COLOR_RED);

    drawLine(cx - 120, cy - 65, cx + 120, cy - 65, COLOR_WHITE);

    std::string scoreStr = "SKOR: " + std::to_string(score);
    drawText(cx - 60, cy - 45, scoreStr.c_str(), 1, COLOR_WHITE);

    std::string hsStr = "TERBAIK: " + std::to_string(highScore);
    drawText(cx - 60, cy - 20, hsStr.c_str(), 1, COLOR_GOLD);

    if (score > 0 && score >= highScore) {
        drawText(cx - 85, cy + 5, "SKOR TERTINGGI!", 1, COLOR_GOLD);
    }

    drawLine(cx - 120, cy + 35, cx + 120, cy + 35, COLOR_WHITE);

    if ((blinkCounter / BLINK_INTERVAL) % 2 == 0) {
        drawText(cx - 110, cy + 50, "TEKAN SPACE LAGI", 1, COLOR_WHITE);
    }

    drawText(cx - 85, cy + 75, "ESC = MENU UTAMA", 1, COLOR_WHITE);
}

void Game::renderScore() {
    int cx = SCREEN_WIDTH / 2;

    renderPanel(cx - 50, 15, 100, 40, COLOR_DARK_BG);

    std::string scoreStr = std::to_string(score);
    int totalW = scoreStr.length() * 4 * 4;
    drawText(cx - totalW / 2, 22, scoreStr.c_str(), 3, COLOR_WHITE);
}

void Game::renderGround() {
    SDL_SetRenderDrawColor(renderer, 139, 90, 43, 255);
    SDL_Rect ground = {0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT};
    SDL_RenderFillRect(renderer, &ground);

    SDL_SetRenderDrawColor(renderer, 60, 40, 20, 255);
    SDL_Rect topBorder = {0, SCREEN_HEIGHT - GROUND_HEIGHT - 3, SCREEN_WIDTH, 3};
    SDL_RenderFillRect(renderer, &topBorder);

    for (int i = 0; i < 12; i++) {
        SDL_SetRenderDrawColor(renderer, 120, 80, 30, 255);
        SDL_Rect dash = {i * 35, SCREEN_HEIGHT - GROUND_HEIGHT / 2, 15, 4};
        SDL_RenderFillRect(renderer, &dash);
    }
}

void Game::renderPanel(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 60);
    for (int i = 0; i < 2; i++) {
        SDL_Rect border = {x - i, y - i, w + i * 2, h + i * 2};
        SDL_RenderDrawRect(renderer, &border);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void Game::drawChar(int x, int y, char c, int size, SDL_Color color) {
    c = std::toupper(static_cast<unsigned char>(c));
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int map[5][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    switch (c) {
        case 'A': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][2]=1; break;
        case 'B': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case 'C': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][0]=1;map[3][0]=1;map[4][1]=1;map[4][2]=1; break;
        case 'D': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case 'E': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][0]=1;map[2][1]=1;map[3][0]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case 'F': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][0]=1;map[2][1]=1;map[3][0]=1;map[4][0]=1; break;
        case 'G': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case 'H': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][2]=1; break;
        case 'I': map[0][1]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][1]=1; break;
        case 'J': map[0][1]=1;map[0][2]=1;map[1][1]=1;map[2][1]=1;map[3][0]=1;map[3][1]=1;map[4][0]=1;map[4][1]=1; break;
        case 'K': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][1]=1;map[2][0]=1;map[2][1]=1;map[3][0]=1;map[3][1]=1;map[4][0]=1;map[4][2]=1; break;
        case 'L': map[0][0]=1;map[1][0]=1;map[2][0]=1;map[3][0]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case 'M': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][1]=1;map[1][2]=1;map[2][0]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][2]=1; break;
        case 'N': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][1]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][2]=1; break;
        case 'O': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case 'P': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[4][0]=1; break;
        case 'Q': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][2]=1;map[3][0]=1;map[3][1]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case 'R': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][1]=1;map[4][0]=1;map[4][2]=1; break;
        case 'S': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][1]=1;map[3][2]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case 'T': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][1]=1; break;
        case 'U': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case 'V': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][2]=1;map[3][1]=1;map[3][2]=1;map[4][2]=1; break;
        case 'W': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][0]=1;map[4][2]=1; break;
        case 'X': map[0][0]=1;map[0][2]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][0]=1;map[4][2]=1; break;
        case 'Y': map[0][0]=1;map[0][2]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][1]=1; break;
        case 'Z': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case '0': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case '1': map[0][1]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][1]=1; break;
        case '2': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][2]=1;map[2][1]=1;map[3][0]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case '3': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][2]=1;map[2][1]=1;map[3][2]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case '4': map[0][0]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][2]=1;map[4][2]=1; break;
        case '5': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][2]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case '6': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[2][0]=1;map[2][1]=1;map[2][2]=1;map[3][0]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case '7': map[0][0]=1;map[0][1]=1;map[0][2]=1;map[1][2]=1;map[2][1]=1;map[3][1]=1;map[4][1]=1; break;
        case '8': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][1]=1;map[3][0]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case '9': map[0][1]=1;map[0][2]=1;map[1][0]=1;map[1][2]=1;map[2][1]=1;map[2][2]=1;map[3][2]=1;map[4][1]=1;map[4][2]=1; break;
        case '-': map[2][0]=1;map[2][1]=1;map[2][2]=1; break;
        case '=': map[2][0]=1;map[2][1]=1;map[2][2]=1;map[4][0]=1;map[4][1]=1;map[4][2]=1; break;
        case '!': map[0][1]=1;map[1][1]=1;map[2][1]=1;map[3][1]=1;map[4][1]=1; break;
        case ':': map[1][1]=1;map[3][1]=1; break;
        case '.': map[4][1]=1; break;
        case '\'': map[0][1]=1; break;
        default: break;
    }

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            if (map[row][col]) {
                SDL_Rect p = {x + col * size * 2, y + row * size * 2, size * 2, size * 2};
                SDL_RenderFillRect(renderer, &p);
            }
        }
    }
}

void Game::drawText(int x, int y, const char* text, int size, SDL_Color color) {
    int spacing = size * 4;
    int currX = x;
    for (const char* c = text; *c; c++) {
        if (*c == ' ') {
            currX += size * 3;
            continue;
        }
        drawChar(currX, y, *c, size, color);
        currX += spacing;
    }
}

void Game::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
