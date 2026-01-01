#include <SFML/Graphics.hpp>

#pragma once
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, unsigned int gap = 0);
    bool overlaps(sf::FloatRect entityBounds);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;

    std::vector<int> m_tilesId;
	sf::Vector2u m_tileSize;
	unsigned int m_width;
    unsigned int m_height;
};

