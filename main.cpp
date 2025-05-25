#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(16);
    }

    return 0;
}