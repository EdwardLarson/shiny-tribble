#include "MainMenuState.h"

using namespace game;
using namespace gamestate;


MainMenuState::MainMenuState(SDL_Renderer* renderer): GameState(renderer){
	mUI.buildFromFile("res/gamedata/ui/main_menu.ui");
}


MainMenuState::~MainMenuState(){

}

void MainMenuState::loadGraphics(){

}

//Perform any per-tick update to the main menu
void MainMenuState::update(double dt) {
	
}

//Render to main menu to the screen
void MainMenuState::render() {
	mUI.render(mRenderer);
}

void MainMenuState::processEvent(SDL_Event* event) {
	
}