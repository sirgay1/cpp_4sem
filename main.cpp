#include "bonuses.hpp"
#include "draw.hpp"
#include "logic.hpp"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Gems", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    srand((unsigned)time(nullptr));
    initGrid();

    bool running = true;
    SDL_Event e;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    float deltaTime = 0;

    while (running) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (float)((NOW - LAST) * 1000 / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && !animationsRunning) {
                int x = e.button.x / TILE_SIZE;
                int y = e.button.y / TILE_SIZE;
                if (selected.x == -1) {
                    selected = { x, y };
                }
                else {
                    SDL_Point second = { x, y };
                    if (isNeighbor(selected, second)) {
                        swapTiles(selected, second);
                    }
                    selected = { -1, -1 };
                }
            }
        }

        if (!animationsRunning) {
            clearMatches();
            handleMatchesAndBonuses();
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        drawGrid(renderer, deltaTime);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}