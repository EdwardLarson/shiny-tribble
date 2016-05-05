#pragma once
#include "C:\Users\larsoe4\Documents\shiny-tribble\shiny-tribble\src\game\ui\UIElement.h"

namespace game{
namespace ui{

class Textbox: public UIElement{
public:
	Textbox();
	virtual ~Textbox();

	virtual void render(SDL_Renderer* renderer) override;

	virtual void loadFromDynamicObject(utility::parsing::DynamicObject * obj) override;

private:
	std::string text;
};

}
}