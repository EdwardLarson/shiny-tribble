#include "GameEnvironment.h"

using namespace game;

GameEnvironment::GameEnvironment(){

}


GameEnvironment::~GameEnvironment(){

}

void GameEnvironment::render(SDL_Renderer* renderer) {

}

void GameEnvironment::update() {
	for (std::set<entity::Entity*>::iterator iter = entities.begin();
		iter != entities.end();
		++iter) {

		(*iter)->update();
	}
}