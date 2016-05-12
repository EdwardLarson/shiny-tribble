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

	//needs some rendering functions
	virtual void render(const std::string& texturePath, int x, int y) = 0;
	virtual void render(const std::string& texturePath, float relativeX, float relativeY) = 0;
	virtual void render(const Texture& texture, int x, int y, int width, int height) = 0;

	virtual void renderAtlas() {}

	//load a texture from a file, returns the ID of the texture
	virtual Texture loadTexture(const std::string& filename) = 0;
};

class NullVideoService: public VideoService {
public:
	NullVideoService();
	virtual ~NullVideoService();

	virtual void render(const std::string& texturePath, int x, int y) override;
	virtual void render(const std::string& texturePath, float relativeX, float relativeY) override;
	virtual void render(const Texture& texture, int x, int y, int width, int height) override;

	virtual Texture loadTexture(const std::string& filename);
};

class DefaultVideoService : public VideoService {
public:
	DefaultVideoService(SDL_Renderer* renderer);
	virtual ~DefaultVideoService();

	virtual void render(const std::string& texturePath, int x, int y) override;
	virtual void render(const std::string& texturePath, float relativeX, float relativeY) override;
	virtual void render(const Texture& texture, int x, int y, int width, int height) override;

	virtual void renderAtlas();

	virtual Texture loadTexture(const std::string& filename) override;

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