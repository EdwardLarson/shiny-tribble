#include "MainMenuState.h"

using namespace game;
using namespace gamestate;


MainMenuState::MainMenuState(){
	mUI.buildFromFile("res/gamedata/ui/main_menu.ui");
}


MainMenuState::~MainMenuState(){

}

void MainMenuState::loadGraphics(){

}

//Perform any per-tick update to the main menu
void MainMenuState::update(double dt) {
	ServiceProvider::getLogging()->log("Updated the MainMenuState");
}

//Render to main menu to the screen
void MainMenuState::render() {
	mUI.render();
}

void MainMenuState::processEvent(SDL_Event* event) {
	
}