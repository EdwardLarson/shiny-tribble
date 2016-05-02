#pragma once

#include <set>
#include <SDL.h>
#include "entity\Entity.h"

namespace game{

class GameEnvironment
{
public:
	GameEnvironment();
	~GameEnvironment();

	void render(SDL_Renderer* renderer);

	virtual void update();

private:
	std::set<entity::Entity*> entities;
};

}

