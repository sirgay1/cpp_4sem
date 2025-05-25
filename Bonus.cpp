#include "Bonus.h"
#include <SDL3/SDL.h>

void Bonus::update() {
    if (active) {
        rect.y += speed;
        if (rect.y > ArkanoidConstants::SCREEN_HEIGHT) {
            active = false;
        }
    }
}

void Bonus::render(SDL_Renderer* renderer) const {
    if (!active) return;
    
    switch (type) {
    case BonusType::PADDLE_SIZE_INC:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Желтый
        break;
    case BonusType::PADDLE_SIZE_DEC:
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Пурпурный
        break;
    case BonusType::BALL_SPEED_INC:
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Голубой
        break;
    case BonusType::BALL_SPEED_DEC:
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Оранжевый
        break;
    case BonusType::STICKY_PADDLE:
        SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255); // Розовый
        break;
    case BonusType::TEMPORARY_FLOOR:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Синий
        break;
    case BonusType::RANDOM_BOUNCE:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Красный
        break;
    }
    
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &rect);
}