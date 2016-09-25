#pragma once
#include "Texture.h"
#include <list>

namespace graphics{
class ParallaxTexture : public Texture{

private:
	struct ParallaxLayer {
		Texture* layerTexture;
		int z;
	};
public:
	ParallaxTexture(bool reverseRender, int z0);
	virtual ~ParallaxTexture();

	void addTexture(Texture* texture, int z);

	void render(float x, float y, float w, float h) const;

	void moveRect(float deltaX, float deltaY);

	//parallax textures are made up of multiple textures on multiple layers with different distances from a base layer
	//base layer is closest to camera, and it is a 1-to-1 relationship between movement of the camera and movement of the base layer

	//each layer has an SDL texture (either an independent one or a section of the dynamic atlas) and a z

private:
	std::list<ParallaxLayer> layers;

	bool m_reverseRender;

	int m_z0; //distance from the camera layer that the "z=0" layer will be
	float cameraDeltaX; //x distance that the camera frame has moved from the initial "aligned" position
	float cameraDeltaY; //y distance that the camera frame has moved from the initial "aligned" position

	SDL_Rect cameraLayer;

	inline float getLayerXOffset(int layerZ) const;
	inline float getLayerYOffset(int layerZ) const;

};

}