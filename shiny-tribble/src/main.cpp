/*
Created by Ed Larson 5/1/2016

LAST UPDATED: 5/3/2016
*/

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define MS_PER_TICK 10

#include <iostream>
#include <chrono>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include "ServiceProvider.h"
#include "utility\Timer.h"
#include "game\gamestate\GameState.h"
#include "game\gamestate\MainMenuState.h"
#include "game\gamestate\TestingState.h"

bool init();
void close();

SDL_Window* buildWindow(const std::string& title, int width, int height);
SDL_Renderer* buildRenderer(SDL_Window* window);

int main(int argc, char* argv[]) {

	//Initialize SDL and its various libraries

	//Create all necessary variables

	// ---SDL---
	init();

	SDL_DisplayMode displayMode;
	int windowW, windowH;

	if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
		printf("Unable to get display mode for display %i! SDL Error: %s\n", 0, SDL_GetError());
		windowW = WINDOW_WIDTH;
		windowH = WINDOW_HEIGHT;
	}else {
		printf("Got the current display mode: %i x %i\n", displayMode.w, displayMode.h);
		windowW = displayMode.w;
		windowH = displayMode.h;
	}

	SDL_Window* mainWindow = buildWindow("Platformer Game", windowW, windowH);
	SDL_Renderer* mainRenderer = buildRenderer(mainWindow);

	// ---TIME---
	utility::time::Timer runningTime;
	utility::time::Timer timeSinceLastUpdate;

	// ---GAME---
	audio::NullAudioService audioService;
	graphics::DefaultVideoService videoService(mainRenderer);
	utility::ConsoleLoggingService loggingService;

	//initialize service
	ServiceProvider::provideAudio((audio::AudioService*) &audioService);
	ServiceProvider::provideVideo((graphics::VideoService*) &videoService);
	//DefaultLoggingService("prod/log.txt")
	ServiceProvider::provideLogging((utility::ConsoleLoggingService*) &loggingService);

	//initialize gamestate
	game::gamestate::GameState* currentGameState = new game::gamestate::TestingState();

	double dt;
	double lag = 0;


	SDL_Rect wholeScreen = { 0, 0, windowW, windowH };

	SDL_Event e;

	//Start the main loop
	bool quit = false;
	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) quit = true;
			else currentGameState->processEvent(&e);
		}

		dt = timeSinceLastUpdate.elapsed();
		lag += dt;
		timeSinceLastUpdate.reset();
		
		while (lag >= MS_PER_TICK) {
			currentGameState->update();
			lag -= MS_PER_TICK;
		}

		SDL_RenderClear(mainRenderer);
		SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0, 0, 0xFF);
		SDL_RenderFillRect(mainRenderer, &wholeScreen);

		currentGameState->render();
		SDL_RenderPresent(mainRenderer);
	}
	///gotta be some problem here

	//Deallocate all variables

	delete currentGameState;

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);

	mainRenderer = NULL;
	mainWindow = NULL;

	std::cout << "checkpoint 1" << std::endl;

	ServiceProvider::provideLogging(new utility::NullLoggingService());
	std::cout << "checkpoint 2" << std::endl;
	ServiceProvider::provideVideo(new graphics::NullVideoService());
	std::cout << "checkpoint 3" << std::endl;
	ServiceProvider::provideAudio(new audio::NullAudioService());

	std::cout << "checkpoint 4" << std::endl;

	//Close SDL and various libraries
	close();

	std::string DELETE_ME;
	std::cout << "Press enter to close program " << std::endl;
	std::cin >> DELETE_ME;

	return 0;
}

bool init() {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) && imgFlags)) {
		printf("Unable to initialize SDL_image! SDL_image error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

void close() {
	IMG_Quit();
	SDL_Quit();
}

SDL_Window* buildWindow(const std::string& title, int width, int height) {
	SDL_Window* window = NULL;

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Unable to create window %s! SDL Error: %s\n", title.c_str(), SDL_GetError());
	}

	return window;
}

SDL_Renderer* buildRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = NULL;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == NULL) {
		printf("Unable to create a renderer! SDL Error: %s\n", SDL_GetError());
	}

	return renderer;
}