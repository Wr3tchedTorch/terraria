#include "Cat.h"

void Cat::physicsProcess(float delta)
{
	float totalSpeed = speed * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
	{
		move({ -totalSpeed, 0 });
		setScale({ 1, 1 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
	{
		move({ totalSpeed, 0 });
		setScale({ -1, 1 });
	}
}
