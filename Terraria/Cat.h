#include "Animable.h"
#include "VelocityComponent.h"

namespace sf {
	class Texture;
}

#pragma once
class Cat : public Animable
{
public:
	Cat(sf::Texture& texture, std::string animationsDataFileName);

	float speed = 600.0f;
	void physicsProcess(float delta);
private:
	enum Action
	{
		None,
		Idle,
		Walking
	};
	Action m_currentAction;
	VelocityComponent m_velocityComponent;

	void setAction(Action toAction);
	bool handleMovement(float delta);
};
