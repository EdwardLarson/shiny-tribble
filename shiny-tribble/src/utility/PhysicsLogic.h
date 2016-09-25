#pragma once
#include <SDL.h>

namespace utility{

bool contains(int x, int y, const SDL_Rect& rectangle);

bool contains(float x, float y, float boxX, float boxY, float boxW, float boxH);

bool isColliding(int x, int y, const SDL_Rect& rectangle);

bool isWithin(float x, float y, float boxX, float boxY, float boxW, float boxH);

}