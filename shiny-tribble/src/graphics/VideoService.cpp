#include "VideoService.h"

//logging needs to be imported here rather than in the header to avoid calling the type before it exists
#ifndef __SERVICE_PROVIDER__
#include "../ServiceProvider.h"
#endif

using namespace graphics;

VideoService::~VideoService(){
}

//NullVideoService
//========================================

NullVideoService::NullVideoService() {

}

NullVideoService::~NullVideoService() {

}

Texture NullVideoService::loadTexture(const std::string& filename) {
	return Texture(NULL, NULL, 0, 0, 0, 0);
}

void NullVideoService::unloadTexture(const Texture& texture) {

}

void NullVideoService::unloadAllTextures() {

}

//DefaultVideoService
//========================================

DefaultVideoService::DefaultVideoService(SDL_Renderer* renderer)
	: mRenderer(renderer), mSheet(NULL), mAtlas(DEFAULT_ATLAS_DIM, DEFAULT_ATLAS_DIM, 128) {

	SDL_GetRendererOutputSize(mRenderer, &screenWidth, &screenHeight);

	//create the base sheet
	mSheet = SDL_CreateTexture(
								renderer, 
								SDL_PIXELFORMAT_RGBA8888, 
								SDL_TEXTUREACCESS_TARGET, 
								DEFAULT_ATLAS_DIM, DEFAULT_ATLAS_DIM
								);

	if (mSheet == NULL) {
		ServiceProvider::getLogging() << "Unable to create base sheet! SDL Error: " << SDL_GetError() << '\n';
	}else {
		//make base atlas transparent
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
		SDL_SetRenderTarget(mRenderer, mSheet);
		SDL_SetTextureBlendMode(mSheet, SDL_BLENDMODE_BLEND);
		SDL_RenderClear(mRenderer);
		SDL_SetRenderTarget(mRenderer, NULL);
	}
}

DefaultVideoService::~DefaultVideoService() {

}

Texture DefaultVideoService::loadTexture(const std::string& filename) {
	Texture newTexture(mRenderer, NULL, 0, 0, 0, 0);

	TextureMap::iterator iter;
	iter = textures.find(filename);
	//check if texture already exists
	if (iter == textures.end()) {
		//Load the texture from the file
		newTexture = createSDLTextureFromFile(filename.c_str());
		if (newTexture.good()) {
			//if texture was successfully pulled from storage, need to add it to the DynamicAtlas
			SDL_Rect atlasRect = mAtlas.addRectangle(newTexture.getWidth(), newTexture.getHeight());

			//make sure a spot was found in the dynamic atlas
			if (atlasRect.w == newTexture.getWidth() && atlasRect.h == newTexture.getHeight()) {
				newTexture.setX(atlasRect.x);
				newTexture.setY(atlasRect.y);

				//Add the loaded texture to the sheet
				SDL_SetRenderTarget(mRenderer, mSheet);
				SDL_RenderCopy(mRenderer, newTexture.getSheet(), NULL, &atlasRect);
				//Reset render target
				SDL_SetRenderTarget(mRenderer, NULL);

				//Free the original loaded texture
				SDL_DestroyTexture(newTexture.getSheet());
				newTexture.setSheet(mSheet);
			}

			//if texture was successfully loaded, insert its name into the map
			textures.insert(filename);
			
			ServiceProvider::getLogging() << "successfully loaded " << filename << '\n';
		}else {
			ServiceProvider::getLogging() << "unable to load " << filename << '\n';
		}
	}else {
		ServiceProvider::getLogging() << "texture " << filename << " was already loaded" << '\n';
	}

	return newTexture;
}

void DefaultVideoService::unloadTexture(const Texture& texture) {
	//First, attempt to remove the rectangle from the dynamic atlas and see if it was in there to begin with
	SDL_Rect texRect = texture.getRect();
	if (mAtlas.removeRectangle(texRect.x, texRect.y, texRect.w, texRect.h)) {
		//Erase that texture from the actual sheet
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
		SDL_SetRenderTarget(mRenderer, mSheet);
		SDL_SetTextureBlendMode(mSheet, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(mRenderer, &texRect);
		SDL_SetRenderTarget(mRenderer, NULL);
	}
}

void DefaultVideoService::unloadAllTextures() {
	//make base atlas transparent
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	SDL_SetRenderTarget(mRenderer, mSheet);
	SDL_SetTextureBlendMode(mSheet, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderTarget(mRenderer, NULL);

	//clear the atlas so it can allocate new rectangles
	mAtlas.clear();
}

Texture DefaultVideoService::createSDLTextureFromFile(const char* filename) {
	SDL_Texture* tex = NULL;
	Texture wrappedTex(mRenderer, tex, 0, 0, 0, 0);

	SDL_Surface* loadedSurface = IMG_Load(filename);
	if (loadedSurface == NULL) {
		//report error
		ServiceProvider::getLogging() << "ERROR: Unable to load texture " << filename << ENDL;
	}
	else {
		tex = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (tex == NULL) {
			//report error
			ServiceProvider::getLogging() << "ERROR: Unable to create texture from " << filename << ENDL;
		}else {
			wrappedTex.setWidth(loadedSurface->w);
			wrappedTex.setHeight(loadedSurface->h);
			wrappedTex.setSheet(tex);
		}
		SDL_FreeSurface(loadedSurface);
	}

	return wrappedTex;
}

void DefaultVideoService::renderAtlas() {
	SDL_RenderCopy(mRenderer, mSheet, NULL, NULL);
}