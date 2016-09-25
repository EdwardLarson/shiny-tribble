#pragma once

#include <istream>
#include <sstream>
#include <SDL.h>
#include "../../utility/PhysicsLogic.h"
#include "../../utility/UIParsing.h"

namespace game {
namespace ui {

class UIElement
{
public:
	//UIElement();
	//~UIElement();

	virtual void render() = 0;

	virtual void loadFromDynamicObject(utility::parsing::DynamicObject* obj) = 0;
	virtual void onClick() = 0;
	virtual void onMouseOver() = 0;

	int getPriority() { return priority; }
	bool contains(float itemX, float itemY) { return utility::contains(itemX, itemY, x, y, width, height); }

protected:
	std::string id;
	float x, y, width, height;
	//how do I do everything in relative coordinates?
	int priority;
};

//Cast a string to type T
//Just piggybacks off of std::istream's casting, so std::istream needs to know how to cast to T for it to work
template <class T>
void easyCast(const std::string& str, T& target) {
	std::istringstream myStream(str);

	myStream >> target;
}

}
}