#ifndef CONFIG_H
#define CONFIG_H

#include <string>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;
const int FPS = 60;
const std::string GAME_TITLE = "Flappy Bird C++";

// Bird
const int BIRD_X = 80;
const int BIRD_SIZE = 20;
const float GRAVITY = 0.5f;
const float FLAP_STRENGTH = -8.0f;
const float BIRD_MAX_VEL = 10.0f;

// Pipe
const int PIPE_WIDTH = 52;
const int PIPE_GAP = 150;
const int PIPE_SPEED = 3;
const int PIPE_SPAWN_INTERVAL = 120;

// Ground
const int GROUND_HEIGHT = 80;

// Colors
const SDL_Color COLOR_SKY = {135, 206, 235, 255};
const SDL_Color COLOR_BIRD = {255, 255, 0, 255};
const SDL_Color COLOR_PIPE = {0, 150, 0, 255};
const SDL_Color COLOR_PIPE_EDGE = {0, 180, 0, 255};
const SDL_Color COLOR_GROUND = {139, 90, 43, 255};
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};

#endif
