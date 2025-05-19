#include "bonuses.hpp"

void applyColorChangeBonus(int x, int y, int color) {
    grid[y][x].tile.isFlashing = true;
    grid[y][x].tile.flashTime = 0.0f;
    grid[y][x].tile.color = color;

    std::vector<SDL_Point> nonNeighbors;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < GRID_SIZE && ny < GRID_SIZE) {
                if (!(abs(dx) == 1 && dy == 0) && !(abs(dy) == 1 && dx == 0) && !(dx == 0 && dy == 0)) {
                    nonNeighbors.push_back({ nx, ny });
                }
            }
        }
    }

    std::random_shuffle(nonNeighbors.begin(), nonNeighbors.end());
    int changed = 0;
    for (auto& p : nonNeighbors) {
        if (changed >= 2) break;
        grid[p.y][p.x].tile.color = color;
        grid[p.y][p.x].tile.isFlashing = true;
        grid[p.y][p.x].tile.flashTime = 0.0f;
        changed++;
    }
}

void applyBombBonus(int x, int y) {
    grid[y][x].tile.toBeDestroyed = true;
    grid[y][x].tile.isFlashing = true;
    grid[y][x].tile.flashTime = 0.0f;

    std::vector<SDL_Point> allTiles;
    for (int ty = 0; ty < GRID_SIZE; ++ty) {
        for (int tx = 0; tx < GRID_SIZE; ++tx) {
            allTiles.push_back({ tx, ty });
        }
    }

    allTiles.erase(std::remove_if(allTiles.begin(), allTiles.end(),
        [x, y](const SDL_Point& p) { return p.x == x && p.y == y; }),
        allTiles.end());

    std::random_shuffle(allTiles.begin(), allTiles.end());
    for (int i = 0; i < 4 && i < allTiles.size(); ++i) {
        SDL_Point p = allTiles[i];
        grid[p.y][p.x].tile.toBeDestroyed = true;
        grid[p.y][p.x].tile.isFlashing = true;
        grid[p.y][p.x].tile.flashTime = 0.0f;
    }
}