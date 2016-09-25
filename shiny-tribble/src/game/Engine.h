#pragma once

#include "../graphics/Texture.h"
#include <queue>

namespace game{

static class Engine
{
public:

	static void addToRender(graphics::Texture* texture);

	~Engine();

private:
	Engine();

	static std::queue<graphics::Texture*> textureQueue;
};

}
