#include "UI.h"

using namespace game;
using namespace ui;

UI::UI(){

}


UI::~UI(){

}

//Creates a UI layout based on a text file read in from the hard drive
void UI::buildFromFile(char* filename) {
	std::vector<utility::parsing::DynamicObject*> objects = utility::parsing::parse(filename);

	game::ui::UIElement* newElement = NULL;

	for (unsigned int i = 0; i < objects.size(); i++) {
		//attempt to create a UIElement from this DynamicObject
		newElement = createElementFromDynamicObject(objects[i]);
		//store the newly created UIElement
		if (newElement != NULL) sortIntoElements(newElement);
		//finally, delete each object
		delete objects[i];
	}
}

void UI::render() {
	//render each element in order of priority
	for (std::list<game::ui::UIElement*>::const_iterator iter = elements.begin();
		iter != elements.end();
		++iter) {

		//render element
		(*iter)->render();
	}
}

void UI::processMouseEvent(SDL_Event* event) {
	int mouseX_raw, mouseY_raw;
	SDL_GetMouseState(&mouseX_raw, &mouseY_raw);
	float mouseX, mouseY;
	mouseX = ((float)mouseX_raw) / ServiceProvider::getVideo().getScreenWidth();
	mouseY = ((float)mouseY_raw) / ServiceProvider::getVideo().getScreenHeight();

	for (std::list<game::ui::UIElement*>::iterator iter = elements.begin();
		iter != elements.end();
		++iter) {

		if ((*iter)->contains(mouseX, mouseY)) {
			//now decide on action to take
			(*iter)->onMouseOver();
		}
	}
}

//Create an actual UIElement from a DynamicObject
game::ui::UIElement* UI::createElementFromDynamicObject(utility::parsing::DynamicObject* obj) {
	UIElement* output = NULL;

	if (obj->getType() == "BUTTON") {
		output = new game::ui::Button();
	}

	if (output != NULL) output->loadFromDynamicObject(obj);

	return output;
}

//Perform a sorted insert of element into elements based on the UIElements' priorities
void UI::sortIntoElements(game::ui::UIElement* element) {
	std::list<game::ui::UIElement*>::iterator iter;
	for (iter = elements.begin(); iter != elements.end(); ++iter) {
		if ((element->getPriority() < (*iter)->getPriority())) break;
	}

	elements.insert(iter, element);
}