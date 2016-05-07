#include "MainMenuState.h"

using namespace game;
using namespace gamestate;


MainMenuState::MainMenuState(){
	mUI.buildFromFile("res/gamedata/ui/main_menu.ui");
	loadGraphics();
}


MainMenuState::~MainMenuState(){

}

void MainMenuState::loadGraphics(){
	std::cout << "loadGraphics was called" << std::endl;
	ServiceProvider::getVideo().loadTexture("res/graphics/center.png");
}

//Perform any per-tick update to the main menu
void MainMenuState::update() {

}

//Render to main menu to the screen
void MainMenuState::render() {
	ServiceProvider::getVideo().render("res/graphics/center.png", 0, 0);

	//render UI over everything
	mUI.render();
}

void MainMenuState::processEvent(SDL_Event* event) {
	
}