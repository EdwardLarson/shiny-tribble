#include "VideoService.h"

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

void NullVideoService::loadTexture(const std::string& filename) {

}

//DefaultVideoService
//========================================

DefaultVideoService::DefaultVideoService(SDL_Renderer* renderer): mRenderer(renderer) {
	
}

DefaultVideoService::~DefaultVideoService() {

}

void DefaultVideoService::render(const std::string& texturePath, int x, int y) {
	//find the texture loaded from this filename
	TextureMap::iterator iter = textures.find(texturePath);
	if (iter != textures.end()) {
		//render the textures
		iter->second->render(mRenderer, x, y);
	}else {
		//texture was never loaded... 
		//Do we load the texture in the middle of rendering (expensive operation)?
		//Or go ahead an do nothing (very cheap)?
		std::cout << "Attempt to render an unloaded texture!" << std::endl;
	}
}

void DefaultVideoService::render(const std::string& texturePath, float relativeX, float relativeY) {
	int w, h;
	SDL_GetRendererOutputSize(mRenderer, &w, &h);
	int x = relativeX * w;
	int y = relativeY * h;
	render(texturePath, x, y);
}

void DefaultVideoService::loadTexture(const std::string& filename) {
	std::cout << "load texture was called" << std::endl;
	TextureMap::iterator iter;
	iter = textures.find(filename);
	//check if texture already exists
	if (iter == textures.end()) {
		//texture does not exist and must be created
		Texture* newTex = new Texture(NULL, 0, 0, 0, 0);
		if (newTex->loadFromFile(mRenderer, filename)) {
			//if texture was successfully loaded, insert it into the map
			textures.insert(std::make_pair(filename, newTex));
			//ServiceProvider::getLogging()->log("Successfully loaded " + filename + "\n");
			std::cout << "successfully loaded " << filename << std::endl;
		}else {
			//ServiceProvider::getLogging()->log("Failed to load " + filename + "\n");
			std::cout << "unable to load " << filename << std::endl;
		}
	}else {
		//ServiceProvider::getLogging()->log(filename + " was already loaded\n");
		std::cout << "texture " << filename << " was already loaded" << std::endl;
	}
}