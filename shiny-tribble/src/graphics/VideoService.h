#pragma once

#include <unordered_set>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "DynamicAtlas.h"


namespace graphics{

class VideoService{
public:
	virtual ~VideoService();

	virtual void renderAtlas() {}

	//load a texture from a file, returns the ID of the texture
	virtual Texture loadTexture(const std::string& filename) = 0;
	virtual void unloadAllTextures() = 0;
};

class NullVideoService: public VideoService {
public:
	NullVideoService();
	virtual ~NullVideoService();

	virtual Texture loadTexture(const std::string& filename);
	virtual void unloadAllTextures();
};

class DefaultVideoService : public VideoService {
public:
	DefaultVideoService(SDL_Renderer* renderer);
	virtual ~DefaultVideoService();

	virtual void renderAtlas();

	virtual Texture loadTexture(const std::string& filename) override;
	virtual void unloadAllTextures();

protected:
	Texture createSDLTextureFromFile(const char* filename);

	static const int DEFAULT_ATLAS_DIM = 1024;

	typedef std::unordered_set<std::string, std::hash<std::string> > TextureMap;
	TextureMap textures;

	SDL_Renderer* mRenderer;
	SDL_Texture* mSheet;
	DynamicAtlas mAtlas;
};

}