#include "Cat.h"
#include <iostream>

Cat::Cat(sf::Texture& texture, std::string animationsDataFileName) : 
	Animable(texture, animationsDataFileName),
	m_velocityComponent(*this, {200, 0}, true)
{	
	m_velocityComponent.setFriction(400.0f);

	setAction(Action::Idle);
}

void Cat::physicsProcess(float delta)
{
	m_velocityComponent.process(delta);

	bool isMoving = handleMovement(delta);

	if (!isMoving)
	{
		setAction(Action::Idle);		
		return;
	}
	setAction(Action::Walking);
}

void Cat::setAction(Action toAction)
{
	if (m_currentAction == toAction)
	{
		return;
	}

	m_currentAction = toAction;	
	switch (m_currentAction)
	{
	case Action::Idle:
		setAnimation("idle");
		break;
	case Action::Walking:		
		setAnimation("walk");
		break;
	}
}

bool Cat::handleMovement(float delta)
{
	bool isLeftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
	bool isRightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);

	if (!isLeftKeyPressed && !isRightKeyPressed)
	{
		return false;
	}

	float totalSpeed = speed * delta;
	int directionMultiplier = isRightKeyPressed ? 1 : -1;

	m_velocityComponent.addVelocity({ totalSpeed * static_cast<float>(directionMultiplier), 0 });

	float scale = abs(getScale().x);
	setScale({ scale * -directionMultiplier, scale });

	return true;
}
