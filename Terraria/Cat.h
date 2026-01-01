#include "Animable.h"
#include <functional>
#include "VelocityComponent.h"

namespace sf {
	class Texture;
}

#pragma once
class Cat : public Animable
{
public:
	Cat(sf::Texture& texture, std::string animationsDataFileName);

	float speed = 900.0f;
	float jumpForce = 1200.0f;

	void physicsProcess(float delta, std::function<bool(sf::FloatRect)> tilemapCollision);

	void jump();
private:
	enum Action
	{
		None,
		Idle,
		Walking,
		Jumping
	};
	Action m_currentAction;
	VelocityComponent m_velocityComponent;
	bool isGrounded = false;

	void setAction(Action toAction);
	bool handleMovement(float delta);
};
