#include <SFML/Graphics/Rect.hpp>

#pragma once
class CollisionComponent
{
public:
	static bool checkTileAABBCollision(const sf::FloatRect& a, const sf::FloatRect& b);
};

