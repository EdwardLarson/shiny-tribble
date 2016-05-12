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

void NullVideoService::render(const std::string& texturePath, int x, int y) {

}

void NullVideoService::render(const std::string& texturePath, float relativeX, float relativeY) {

}

void NullVideoService::render(const Texture& texture, int x, int y, int width, int height) {

}

Texture NullVideoService::loadTexture(const std::string& filename) {
	return Texture(NULL, 0, 0, 0, 0);
}

//DefaultVideoService
//========================================

DefaultVideoService::DefaultVideoService(SDL_Renderer* renderer)
	: mRenderer(renderer), mSheet(NULL), mAtlas(DEFAULT_ATLAS_DIM, DEFAULT_ATLAS_DIM, 128) {

	//create the base sheet
	mSheet = SDL_CreateTexture(
								renderer, 
								SDL_PIXELFORMAT_RGBA8888, 
								SDL_TEXTUREACCESS_TARGET, 
								DEFAULT_ATLAS_DIM, DEFAULT_ATLAS_DIM
								);

	if (mSheet == NULL) {
		ServiceProvider::getLogging() << "Unable to create base sheet! SDL Error: " << SDL_GetError() << '\n';
	}
}

DefaultVideoService::~DefaultVideoService() {

}

void DefaultVideoService::render(const std::string& texturePath, int x, int y) {
	//find the texture loaded from this filename
	TextureMap::iterator iter = textures.find(texturePath);
	if (iter != textures.end()) {
		//render the textures
		//iter->second->render(mRenderer, x, y);
	}else {
		//texture was never loaded... 
		//Do we load the texture in the middle of rendering (expensive operation)?
		//Or go ahead an do nothing (very cheap)?
		ServiceProvider::getLogging() << "Attempt to render an unloaded texture!" << '\n';
	}
}

void DefaultVideoService::render(const std::string& texturePath, float relativeX, float relativeY) {
	int w, h;
	SDL_GetRendererOutputSize(mRenderer, &w, &h);
	int x = (int) ((float) relativeX * w);
	int y = (int) ((float) relativeY * h);
	render(texturePath, x, y);
}

void DefaultVideoService::render(const Texture& texture, int x, int y, int width, int height) {
	texture.render(mRenderer, x, y, width, height);
}

Texture DefaultVideoService::loadTexture(const std::string& filename) {
	Texture newTexture(NULL, 0, 0, 0, 0);

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

Texture DefaultVideoService::createSDLTextureFromFile(const char* filename) {
	SDL_Texture* tex = NULL;
	Texture wrappedTex(tex, 0, 0, 0, 0);

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