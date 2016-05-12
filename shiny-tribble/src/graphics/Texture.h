#pragma once

#include <string>
#include <SDL_image.h>
#include <SDL.h>

namespace graphics{

class Texture{
public:
	Texture(SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH);
	virtual ~Texture();

	virtual bool loadFromFile(SDL_Renderer* renderer, const std::string& filename);
	virtual void free();

	inline bool good() { return mSheet != NULL; }

	inline SDL_Texture* getSheet() const { return mSheet; }
	inline int getWidth() const { return clip.w; }
	inline int getHeight() const { return clip.h; }
	inline int getX() const { return clip.x; }
	inline int getY() const { return clip.y; }

	inline void setSheet(SDL_Texture* sheet) { mSheet = sheet; }
	inline void setWidth(int width) { clip.w = width; }
	inline void setHeight(int height) { clip.h = height; }
	inline void setX(int x) { clip.x = x; }
	inline void setY(int y) { clip.y = y; }

	void render(SDL_Renderer* renderer, int x, int y, int w, int h) const;

private:
	SDL_Texture* mSheet;
	SDL_Rect clip;
};

}