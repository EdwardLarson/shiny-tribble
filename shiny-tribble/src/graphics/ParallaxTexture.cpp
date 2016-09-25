#include "ParallaxTexture.h"



graphics::ParallaxTexture::ParallaxTexture(bool reverseRender, int z0): Texture(), layers(), m_reverseRender(reverseRender), m_z0(z0){
	cameraLayer = { 0, 0, 0, 0 };
	cameraDeltaX = 0;
	cameraDeltaY = 0;
}


graphics::ParallaxTexture::~ParallaxTexture(){
}

void graphics::ParallaxTexture::addTexture(Texture* texture, int z) {
	//insert new parallax layer  in order, so that the highest z is first
	std::list<ParallaxLayer>::iterator iter;
	for (iter = layers.begin();
			iter != layers.end();
			++iter) {
		//check if the new layer's z is higher than the current iterator's z
		//this would mean that it should be inserted before the current iterator
		if (m_reverseRender? (z < iter->z) : (z > iter->z)) {
			break;
		}
	}

	layers.insert(iter, {
		texture,
		z
		});
}

void graphics::ParallaxTexture::render(float x, float y, float w, float h) const {
	for (std::list<ParallaxLayer>::const_iterator iter = layers.begin(); iter != layers.end(); ++iter) {
		//use z layer to shift renderings of each layer relative to base layer
		float offsetX = x + getLayerXOffset(iter->z);
		float offsetY = y + getLayerYOffset(iter->z);

		iter->layerTexture->render(offsetX, offsetY, w, h);
	}
}

inline float graphics::ParallaxTexture::getLayerXOffset(int layerZ) const {
	//return (-1 * (cameraDeltaX / (float) m_z0) * layerZ);
	return ( -1 * cameraDeltaX * ( ((float)layerZ) / ((float)m_z0) ) );
}

inline float graphics::ParallaxTexture::getLayerYOffset(int layerZ) const {
	//return (-1 * (cameraDeltaX / (float) m_z0) * layerZ);
	return (-1 * cameraDeltaY * (((float)layerZ) / ((float)m_z0)));

}

void graphics::ParallaxTexture::moveRect(float deltaX, float deltaY) {
	cameraDeltaX += deltaX;
	cameraDeltaY += deltaY;
}