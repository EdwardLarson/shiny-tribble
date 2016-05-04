#pragma once

#include "UIElement.h"

namespace game {
namespace ui {

class Button: public UIElement
{
public:
	Button();
	virtual ~Button();

	virtual void render() override;

	virtual void loadFromDynamicObject(utility::parsing::DynamicObject * obj) override;

private:
	double x, y;
	std::string text;
};

}
}