#include "logic.hpp"
#include "bonuses.hpp"

bool isNeighbor(const SDL_Point& a, const SDL_Point& b) {
    return (abs(a.x - b.x) == 1 && a.y == b.y) || (abs(a.y - b.y) == 1 && a.x == b.x);
}

void swapTiles(SDL_Point a, SDL_Point b) {
    std::swap(grid[a.y][a.x], grid[b.y][b.x]);
    grid[a.y][a.x].targetX = static_cast<float>(a.x * TILE_SIZE);
    grid[a.y][a.x].targetY = static_cast<float>(a.y * TILE_SIZE);
    grid[b.y][b.x].targetX = static_cast<float>(b.x * TILE_SIZE);
    grid[b.y][b.x].targetY = static_cast<float>(b.y * TILE_SIZE);
    grid[a.y][a.x].animating = grid[b.y][b.x].animating = true;
}

bool checkMatchesAndMark() {
    bool found = false;
    std::vector<std::vector<bool>> visited(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (visited[y][x]) continue;

            int targetColor = grid[y][x].tile.color;
            std::vector<SDL_Point> stack = { {x, y} };
            std::vector<SDL_Point> cluster;

            while (!stack.empty()) {
                SDL_Point p = stack.back(); stack.pop_back();
                if (p.x < 0 || p.x >= GRID_SIZE || p.y < 0 || p.y >= GRID_SIZE) continue;
                if (visited[p.y][p.x]) continue;
                if (grid[p.y][p.x].tile.color != targetColor) continue;

                visited[p.y][p.x] = true;
                cluster.push_back(p);

                stack.push_back({ p.x + 1, p.y });
                stack.push_back({ p.x - 1, p.y });
                stack.push_back({ p.x, p.y + 1 });
                stack.push_back({ p.x, p.y - 1 });
            }

            if (cluster.size() >= 3) {
                found = true;
                for (auto& p : cluster) {
                    grid[p.y][p.x].tile.toBeDestroyed = true;
                    if (rand() % 100 < 15) {
                        grid[p.y][p.x].tile.bonusType = static_cast<BonusType>(rand() % 2 + 1);
                    }
                }
            }
        }
    }

    return found;
}

void dropTiles(bool animated) {
    for (int x = 0; x < GRID_SIZE; ++x) {
        int writeY = GRID_SIZE - 1;
        for (int y = GRID_SIZE - 1; y >= 0; --y) {
            if (!grid[y][x].tile.toBeDestroyed) {
                if (y != writeY) {
                    grid[writeY][x] = grid[y][x];
                    if (animated) {
                        grid[writeY][x].targetY = static_cast<float>(writeY * TILE_SIZE);
                        grid[writeY][x].animating = true;
                    }
                    else {
                        grid[writeY][x].drawY = static_cast<float>(writeY * TILE_SIZE);
                        grid[writeY][x].targetY = static_cast<float>(writeY * TILE_SIZE);
                    }
                }
                --writeY;
            }
        }
        for (int y = writeY; y >= 0; --y) {
            int color = rand() % COLOR_COUNT;
            float fx = static_cast<float>(x * TILE_SIZE);
            grid[y][x] = {
                {color, false},
                fx, 0.0f, fx, static_cast<float>(y * TILE_SIZE),
                animated
            };
        }
    }
}

void clearMatches() {
    for (auto& row : grid)
        for (auto& tile : row)
            if (tile.tile.toBeDestroyed) tile.tile.toBeDestroyed = false;
}

void handleMatchesAndBonuses() {
    if (checkMatchesAndMark()) {
        for (int y = 0; y < GRID_SIZE; ++y) {
            for (int x = 0; x < GRID_SIZE; ++x) {
                if (grid[y][x].tile.toBeDestroyed && grid[y][x].tile.bonusType != BONUS_NONE) {
                    int color = grid[y][x].tile.color;
                    if (grid[y][x].tile.bonusType == BONUS_COLOR_CHANGE) {
                        applyColorChangeBonus(x, y, color);
                    }
                    else if (grid[y][x].tile.bonusType == BONUS_BOMB) {
                        applyBombBonus(x, y);
                    }
                    grid[y][x].tile.bonusType = BONUS_NONE;
                }
            }
        }

        checkMatchesAndMark();
        dropTiles(true);
    }
}