#include <array>
#include <unordered_map>
#include <unordered_set>
#include <SFML/System/Vector2.hpp>

struct Tile
{
	int id;
	sf::Vector2i position;
};

struct Chunk
{
	static const int CHUNK_SIZE = 16;
	sf::Vector2i gridPos;

	std::array<Tile, CHUNK_SIZE * CHUNK_SIZE> tiles;
};

struct Vector2iHash {
	std::size_t operator()(const sf::Vector2i& v) const {
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};

#pragma once
class GridManager
{
public:
	static const int TILE_SIZE = 16;

	GridManager();
	
	void loadChunksOnScreen(/*pass screen position/size as params*/ bool loadOnlyVisibleChunks = true);	

	std::vector<Tile*> getNearbyTiles(int x, int y);
	std::vector<Chunk*> getNearbyChunks(int x, int y);

private:
	std::unordered_map <sf::Vector2i, Chunk, Vector2iHash> m_chunks;
};

