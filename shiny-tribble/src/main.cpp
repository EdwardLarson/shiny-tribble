/*
Created by Ed Larson 5/1/2016

LAST UPDATED: 5/1/2016
*/

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

#include <iostream>
#include <chrono>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include "utility\Timer.h"

bool init();
void close();

SDL_Window* buildWindow(const std::string& title, int width, int height);
SDL_Renderer* buildRenderer(SDL_Window* window);

int main(int argc, char* argv[]) {

	//Initialize SDL and its various libraries

	//Create all necessary variables

	// ---SDL---
	init();

	SDL_Window* mainWindow = buildWindow("Platformer Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Renderer* mainRenderer = buildRenderer(mainWindow);

	// ---TIME---
	utility::time::Timer runningTime;
	utility::time::Timer dt;
	
	const double S_PER_TICK = 0.015; //gives about 60 ticks per second

	// ---GAME---
	//GameState* currentGameState = new GameState_MainMenu;

	int ticks = 0;
	int loops = 0;

	SDL_Event e;

	//Start the main loop
	bool quit = false;
	while (!quit) {
		if (dt.elapsed() >= S_PER_TICK) {
			//currentGameState->update();
			dt.reset();
			ticks++;

			std::cout << "Tick number " << ticks << " over " << (runningTime.elapsed()) << " seconds" << std::endl;
		}
		//currentGameState->render();
		SDL_RenderClear(mainRenderer);
		SDL_RenderPresent(mainRenderer);

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) quit = true;
		}

		loops++;
	}

	//Deallocate all variables
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);

	mainRenderer = NULL;
	mainWindow = NULL;

	//Close SDL and various libraries
	close();

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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Unable to create a renderer! SDL Error: %s\n", SDL_GetError());
	}

	return renderer;
}