#include "Animable.h"

namespace sf {
	class Texture;
}

#pragma once
class Cat : public Animable
{
public:
	Cat(sf::Texture& texture, std::string animationsDataFileName);

	float speed = 100.0f;
	void physicsProcess(float delta);
private:
	enum Action
	{
		None,
		Idle,
		Walking
	};
	Action m_currentAction;

	void setAction(Action toAction);
};
