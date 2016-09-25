#include "PhysicsLogic.h"

bool utility::isColliding(int x, int y, const SDL_Rect& rectangle) {
	return (
		(x >= rectangle.x) &&
		(x <= rectangle.x + rectangle.w) &&
		(y >= rectangle.y) &&
		(y <= rectangle.y + rectangle.h)
		);
}

bool utility::isWithin(float x, float y, float boxX, float boxY, float boxW, float boxH) {
	return (
		(x >= boxX) &&
		(x <= boxX + boxW) &&
		(y >= boxY) &&
		(y <= boxY + boxH)
		);
}

bool utility::contains(int x, int y, const SDL_Rect& rectangle) {
	return (x >= rectangle.x 
			&& x < rectangle.x + rectangle.w) 
		&& (y >= rectangle.y 
			&& y < rectangle.y + rectangle.h);
}

bool utility::contains(float x, float y, float boxX, float boxY, float boxW, float boxH) {
	return (x >= boxX
		&& x < boxX + boxW)
		&& (y >= boxY
			&& y < boxY + boxH);
}