#include "Entity.h"
#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"

Entity::Entity(sf::Texture& texture) : m_sprite(texture)
{
	m_texture = &texture;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}