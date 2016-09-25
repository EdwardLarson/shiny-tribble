#include "Button.h"

using namespace game;
using namespace ui;

Button::Button(){

}


Button::~Button(){

}

void Button::render() {
	mTexture.render(x, y, width, height);
}

//Load the variables stored in a DynamicObject into this Button
//If the DynamicObject doesn't have a certain variable, the default value is simply kept
void Button::loadFromDynamicObject(utility::parsing::DynamicObject* obj) {
	if (obj == NULL) return;

	std::string current = "";

	//get id
	current = obj->getValue("id");
	if (current != "") easyCast(current, id);
	//get priority
	current = obj->getValue("priority");
	if (current != "") easyCast(current, priority);
	//get x coord
	current = obj->getValue("x");
	if (current != "") easyCast(current, x);
	//get y coord
	current = obj->getValue("y");
	if (current != "") easyCast(current, y);
	//get width
	current = obj->getValue("width");
	if (current != "") easyCast(current, width);
	//get height
	current = obj->getValue("height");
	if (current != "") easyCast(current, height);
	//get text
	current = obj->getValue("text");
	if (current != "") easyCast(current, text);
	//get texture
	current = obj->getValue("img");
	if (current != "") {
		mTexture = ServiceProvider::getVideo().loadTexture(current);
	}
}

void Button::onClick() {

}

void Button::onMouseOver() {
	ServiceProvider::getLogging().log("Moused over button: " + id);
}