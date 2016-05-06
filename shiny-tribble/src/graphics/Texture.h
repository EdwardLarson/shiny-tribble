#pragma once

#include <string>
#include <SDL_image.h>
#include <SDL.h>

namespace graphics{

class Texture
{
public:
	Texture(SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH);
	virtual ~Texture();

	virtual bool loadFromFile(SDL_Renderer* renderer, const std::string& filename);
	virtual void free();

	void render(SDL_Renderer* renderer, int x, int y);

private:
	SDL_Texture* mSheet;
	SDL_Rect clip;
};

}