#include "Textbox.h"

using namespace game;
using namespace ui;

Textbox::Textbox(){

}


Textbox::~Textbox(){

}

void Textbox::render(SDL_Renderer* renderer) {

}

//Load the variables stored in a DynamicObject into this Button
//If the DynamicObject doesn't have a certain variable, the default value is simply kept
void Textbox::loadFromDynamicObject(utility::parsing::DynamicObject* obj) {
	if (obj == NULL) return;

	std::string current = "";

	current = obj->getValue("id");
	if (current != "") easyCast(current, id);
	current = obj->getValue("priority");
	if (current != "") easyCast(current, priority);
	current = obj->getValue("x");
	if (current != "") easyCast(current, x);
	current = obj->getValue("y");
	if (current != "") easyCast(current, y);
	current = obj->getValue("text");
	if (current != "") easyCast(current, text);
}