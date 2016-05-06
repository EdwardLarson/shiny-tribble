#pragma once

#include <unordered_map>
#include "Texture.h"

namespace graphics{

class VideoService{
public:
	virtual ~VideoService();

	//needs some rendering functions
	virtual void render(const std::string& texturePath, int x, int y) = 0;

	//load a texture from a file, returns the ID of the texture
	virtual void loadTexture(const std::string& filename) = 0;

private:
	std::unordered_map<const std::string, Texture*, std::hash<std::string> > textures;
};

class NullVideoService: public VideoService {
public:
	NullVideoService();
	virtual ~NullVideoService();

	virtual void render(const std::string& texturePath, int x, int y) override;

	virtual void loadTexture(const std::string& filename);
};

class DefaultVideoService : public VideoService {
	DefaultVideoService();
	virtual ~DefaultVideoService();

	virtual void render(const std::string& texturePath, int x, int y);

	virtual void loadTexture(const std::string& filename) override;
};

}