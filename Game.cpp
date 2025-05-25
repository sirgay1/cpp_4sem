#include "Game.h"
#include <random>
#include <algorithm>

Game::Game() : score(0), lives(3), running(true), gameOver(false),
stickyPaddle(false), floorActive(false), ballBaseSpeed(5.0f) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Arkanoid",
        ArkanoidConstants::SCREEN_WIDTH,
        ArkanoidConstants::SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderVSync(renderer, 1);

    resetGame();
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::resetGame() {
    paddle = {
        (ArkanoidConstants::SCREEN_WIDTH - ArkanoidConstants::PADDLE_WIDTH) / 2.0f,
        ArkanoidConstants::SCREEN_HEIGHT - ArkanoidConstants::PADDLE_HEIGHT - 10,
        ArkanoidConstants::PADDLE_WIDTH,
        ArkanoidConstants::PADDLE_HEIGHT
    };

    ball = {
        ArkanoidConstants::SCREEN_WIDTH / 2.0f,
        ArkanoidConstants::SCREEN_HEIGHT / 2.0f,
        ArkanoidConstants::BALL_SIZE,
        ArkanoidConstants::BALL_SIZE
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    ballVelocity = { dist(gen) > 0 ? 0.5f : -0.5f, -0.5f };
    ballBaseSpeed = 5.0f;

    bricks.clear();
    bonuses.clear();

    for (int row = 0; row < ArkanoidConstants::BRICK_ROWS; ++row) {
        for (int col = 0; col < ArkanoidConstants::BRICK_COLS; ++col) {
            BrickType type;
            int r = rand() % 100;

            if (r < 10) type = BrickType::UNBREAKABLE;
            else if (r < 25) type = BrickType::BONUS;
            else if (r < 40) type = BrickType::SPEED_CHANGE;
            else if (r < 55) type = BrickType::HEALTHY;
            else type = BrickType::REGULAR;

            bricks.emplace_back(
                col * (ArkanoidConstants::BRICK_WIDTH + 5) + 30,
                row * (ArkanoidConstants::BRICK_HEIGHT + 5) + 50,
                type
            );
        }
    }

    score = 0;
    lives = 3;
    running = true;
    gameOver = false;
    stickyPaddle = false;
    floorActive = false;
}

void Game::spawnBonus(float x, float y, BonusType type) {
    bonuses.push_back({
        {x + (ArkanoidConstants::BRICK_WIDTH - ArkanoidConstants::BONUS_WIDTH) / 2,
         y + ArkanoidConstants::BRICK_HEIGHT,
         ArkanoidConstants::BONUS_WIDTH,
         ArkanoidConstants::BONUS_HEIGHT},
        type,
        true,
        2.0f
        });
}

void Game::activateBonus(BonusType type) {
    switch (type) {
    case BonusType::PADDLE_SIZE_INC:
        paddle.w += 30;
        break;
    case BonusType::PADDLE_SIZE_DEC:
        paddle.w = std::max(50.0f, paddle.w - 30);
        break;
    case BonusType::BALL_SPEED_INC:
        ballBaseSpeed += 1.0f;
        break;
    case BonusType::BALL_SPEED_DEC:
        ballBaseSpeed = std::max(3.0f, ballBaseSpeed - 1.0f);
        break;
    case BonusType::STICKY_PADDLE:
        stickyPaddle = true;
        break;
    case BonusType::TEMPORARY_FLOOR:
        floorActive = true;
        break;
    case BonusType::RANDOM_BOUNCE: {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
        ballVelocity.x += dist(gen);
        ballVelocity.y += dist(gen);
        break;
    }
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_R && !running) {
                resetGame();
            }
            if (event.key.key == SDLK_SPACE && stickyPaddle) {
                ballVelocity.y = -fabs(ballVelocity.y);
                stickyPaddle = false;
            }
        }
    }

    const bool* keyboard = SDL_GetKeyboardState(NULL);
    if (keyboard[SDL_SCANCODE_LEFT] && paddle.x > 0) {
        paddle.x -= 5;
        if (stickyPaddle) {
            ball.x -= 5;
            paddleStickPos = (ball.x + ball.w / 2) - (paddle.x + paddle.w / 2);
        }
    }
    if (keyboard[SDL_SCANCODE_RIGHT] && paddle.x < ArkanoidConstants::SCREEN_WIDTH - paddle.w) {
        paddle.x += 5;
        if (stickyPaddle) {
            ball.x += 5;
            paddleStickPos = (ball.x + ball.w / 2) - (paddle.x + paddle.w / 2);
        }
    }
}

void Game::update() {
    if (!running) return;

    SDL_FRect prevBall = ball;

    ball.x += ballVelocity.x * ballBaseSpeed;
    ball.y += ballVelocity.y * ballBaseSpeed;

    for (auto& bonus : bonuses) {
        if (bonus.active) {
            bonus.rect.y += bonus.speed;
            if (bonus.rect.y > ArkanoidConstants::SCREEN_HEIGHT) {
                bonus.active = false;
            }
        }
    }

    for (auto& bonus : bonuses) {
        if (bonus.active && SDL_HasRectIntersectionFloat(&bonus.rect, &paddle)) {
            activateBonus(bonus.type);
            bonus.active = false;
        }
    }

    if (ball.x <= 0 || ball.x >= ArkanoidConstants::SCREEN_WIDTH - ball.w) {
        ballVelocity.x *= -1;
    }
    if (ball.y <= 0) {
        ballVelocity.y *= -1;
    }

    if (floorActive && ball.y >= ArkanoidConstants::SCREEN_HEIGHT - 10) {
        ballVelocity.y *= -1;
        floorActive = false;
    }

    if (SDL_HasRectIntersectionFloat(&ball, &paddle)) {
        if (stickyPaddle) {
            paddleStickPos = (ball.x + ball.w / 2) - (paddle.x + paddle.w / 2);
        }
        else {
            ballVelocity.y = -fabs(ballVelocity.y);
            float hitPos = (ball.x + ball.w / 2) - (paddle.x + paddle.w / 2);
            ballVelocity.x = hitPos * 0.02f;
        }
    }

    bool collisionX = false;
    bool collisionY = false;

    for (auto& brick : bricks) {
        if (brick.alive && SDL_HasRectIntersectionFloat(&ball, &brick.rect)) {
            float overlapLeft = ball.x + ball.w - brick.rect.x;
            float overlapRight = brick.rect.x + brick.rect.w - ball.x;
            float overlapTop = ball.y + ball.h - brick.rect.y;
            float overlapBottom = brick.rect.y + brick.rect.h - ball.y;

            float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

            if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                collisionX = true;
            }
            else {
                collisionY = true;
            }

            if (brick.type == BrickType::UNBREAKABLE) {
                if (collisionX) {
                    ball.x = prevBall.x;
                    ballVelocity.x *= -1;
                }
                if (collisionY) {
                    ball.y = prevBall.y;
                    ballVelocity.y *= -1;
                }
                continue;
            }

            bool destroyed = brick.hit();
            score += 1;

            if (brick.type == BrickType::BONUS && destroyed && brick.hasBonus) {
                BonusType bonusType = static_cast<BonusType>(rand() % 7);
                spawnBonus(brick.rect.x, brick.rect.y, bonusType);
            }
            else if (brick.type == BrickType::SPEED_CHANGE) {
                ballBaseSpeed += (rand() % 2 == 0) ? 0.5f : -0.5f;
                ballBaseSpeed = std::max(3.0f, std::min(10.0f, ballBaseSpeed));
            }

            if (collisionX) {
                ball.x = prevBall.x;
                ballVelocity.x *= -1;
            }
            if (collisionY) {
                ball.y = prevBall.y;
                ballVelocity.y *= -1;
            }
            break;
        }
    }

    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
        [](const Brick& b) { return !b.alive; }), bricks.end());

    bonuses.erase(std::remove_if(bonuses.begin(), bonuses.end(),
        [](const Bonus& b) { return !b.active; }), bonuses.end());

    if (ball.y >= ArkanoidConstants::SCREEN_HEIGHT) {
        if (--lives <= 0) {
            running = false;
            gameOver = true;
        }
        else {
            ball = {
                ArkanoidConstants::SCREEN_WIDTH / 2.0f,
                ArkanoidConstants::SCREEN_HEIGHT / 2.0f,
                ArkanoidConstants::BALL_SIZE,
                ArkanoidConstants::BALL_SIZE
            };
            ballVelocity.y = -0.5f;
            stickyPaddle = false;
        }
    }

    if (bricks.empty()) {
        running = false;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball);

    for (const auto& brick : bricks) {
        if (brick.alive) {
            SDL_SetRenderDrawColor(renderer, brick.color.r, brick.color.g, brick.color.b, 255);
            SDL_RenderFillRect(renderer, &brick.rect);

            if (brick.type == BrickType::HEALTHY) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_FRect healthBar = {
                    brick.rect.x,
                    brick.rect.y + brick.rect.h - 5,
                    brick.rect.w * (brick.health / 3.0f),
                    3
                };
                SDL_RenderFillRect(renderer, &healthBar);
            }
        }
    }

    for (const auto& bonus : bonuses) {
        if (bonus.active) {
            switch (bonus.type) {
            case BonusType::PADDLE_SIZE_INC: SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break;
            case BonusType::PADDLE_SIZE_DEC: SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); break;
            case BonusType::BALL_SPEED_INC: SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); break;
            case BonusType::BALL_SPEED_DEC: SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break;
            case BonusType::STICKY_PADDLE: SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255); break;
            case BonusType::TEMPORARY_FLOOR: SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
            case BonusType::RANDOM_BOUNCE: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
            }
            SDL_RenderFillRect(renderer, &bonus.rect);
        }
    }

    if (floorActive) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, 100);
        SDL_FRect floor = { 0, ArkanoidConstants::SCREEN_HEIGHT - 5, ArkanoidConstants::SCREEN_WIDTH, 5 };
        SDL_RenderFillRect(renderer, &floor);
    }

    SDL_RenderPresent(renderer);
}

bool Game::isRunning() const {
    return running || !gameOver;
}