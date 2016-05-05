#pragma once

#include <iostream>
#include <SDL.h>
#include "GameState.h"
#include "../../ServiceProvider.h"

namespace game{
namespace gamestate{

class MainMenuState: public GameState{
public:
	MainMenuState();
	virtual ~MainMenuState();

	virtual void loadGraphics();

	virtual void update(double dt) override;

	virtual void render() override;

	virtual void processEvent(SDL_Event* event) override;
};

}
}