#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(sf::Transformable& parentTransformable, sf::Vector2f maxVelocity, bool simulatePhysics) :
	m_parentTransformable(parentTransformable)
{
	SetMaxVelocity(maxVelocity);

	m_simulatePhysics = simulatePhysics;
}

void VelocityComponent::Process(float delta)
{
	if (m_simulatePhysics)
	{
		AddGravity();
	}
	m_parentTransformable.move(m_velocity * delta);
}

void VelocityComponent::AddVelocity(const sf::Vector2f& velocity)
{
	m_velocity += velocity;

	TrimVelocity();
}

void VelocityComponent::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;

	TrimVelocity();
}

void VelocityComponent::SetMaxVelocity(sf::Vector2f velocity)
{
	m_maxVelocity = velocity;

	TrimVelocity();
}

void VelocityComponent::SetSimulatePhysics(bool simulate)
{
	m_simulatePhysics = simulate;
}

void VelocityComponent::SetGravity(float toGravity)
{
	m_gravity = toGravity;
}

float VelocityComponent::GetGravity() const
{
	return m_gravity;
}

bool VelocityComponent::IsSimulatingPhysics() const
{
	return m_simulatePhysics;
}

const sf::Vector2f& VelocityComponent::GetVelocity() const
{
	return m_velocity;
}

const sf::Vector2f& VelocityComponent::GetMaxVelocity() const
{
	return m_maxVelocity;
}

void VelocityComponent::AddGravity()
{
	m_velocity.y += m_gravity;
}

void VelocityComponent::TrimVelocity()
{
	if (m_maxVelocity.x != 0 && m_velocity.x > m_maxVelocity.x)
	{
		m_velocity.x = m_maxVelocity.x;
	}
	else if (m_maxVelocity.x != 0 && m_velocity.x < -m_maxVelocity.x)
	{
		m_velocity.x = -m_maxVelocity.x;
	}

	if (m_maxVelocity.y == 0)
	{
		return;
	}
	
	if (m_velocity.y > m_maxVelocity.y)
	{
		m_velocity.y = m_maxVelocity.y;
	}
	else if (m_velocity.y < -m_maxVelocity.y)
	{
		m_velocity.y = -m_maxVelocity.y;
	}
}
