#include "Cat.h"
#include <iostream>
#include <limits>
#include "CollisionComponent.h"

Cat::Cat(sf::Texture& texture, std::string animationsDataFileName) : 
	Animable(texture, animationsDataFileName),
	m_velocityComponent(*this, {300, 0}, true)
{	
	m_velocityComponent.setFriction(1000.0f);

	setAction(Action::Idle);
}

void Cat::physicsProcess(float delta, std::vector<sf::Vector2f> dirtPositions)
{
	sf::Vector2f size(m_sprite.getGlobalBounds().size);
	sf::FloatRect collisionRect({ {getPosition().x, getPosition().y},
								{size.x, size.y+10}});
	
	bool colided = false;

	for (const auto& dirtPosition : dirtPositions)
	{
		if (CollisionComponent::checkTileAABBCollision(collisionRect, { dirtPosition, {16*3, 16*3} }))
		{
			m_velocityComponent.setSimulatePhysics(false);
			if (!isGrounded)
			{
				m_velocityComponent.setVelocity({ m_velocityComponent.getVelocity().x, 0 });
			}
			colided = true;
			break;
		}
	}

	isGrounded = colided;
	
	if (!isGrounded)
	{
		m_velocityComponent.setSimulatePhysics(true);
	}

	m_velocityComponent.process(delta);

	bool isMoving = handleMovement(delta);

	if (!isGrounded)
	{
		setAction(Action::Jumping);
		return;
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
	case Action::Jumping:
		setAnimation("jump");
		break;
	}
}

bool Cat::handleMovement(float delta)
{
	bool isLeftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
	bool isRightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);

	if (!isLeftKeyPressed && !isRightKeyPressed)
	{
		m_velocityComponent.setApplyFriction(true);
		return false;
	}
	m_velocityComponent.setApplyFriction(false);
	float totalSpeed = speed * delta;

	int directionMultiplier = isRightKeyPressed ? 1 : -1;

	m_velocityComponent.addVelocity({ totalSpeed * static_cast<float>(directionMultiplier), 0 });
	if (!isGrounded)
	{
		m_velocityComponent.setVelocity({ 
			std::numeric_limits<float>::max() * static_cast<float>(directionMultiplier),
			m_velocityComponent.getVelocity().y
		});
	}

	float scale = abs(getScale().x);
	setScale({ scale * -directionMultiplier, scale });

	return true;
}

void Cat::jump()
{
	if (!isGrounded)
	{
		return;
	}

	m_velocityComponent.addVelocity({ 0, -jumpForce });
	setAction(Action::Jumping);
}