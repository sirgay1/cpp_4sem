#pragma once
#include "game.hpp"

bool isNeighbor(const SDL_Point& a, const SDL_Point& b);
void swapTiles(SDL_Point a, SDL_Point b);
bool checkMatchesAndMark();
void dropTiles(bool animated = true);
void clearMatches();
void handleMatchesAndBonuses();