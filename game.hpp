#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int GRID_SIZE = 8;
const int TILE_SIZE = SCREEN_WIDTH / GRID_SIZE;
const int COLOR_COUNT = 5;
const float ANIMATION_SPEED = 0.25f;
const int BONUS_RADIUS = 3;
const int BOMB_EXPLOSION_COUNT = 5;
const float BONUS_FLASH_DURATION = 0.5f;

enum BonusType {
    BONUS_NONE = 0,
    BONUS_COLOR_CHANGE,
    BONUS_BOMB
};

struct Tile {
    int color;
    bool toBeDestroyed = false;
    BonusType bonusType = BONUS_NONE;
    bool isFlashing = false;
    float flashTime = 0.0f;
};

struct VisualTile {
    Tile tile;
    float drawX, drawY;
    float targetX, targetY;
    bool animating = false;
};

extern SDL_Color colors[COLOR_COUNT];
extern std::vector<std::vector<VisualTile>> grid;
extern SDL_Point selected;
extern bool animationsRunning;

void initGrid();