#include "VelocityComponent.h"
#include <iostream>
#include <string>
#include <algorithm>

VelocityComponent::VelocityComponent(sf::Transformable& parentTransformable, sf::Vector2f maxVelocity, bool simulatePhysics) :
	m_parentTransformable(parentTransformable)
{
	setMaxVelocity(maxVelocity);

	m_simulatePhysics = simulatePhysics;
}

void VelocityComponent::process(float delta)
{
	if (m_simulatePhysics)
	{
		addGravity(delta);
	}
	if (m_velocity.x != 0 && m_applyFriction)
	{
		addFriction(delta);
	}
	std::cout << "velocity, x: " << std::to_string(m_velocity.x) << " y: " << std::to_string(m_velocity.y) << "\n";
	m_parentTransformable.move(m_velocity * delta);
}

void VelocityComponent::addVelocity(const sf::Vector2f& velocity)
{
	m_velocity += velocity;

	trimVelocity();
}

void VelocityComponent::addFriction(float delta)
{
	float frictionAmount = m_friction * delta;

	if (frictionAmount >= std::abs(m_velocity.x))
	{
		m_velocity.x = 0;
		return;
	}

	int sign = m_velocity.x > 0 ? -1 : 1;
	addVelocity({frictionAmount * sign, 0});
}

void VelocityComponent::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;

	trimVelocity();
}

void VelocityComponent::setMaxVelocity(sf::Vector2f velocity)
{
	m_maxVelocity = velocity;

	trimVelocity();
}

void VelocityComponent::setSimulatePhysics(bool simulate)
{
	m_simulatePhysics = simulate;
}

void VelocityComponent::setGravity(float toGravity)
{
	m_gravity = toGravity;
}

void VelocityComponent::setFriction(float friction)
{
	m_friction = friction;
}

void VelocityComponent::setApplyFriction(bool addFriction)
{
	m_applyFriction = addFriction;
}

float VelocityComponent::getGravity() const
{
	return m_gravity;
}

bool VelocityComponent::isSimulatingPhysics() const
{
	return m_simulatePhysics;
}

const sf::Vector2f& VelocityComponent::getVelocity() const
{
	return m_velocity;
}

const sf::Vector2f& VelocityComponent::getMaxVelocity() const
{
	return m_maxVelocity;
}

void VelocityComponent::addGravity(float delta)
{
	m_velocity.y += m_gravity * delta;
}

void VelocityComponent::trimVelocity()
{
	if (m_maxVelocity.x != 0) {
		m_velocity.x = std::clamp(m_velocity.x, -m_maxVelocity.x, m_maxVelocity.x);
	}

	if (m_maxVelocity.y != 0) {
		m_velocity.y = std::clamp(m_velocity.y, -m_maxVelocity.y, m_maxVelocity.y);
	}
}
