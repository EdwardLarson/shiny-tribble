#pragma once

#include <SDL.h>

#include "Texture.h"

namespace graphics{

	Texture* createTextureFromPath();

	/*
	okay lets think this through
	so each entity CLASS needs to have its own texture
	but multiple textures  may share a sheetS

	solutions:
	each implementation has a static mTexture - is this even possible?
	createTextureFromPath takes in a set of already loaded sheets? i dunno

	entities know their texture ID, which can be used by some render function to get the actual graphics::Texture from a map
	that map is stored in - gamestate? I guess. That's the only thing makes sense tbh
	When gamestate is created/destroyed it handles loading/unloading textures
	I like it
	*/

}