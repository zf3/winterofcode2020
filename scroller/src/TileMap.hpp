#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// 读取Tiled格式的CSV文件，成功的话返回true
// result是row-major的所有整数结果
bool loadTiledCsv(std::string f, std::vector<int> &result, int *width, int *height);

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int> &tiles, unsigned int width, unsigned int height);
	bool addLayer(const std::vector<int> &tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
	sf::Vector2u m_tileSize;
};