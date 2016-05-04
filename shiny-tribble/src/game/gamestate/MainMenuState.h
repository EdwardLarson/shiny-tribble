#pragma once

#include <iostream>
#include <SDL.h>
#include "GameState.h"

namespace game{
namespace gamestate{

class MainMenuState: public GameState{
public:
	MainMenuState(SDL_Renderer* renderer);
	virtual ~MainMenuState();

	virtual void loadGraphics();

	virtual void update(double dt) override;

	virtual void render() override;

	virtual void processEvent(SDL_Event* event) override;
};

}
}