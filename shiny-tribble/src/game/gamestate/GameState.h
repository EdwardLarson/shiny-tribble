#pragma once
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "../GameEnvironment.h"
#include "../GameWorld.h"
#include "../../graphics/Texture.h"
#include "../../game/ui/UI.h"

namespace game{
namespace gamestate {

class GameState{

public:
	GameState(SDL_Renderer* renderer);
	virtual ~GameState();

	virtual void loadGraphics() = 0;

	virtual void update(double dt) = 0;

	virtual void render() = 0;

	virtual void processEvent(SDL_Event* event) = 0;

protected:

	typedef game::ui::UI GameStateUI;

	SDL_Renderer* mRenderer;
	std::unordered_map<int, graphics::Texture> textures;

	GameStateUI mUI;
};

}
}