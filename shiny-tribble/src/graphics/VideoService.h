#pragma once

#include <unordered_map>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"


namespace graphics{

class VideoService{
public:
	virtual ~VideoService();

	//needs some rendering functions
	virtual void render(const std::string& texturePath, int x, int y) = 0;
	virtual void render(const std::string& texturePath, float relativeX, float relativeY) = 0;

	//load a texture from a file, returns the ID of the texture
	virtual void loadTexture(const std::string& filename) = 0;

protected:
	typedef std::unordered_map<const std::string, Texture*, std::hash<std::string> > TextureMap;
	TextureMap textures;
};

class NullVideoService: public VideoService {
public:
	NullVideoService();
	virtual ~NullVideoService();

	virtual void render(const std::string& texturePath, int x, int y) override;
	virtual void render(const std::string& texturePath, float relativeX, float relativeY) override;

	virtual void loadTexture(const std::string& filename);
};

class DefaultVideoService : public VideoService {
public:
	DefaultVideoService(SDL_Renderer* renderer);
	virtual ~DefaultVideoService();

	virtual void render(const std::string& texturePath, int x, int y) override;
	virtual void render(const std::string& texturePath, float relativeX, float relativeY) override;

	virtual void loadTexture(const std::string& filename) override;

protected:
	SDL_Renderer* mRenderer;
};

}