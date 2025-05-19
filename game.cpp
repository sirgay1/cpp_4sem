#include "game.hpp"

SDL_Color colors[COLOR_COUNT] = {
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {0, 0, 255, 255},
    {255, 255, 0, 255},
    {255, 0, 255, 255}
};

std::vector<std::vector<VisualTile>> grid(GRID_SIZE, std::vector<VisualTile>(GRID_SIZE));
SDL_Point selected{ -1, -1 };
bool animationsRunning = false;

void initGrid() {
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            int color = rand() % COLOR_COUNT;
            float fx = static_cast<float>(x * TILE_SIZE);
            float fy = static_cast<float>(y * TILE_SIZE);
            grid[y][x] = { {color, false}, fx, fy, fx, fy, false };
        }
    }
}