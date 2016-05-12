#include "Entity.h"

using namespace game;
using namespace entity;

Entity::Entity(): mTexture(NULL), x(0), y(0){
	
}


Entity::~Entity(){

}

void Entity::update(){

}

void Entity::render(SDL_Renderer* renderer) {
	if (mTexture != NULL) mTexture->render(x, y, 1, 1);
}