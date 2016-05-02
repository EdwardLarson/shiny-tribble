#pragma once
#include <SDL.h>
#include <iostream>
#include "GameEnvironment.h"
#include "GameWorld.h"

namespace game{

class GameState{

public:
	GameState(SDL_Renderer* renderer);
	virtual ~GameState();

	virtual void update();

	virtual void render();

	virtual void processEvent(SDL_Event* event);

private:
	GameEnvironment* currentEnvironment;
	GameWorld* world;

	SDL_Renderer* mRenderer;
};

}