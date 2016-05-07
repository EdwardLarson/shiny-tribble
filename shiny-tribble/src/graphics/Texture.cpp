#include "Texture.h"
#include "../ServiceProvider.h"

using namespace graphics;

Texture::Texture(SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH): mSheet(sheet){
	clip = { clipX, clipY, clipW, clipH };
}


Texture::~Texture(){

}

void Texture::render(SDL_Renderer* renderer, int x, int y) {
	//First create a quad where this texture will be rendered
	SDL_Rect renderQuad = { x, y, clip.w, clip.h };
	
	SDL_RenderCopy(renderer, mSheet, NULL, &renderQuad);
}

bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& filename) {
	free();

	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
	if (loadedSurface == NULL) {
		//report error
		ServiceProvider::getLogging() << "ERROR: Unable to load texture " << filename << ENDL;
	}else {
		mSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (mSheet == NULL) {
			//report error
			ServiceProvider::getLogging() << "ERROR: Unable to create texture from " << filename << ENDL;
		}else {
			clip.w = loadedSurface->w;
			clip.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return mSheet != NULL;
}

void Texture::free() {
	if (mSheet != NULL) {
		SDL_DestroyTexture(mSheet);
		mSheet = NULL;
	}
}