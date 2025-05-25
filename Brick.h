#ifndef brick_h
#define brick_h

#include <SDL3/SDL.h>
#include "Constants.h"

enum class BrickType {
    REGULAR,
    UNBREAKABLE,
    BONUS,
    SPEED_CHANGE,
    HEALTHY
};

class Brick {
public:
    SDL_FRect rect;
    BrickType type;
    int health;
    bool alive;
    SDL_Color color;
    bool hasBonus;

    Brick(float x, float y, BrickType t);
    bool hit();
};
#endif 
