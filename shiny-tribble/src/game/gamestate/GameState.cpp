#include "GameState.h"

using namespace game;
using namespace gamestate;

GameState::GameState(SDL_Renderer* renderer): mRenderer(renderer){
	//also need to load all of the textures for this gamestate
}


GameState::~GameState(){

}

/*
//Perform any actions that should be performed at every tick
void GameState::update() {
	
}

//Render to screen whatever this GameState requires
void GameState::render() {

}

void GameState::processEvent(SDL_Event* event) {

}
*/