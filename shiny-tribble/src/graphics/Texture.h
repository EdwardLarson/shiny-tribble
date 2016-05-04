#pragma once

#include <SDL.h>

namespace graphics{

class Texture
{
public:
	Texture(SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH);
	virtual ~Texture();

	void render(SDL_Renderer* renderer, int x, int y);

private:
	SDL_Texture* mSheet;
	SDL_Rect clip;
};

}