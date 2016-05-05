#pragma once

#include "UIElement.h"

namespace game {
namespace ui {

class Button: public UIElement
{
public:
	Button();
	virtual ~Button();

	virtual void render(SDL_Renderer* renderer) override;

	virtual void loadFromDynamicObject(utility::parsing::DynamicObject * obj) override;

private:
	std::string text;
};

}
}