#include "Tilemap.h"
#include <iostream>

bool TileMap::load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, unsigned int gap)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_tileSize = tileSize;
    m_width    = width;
	m_height   = height;
    m_tilesId.resize(width * height);    

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(width * height * 6);

    int tilesPerRow = (m_tileset.getSize().x + gap) / (tileSize.x + gap);
    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            const int tileNumber = tiles[i + j * width];
            m_tilesId[i + j * width] = tileNumber;

            if (tileNumber == -1)
            {
                continue;
            }

            // find its position in the tileset texture
            const int tu = tileNumber % tilesPerRow;
            const int tv = tileNumber / tilesPerRow;

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            float left = tu * (tileSize.x + gap);
            float right = left + tileSize.x;
            float top = tv * (tileSize.y + gap);
            float bottom = top + tileSize.y;

            triangles[0].texCoords = sf::Vector2f(left, top);
            triangles[1].texCoords = sf::Vector2f(right, top);
            triangles[2].texCoords = sf::Vector2f(left, bottom);
            triangles[3].texCoords = sf::Vector2f(left, bottom);
            triangles[4].texCoords = sf::Vector2f(right, top);
            triangles[5].texCoords = sf::Vector2f(right, bottom);
        }
    }

    return true;
}

bool TileMap::overlaps(sf::FloatRect entityBounds)
{
    auto bounds = m_vertices.getBounds();    

    sf::FloatRect actualPosition = m_vertices.getBounds();
    actualPosition.position += getPosition();

    if (!actualPosition.contains(entityBounds.position))
    {        
        return false;
	}
    std::cout << "inside bounds" << "\n";
    
    sf::Vector2f entityPositionInsideGrid = entityBounds.position - getPosition();    
	int leftTile = static_cast<int>(entityPositionInsideGrid.x / m_tileSize.x);
    int topTile = static_cast<int>(entityPositionInsideGrid.y / m_tileSize.y);

    int rightTile = static_cast<int>((entityPositionInsideGrid.x + entityBounds.size.x - 0.1f) / m_tileSize.x);
    int bottomTile = static_cast<int>((entityPositionInsideGrid.y + entityBounds.size.y - 0.1f) / m_tileSize.y);

    leftTile = std::max(0, leftTile);
    rightTile = std::min(static_cast<int>(m_width) - 1, rightTile);
    topTile = std::max(0, topTile);
    bottomTile = std::min(static_cast<int>(m_height) - 1, bottomTile);

    for (int i = leftTile; i <= rightTile; ++i)
    {
        for (int j = topTile; j <= bottomTile; ++j)
        {
            int tileIndex = i + j * m_width;

            if (m_tilesId[tileIndex] != -1)
            {
                return true;
            }
        }
	}
    return false;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}