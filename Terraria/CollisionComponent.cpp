#include "CollisionComponent.h"

bool CollisionComponent::checkTileAABBCollision(const sf::FloatRect& a, const sf::FloatRect& b)
{
    auto overlap = a.findIntersection(b);
	return overlap.has_value();
}
