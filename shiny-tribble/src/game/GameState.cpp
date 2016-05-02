#include "GameState.h"

using namespace game;

GameState::GameState(SDL_Renderer* renderer): currentEnvironment(NULL), world(NULL), mRenderer(renderer){

}


GameState::~GameState(){

}

//Perform any actions that should be performed at every tick
void GameState::update() {
	currentEnvironment->update();
}

//Render 
void GameState::render() {
	currentEnvironment->render(mRenderer);

	//render ui
}

void GameState::processEvent(SDL_Event* event) {

}