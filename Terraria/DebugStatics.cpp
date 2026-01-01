#include "DebugStatics.h"

void DebugStatics::createDebugRectangle(sf::FloatRect rect)
{
	debugVertex.setPrimitiveType(sf::PrimitiveType::Triangles);
	debugVertex.resize(debugVertex.getVertexCount() + 6);

	debugVertex[0].position = sf::Vector2f(rect.position.x, rect.position.y);
	debugVertex[1].position = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y);
	debugVertex[2].position = sf::Vector2f(rect.position.x, rect.position.y + rect.size.y);

	debugVertex[3].position = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y);
	debugVertex[4].position = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);
	debugVertex[5].position = sf::Vector2f(rect.position.x, rect.position.y + rect.size.y);

	debugVertex[0].color = sf::Color::Red;
	debugVertex[1].color = sf::Color::Red;
	debugVertex[2].color = sf::Color::Red;
	debugVertex[3].color = sf::Color::Red;
	debugVertex[4].color = sf::Color::Red;
	debugVertex[5].color = sf::Color::Red;
}

void DebugStatics::createDebugCircle(sf::FloatRect rect)
{
}

void DebugStatics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(debugVertex, states);
}

