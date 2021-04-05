#include "TileMap.hpp"

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int> &tiles, unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset))
		return false;
	m_tileSize = tileSize;

	m_vertices.setPrimitiveType(sf::Quads);
	addLayer(tiles, width, height);

	return true;
}

bool TileMap::addLayer(const std::vector<int> &tiles, unsigned int width, unsigned int height) {
	// resize the vertex array to fit the level size
	sf::Vector2u tileSize = m_tileSize;

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * width];
			// 跳过所有空的tile
			if (tileNumber == -1)
				continue;

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			sf::Vertex q0, q1, q2, q3;
			// define its 4 corners
			q0.position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			q1.position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			q2.position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			q3.position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			q0.texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			q1.texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			q2.texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			q3.texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			m_vertices.append(q0);
			m_vertices.append(q1);
			m_vertices.append(q2);
			m_vertices.append(q3);
		}
	return true;
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
