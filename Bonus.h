#ifndef bonus_h
#define bonus_h

#include <SDL3/SDL.h>
#include "Constants.h"

enum class BonusType {
    PADDLE_SIZE_INC,
    PADDLE_SIZE_DEC,
    BALL_SPEED_INC,
    BALL_SPEED_DEC,
    STICKY_PADDLE,
    TEMPORARY_FLOOR,
    RANDOM_BOUNCE
};

struct Bonus {
    SDL_FRect rect;
    BonusType type;
    bool active;
    float speed;

    void update();
    void render(SDL_Renderer* renderer) const;
};
#endif