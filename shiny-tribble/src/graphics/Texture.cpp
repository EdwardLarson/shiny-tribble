#include "Texture.h"

using namespace graphics;

Texture::Texture(SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH): mSheet(sheet){
	clip = { clipX, clipY, clipW, clipH };
}


Texture::~Texture(){

}

void Texture::render(SDL_Renderer* renderer, int x, int y) {
	//First create a quad where this texture will be rendered
	SDL_Rect renderQuad = { x, y, clip.w, clip.h };

	SDL_RenderCopy(renderer, mSheet, &clip, &renderQuad);
}