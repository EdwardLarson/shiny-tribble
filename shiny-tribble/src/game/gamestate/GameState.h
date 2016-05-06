#pragma once
#include <SDL.h>
#include <iostream>
#include "../GameEnvironment.h"
#include "../GameWorld.h"
#include "../../game/ui/UI.h"

namespace game{
namespace gamestate {

class GameState{

public:
	GameState();
	virtual ~GameState();

	virtual void loadGraphics() = 0;

	virtual void update() = 0;

	virtual void render() = 0;

	virtual void processEvent(SDL_Event* event) = 0;

protected:

	typedef game::ui::UI GameStateUI;

	GameStateUI mUI;
};

}
}