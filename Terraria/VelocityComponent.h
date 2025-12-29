#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

#pragma once
class VelocityComponent
{
public:	
	VelocityComponent(sf::Transformable& parentTransformable, sf::Vector2f maxVelocity, bool simulatePhysics = true);
	void process(float delta);
	void addVelocity(const sf::Vector2f& velocity);
	void setVelocity(sf::Vector2f velocity);
	void setMaxVelocity(sf::Vector2f velocity);
	void setSimulatePhysics(bool simulate);
	void setGravity(float toGravity);
	void setFriction(float friction);
	void setApplyFriction(bool applyFriction);
	
	float getGravity() const;
	bool isSimulatingPhysics() const;
	const sf::Vector2f& getVelocity() const;	
	const sf::Vector2f& getMaxVelocity() const;

private:
	float m_gravity  = 3250.0f;
	float m_friction = 300.0f;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Transformable& m_parentTransformable;
	
	bool m_simulatePhysics = true;
	bool m_applyFriction = true;

	void addFriction(float delta);
	void addGravity(float delta);
	void trimVelocity();
};
