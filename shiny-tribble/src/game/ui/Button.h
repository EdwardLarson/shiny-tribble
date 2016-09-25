#pragma once

#include "UIElement.h"
#include "../../graphics/Texture.h"
#include "../../ServiceProvider.h"

namespace game {
namespace ui {

class Button: public UIElement
{
public:
	Button();
	virtual ~Button();

	virtual void render() override;

	virtual void loadFromDynamicObject(utility::parsing::DynamicObject * obj) override;
	virtual void onClick() override;
	virtual void onMouseOver() override;

private:
	std::string text;
	graphics::Texture mTexture;
};

}
}