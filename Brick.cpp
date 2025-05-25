#include "Brick.h"
#include <SDL3/SDL.h>
#include <random>

Brick::Brick(float x, float y, BrickType t) :
    rect{ x, y, ArkanoidConstants::BRICK_WIDTH, ArkanoidConstants::BRICK_HEIGHT },
    type(t),
    alive(true),
    hasBonus(false) {
    
    switch (type) {
    case BrickType::REGULAR: health = 1; break;
    case BrickType::UNBREAKABLE: health = -1; break;
    case BrickType::BONUS:
        health = 1;
        hasBonus = true;
        break;
    case BrickType::SPEED_CHANGE: health = 1; break;
    case BrickType::HEALTHY: health = 3; break;
    }
    
    switch (type) {
    case BrickType::REGULAR:
        color = { 50, 200, 50, 255 };
        break;
    case BrickType::UNBREAKABLE:
        color = { 20, 100, 20, 255 };
        break;
    case BrickType::BONUS:
        color = { 100, 255, 100, 255 };
        break;
    case BrickType::SPEED_CHANGE:
        color = { 50, 150, 50, 255 };
        break;
    case BrickType::HEALTHY:
        color = { 0, 255, 0, 255 };
        break;
    }
}

bool Brick::hit() {
    if (type == BrickType::UNBREAKABLE) return false;

    health--;
    if (health <= 0) {
        alive = false;
        return true;
    }
    return false;
}