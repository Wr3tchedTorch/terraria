#include "SFML/Graphics/Sprite.hpp"

namespace sf {
	class Texture;
}

#pragma once
class Entity : public sf::Transformable, public sf::Drawable
{
public:
	Entity(sf::Texture& texture);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Sprite m_sprite;

private:
	sf::Texture* m_texture;
};
