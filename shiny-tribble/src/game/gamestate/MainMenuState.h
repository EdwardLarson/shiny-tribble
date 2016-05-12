#pragma once

#include <iostream>
#include <SDL.h>
#include "GameState.h"
#include "../../ServiceProvider.h"
#include "../../graphics/Texture.h"

namespace game{
namespace gamestate{

class MainMenuState: public GameState{
public:
	MainMenuState();
	virtual ~MainMenuState();

	virtual void loadGraphics();

	virtual void update() override;

	virtual void render() override;

	virtual void processEvent(SDL_Event* event) override;

private:
	graphics::Texture buttonTex;
};

}
}