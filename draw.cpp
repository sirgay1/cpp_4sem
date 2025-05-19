#include "draw.hpp"

void drawGrid(SDL_Renderer* renderer, float deltaTime) {
    animationsRunning = false;
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            VisualTile& vt = grid[y][x];

            if (vt.animating) {
                animationsRunning = true;
                float dx = vt.targetX - vt.drawX;
                float dy = vt.targetY - vt.drawY;
                if (std::abs(dx) < 1 && std::abs(dy) < 1) {
                    vt.drawX = vt.targetX;
                    vt.drawY = vt.targetY;
                    vt.animating = false;
                }
                else {
                    vt.drawX += dx * ANIMATION_SPEED;
                    vt.drawY += dy * ANIMATION_SPEED;
                }
            }

            if (!vt.tile.toBeDestroyed) {
                SDL_Color c = colors[vt.tile.color];
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_FRect rect = {
                    vt.drawX,
                    vt.drawY,
                    TILE_SIZE - 2,
                    TILE_SIZE - 2
                };
                SDL_RenderFillRect(renderer, &rect);

                if (vt.tile.isFlashing) {
                    vt.tile.flashTime += deltaTime;
                    if (vt.tile.flashTime <= BONUS_FLASH_DURATION) {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        float centerX = vt.drawX + (TILE_SIZE - 2) / 2.0f;
                        float centerY = vt.drawY + (TILE_SIZE - 2) / 2.0f;
                        float radius = (TILE_SIZE - 2) / 3.0f;
                        for (int i = 0; i < 360; i += 10) {
                            float angle = i * 3.14159f / 180.0f;
                            float x1 = centerX + radius * cos(angle);
                            float y1 = centerY + radius * sin(angle);
                            float x2 = centerX + radius * cos(angle + 0.17f);
                            float y2 = centerY + radius * sin(angle + 0.17f);
                            SDL_RenderLine(renderer, x1, y1, x2, y2);
                        }
                    }
                    else {
                        vt.tile.isFlashing = false;
                        vt.tile.flashTime = 0.0f;
                    }
                }
            }
        }
    }
}