#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>

#pragma once
class DebugStatics : public sf::Drawable
{
public:
	void createDebugRectangle(sf::FloatRect rect);
	void createDebugRectangle(sf::FloatRect rect, float lifetime);
	void createDebugCircle(sf::FloatRect rect);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray debugVertex;
};
