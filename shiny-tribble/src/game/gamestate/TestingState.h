#pragma once
#include "../../ServiceProvider.h"
#include "GameState.h"
#include "../../graphics/ParallaxTexture.h"


namespace game{
namespace gamestate{

class TestingState : public game::gamestate::GameState{
public:
	TestingState();
	virtual ~TestingState();

	virtual void loadGraphics();

	virtual void update() override;

	virtual void render() override;

	virtual void processEvent(SDL_Event* event) override;

private:
	graphics::ParallaxTexture parallaxTex;


};

}
}