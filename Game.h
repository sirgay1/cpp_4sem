#ifndef game_h
#define game_h

#include <SDL3/SDL.h>
#include <vector>
#include "Brick.h"
#include "Bonus.h"
#include "Constants.h"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_FRect paddle;
    SDL_FRect ball;
    SDL_FPoint ballVelocity;
    float ballBaseSpeed;

    std::vector<Brick> bricks;
    std::vector<Bonus> bonuses;
    int score;
    int lives;
    bool running;
    bool gameOver;
    bool stickyPaddle;
    bool floorActive;
    float paddleStickPos;

public:
    Game();
    ~Game();

    void resetGame();
    void handleEvents();
    void update();
    void render();
    bool isRunning() const;

private:
    void spawnBonus(float x, float y, BonusType type);
    void activateBonus(BonusType type);
};
#endif