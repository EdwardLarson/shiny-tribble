#pragma once

#include <string>
#include <SDL_image.h>
#include <SDL.h>

namespace graphics{

class Texture{
public:
	Texture();
	Texture(SDL_Renderer* renderer, SDL_Texture* sheet, int clipX, int clipY, int clipW, int clipH);
	virtual ~Texture();

	//virtual bool loadFromFile(SDL_Renderer* renderer, const std::string& filename);
	virtual void free();

	inline bool good() { return mSheet != NULL; }

	inline SDL_Texture* getSheet() const { return mSheet; }
	inline SDL_Rect getRect() const { return mClip; }
	inline int getWidth() const { return mClip.w; }
	inline int getHeight() const { return mClip.h; }
	inline int getX() const { return mClip.x; }
	inline int getY() const { return mClip.y; }

	inline void setSheet(SDL_Texture* sheet) { mSheet = sheet; }
	inline void setRect(const SDL_Rect& rect) { mClip = rect; }
	inline void setWidth(int width) { mClip.w = width; }
	inline void setHeight(int height) { mClip.h = height; }
	inline void setX(int x) { mClip.x = x; }
	inline void setY(int y) { mClip.y = y; }

	/*
	//Render with absolute position and dimensions
	void render(int x, int y, int w, int h) const;
	//Render with relative position and absolute dimensions
	void render(float x, float y, int w, int h) const;
	//Render with absolute position and relative dimensions
	void render(int x, int y, float w, float h) const;*/
	//Render with relative position and dimensions
	virtual void render(float x, float y, float w, float h) const;

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mSheet;
	SDL_Rect mClip;
};

}