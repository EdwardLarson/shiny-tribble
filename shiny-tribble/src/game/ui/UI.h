#pragma once

#include <vector>
#include <list>
#include <SDL.h>
#include "../../game/ui/UIElement.h"
#include "../../game/ui/Button.h"

namespace game{
namespace ui{

class UI
{
public:
	UI();
	virtual ~UI();

	virtual void render();

	virtual void buildFromFile(char* filename);

private:
	std::list<game::ui::UIElement*> elements;

	game::ui::UIElement* createElementFromDynamicObject(utility::parsing::DynamicObject* obj);
	void sortIntoElements(game::ui::UIElement* element);
};


}
}