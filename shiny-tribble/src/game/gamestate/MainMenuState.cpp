#include "MainMenuState.h"

using namespace game;
using namespace gamestate;


MainMenuState::MainMenuState(): buttonTex(NULL, 0, 0, 0, 0){
	mUI.buildFromFile("res/gamedata/ui/main_menu.ui");
	loadGraphics();
}


MainMenuState::~MainMenuState(){

}

void MainMenuState::loadGraphics(){
	std::cout << "loadGraphics was called" << std::endl;
	buttonTex = ServiceProvider::getVideo().loadTexture("res/graphics/center.png");
}

//Perform any per-tick update to the main menu
void MainMenuState::update() {

}

//Render to main menu to the screen
void MainMenuState::render() {
	//ServiceProvider::getVideo().render(buttonTex, 10, 10, 500, 200);

	ServiceProvider::getVideo().renderAtlas();

	//render UI over everything
	//mUI.render();
}

void MainMenuState::processEvent(SDL_Event* event) {
	
}