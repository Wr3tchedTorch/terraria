#include "Cat.h"
#include <iostream>

Cat::Cat(sf::Texture& texture, std::string animationsDataFileName) : Animable(texture, animationsDataFileName)
{	
	setAction(Action::Idle);
}

void Cat::physicsProcess(float delta)
{
	float totalSpeed = speed * delta;

	bool isMoving = false;

	bool isLeftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
	bool isRightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);

	if (isLeftKeyPressed || isRightKeyPressed)
	{
		isMoving = true;
		int multiplier = isRightKeyPressed ? 1 : -1;

		move({ totalSpeed * static_cast<float>(multiplier), 0 });

		float scale = abs(getScale().x);
		setScale({ scale * -multiplier, scale });
	}

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
