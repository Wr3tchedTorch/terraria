#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

#pragma once
class VelocityComponent
{
public:	
	VelocityComponent(sf::Transformable& parentTransformable, sf::Vector2f maxVelocity, bool simulatePhysics = true);
	void Process(float delta);
	void AddVelocity(const sf::Vector2f& velocity);
	void SetVelocity(sf::Vector2f velocity);
	void SetMaxVelocity(sf::Vector2f velocity);
	void SetSimulatePhysics(bool simulate);
	void SetGravity(float toGravity);
	
	float GetGravity() const;
	bool IsSimulatingPhysics() const;
	const sf::Vector2f& GetVelocity() const;	
	const sf::Vector2f& GetMaxVelocity() const;

private:
	float m_gravity = .8f;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Transformable& m_parentTransformable;
	
	bool m_simulatePhysics = true;
	void AddGravity();
	void TrimVelocity();
};
