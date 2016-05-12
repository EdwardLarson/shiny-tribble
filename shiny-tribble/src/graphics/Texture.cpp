#include "Texture.h"
#include "../ServiceProvider.h"

using namespace graphics;

Texture::Texture()
	: mRenderer(NULL), mSheet(NULL){
	mClip = { 0, 0, 0, 0 };
}

Texture::Texture(SDL_Renderer* renderer, SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH)
	: mRenderer(renderer), mSheet(sheet){
	mClip = { clipX, clipY, clipW, clipH };
}


Texture::~Texture(){
	//Don't necessarily want to clear sheet as it could be the texture atlas
}

void Texture::render(int x, int y, int w, int h) const {
	//Create a renderquad where this texture will be rendered
	SDL_Rect renderQuad = { 
		x, 
		y, 
		w,
		h 
	};
	
	SDL_RenderCopy(mRenderer, mSheet, &mClip, &renderQuad);
}

void Texture::render(float x, float y, int w, int h) const {
	//Get the total width and height of the target
	int totalW, totalH;
	SDL_GetRendererOutputSize(mRenderer, &totalW, &totalH);

	//Create a renderquad for the absolute position to render to based on the relative coordinates
	SDL_Rect renderQuad = { 
		((int) ((float) x * totalW)), 
		((int)((float) y * totalH)), 
		w, 
		h 
	};

	SDL_RenderCopy(mRenderer, mSheet, &mClip, &renderQuad);
}

void Texture::render(int x, int y, float w, float h) const {
	//Get the total width and height of the target
	int totalW, totalH;
	SDL_GetRendererOutputSize(mRenderer, &totalW, &totalH);

	//Create a renderquad for the absolute position to render to based on the relative dimensions
	SDL_Rect renderQuad = {
		x,
		y,
		((int)((float)w * totalW)),
		((int)((float)h * totalH)),
	};

	SDL_RenderCopy(mRenderer, mSheet, &mClip, &renderQuad);
}

void Texture::render(float x, float y, float w, float h) const {
	//Get the total width and height of the target
	int totalW, totalH;
	SDL_GetRendererOutputSize(mRenderer, &totalW, &totalH);

	//Create a renderquad for the absolute position to render to based on the relative dimensions
	SDL_Rect renderQuad = {
		((int)((float)x * totalW)),
		((int)((float)y * totalH)),
		((int)((float)w * totalW)),
		((int)((float)h * totalH)),
	};

	SDL_RenderCopy(mRenderer, mSheet, &mClip, &renderQuad);
}

/*
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
			mClip.w = loadedSurface->w;
			mClip.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return mSheet != NULL;
}
*/

void Texture::free() {
	if (mSheet != NULL) {
		SDL_DestroyTexture(mSheet);
		mSheet = NULL;
	}
}