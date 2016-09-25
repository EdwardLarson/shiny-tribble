#include "TestingState.h"

using namespace game;
using namespace gamestate;

TestingState::TestingState() : parallaxTex(true, 10)
{
	tex_a = ServiceProvider::getVideo().loadTexture("res/graphics/parallax1.png");
	tex_b = ServiceProvider::getVideo().loadTexture("res/graphics/parallax2.png");
	tex_c = ServiceProvider::getVideo().loadTexture("res/graphics/parallax3.png");

	parallaxTex.addTexture(&tex_a, 0);
	parallaxTex.addTexture(&tex_b, 3);
	parallaxTex.addTexture(&tex_c, 4);


}


TestingState::~TestingState()
{
}

void game::gamestate::TestingState::loadGraphics()
{
}

void game::gamestate::TestingState::update()
{
	
}

void game::gamestate::TestingState::render()
{
	parallaxTex.render(0.5f, 0.5f, 0.1f, 0.1f);
}

void game::gamestate::TestingState::processEvent(SDL_Event * event)
{
	if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_d) {
			parallaxTex.moveRect(0.001f, 0.0f);
			ServiceProvider::getLogging() << "moveRight\n";
		}else if (event->key.keysym.sym == SDLK_a) {
			parallaxTex.moveRect(-0.001f, 0.0f);
			ServiceProvider::getLogging() << "moveLeft\n";
		}
		else if (event->key.keysym.sym == SDLK_w) {
			parallaxTex.moveRect(0.0f, -0.001f);
			ServiceProvider::getLogging() << "moveUp\n";
		}
		else if (event->key.keysym.sym == SDLK_s) {
			parallaxTex.moveRect(0.0f, 0.001f);
			ServiceProvider::getLogging() << "moveDown\n";
		}
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN) {
		event->motion;
	}
	else if (event->type == SDL_MOUSEBUTTONUP) {

	}
}
