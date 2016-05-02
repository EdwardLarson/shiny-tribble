#pragma once

namespace game {
namespace entity {

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update();
};

}
}

