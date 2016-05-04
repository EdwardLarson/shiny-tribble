#pragma once

#include <SDL.h>
#include "../../graphics/Texture.h"

namespace game {
namespace entity {

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update();

	virtual void render(SDL_Renderer* renderer);

private:
	graphics::Texture* mTexture;

	int x, y;
};

}
}

