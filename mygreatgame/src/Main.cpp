#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include "TileMap.hpp"

using namespace sf;
using namespace std;

// 读取Tiled格式的CSV文件，成功的话返回true
// result是row-major的所有整数结果
bool loadTiledCsv(string f, vector<int> &result, int *width, int *height) {
    ifstream file(f);
    if (!file) {
        cout << "Cannot open file " << f << endl;
        return false;
    }
    std::string line = "";
    *width = -1;
    *height = 0;
    // Iterate through each line and split the content using delimeter
    while (getline(file, line)) {
        std::string token;
        size_t pos;
        while (line.length() > 0) {
            pos = line.find(",");
            if (pos == string::npos)
                pos = line.length();
            token = line.substr(0, pos);
            result.push_back(stoi(token));
            line.erase(0, pos + 1);
        }
        if (*width == -1)
            *width = result.size();
        (*height) ++;
    }
    // Close the File
    file.close();
    return true;
}

int main()
{
    vector<int> level0, level1, level2, level3, level4;
    int width, height;
    if (!loadTiledCsv("resources/testmap_Tile Layer 1.csv", level0, &width, &height))
        return -1;
    if (!loadTiledCsv("resources/testmap_Tile Layer 2.csv", level1, &width, &height))
        return -1;
    if (!loadTiledCsv("resources/testmap_Tile Layer 3.csv", level2, &width, &height))
        return -1;
    if (!loadTiledCsv("resources/testmap_Tile Layer 4.csv", level3, &width, &height))
        return -1;
    if (!loadTiledCsv("resources/testmap_Tile Layer 5.csv", level4, &width, &height))
        return -1;
    TileMap map;
    if (!map.load("resources/RPG Nature Tileset.png", sf::Vector2u(32, 32), level0, width, height))
        return -1;
    if (!map.addLayer(level1, width, height))
        return -1;
    if (!map.addLayer(level2, width, height))
        return -1;
    if (!map.addLayer(level3, width, height))
        return -1;
    if (!map.addLayer(level4, width, height))
        return -1;
    int screenWidth = 800, screenHeight = 600;
    int tileWidth = 1000, tileHeight = 1000;
    float playerX = 0, playerY = 0;
    sf::Clock clock;
    bool keyStatus[4] = {false};
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Test window");

    View view(FloatRect(0.f, 0.f, 800.f, 600.f));
    window.setView(view);

    int spriteX = 0, spriteY = 0;
    Texture texture;
    texture.loadFromFile("resources/Desert_1.png");
    Sprite bg;
    bg.setTextureRect(IntRect(0, 0, tileWidth, tileHeight));
    bg.setTexture(texture);
    bg.move(spriteX,spriteY);
    float speed = 2;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S)
                {
                    keyStatus[0] = true;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    keyStatus[1] = true;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    keyStatus[2] = true;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    keyStatus[3] = true;
                }
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::S)
                {
                    keyStatus[0] = false;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    keyStatus[1] = false;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    keyStatus[2] = false;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    keyStatus[3] = false;
                }
            }
        }
        Time time = clock.getElapsedTime();
        float deltaTime = time.asMilliseconds();
        clock.restart();
        if(keyStatus[0] == true) {
            view.move(0,deltaTime*speed);
            window.setView(view);
            playerY+=deltaTime*speed;
        }
        if(keyStatus[1] == true) {
            view.move(0,-deltaTime*speed);
            window.setView(view);
            playerY-=deltaTime*speed;
        }
        if(keyStatus[2] == true) {
            view.move(-deltaTime*speed,0);
            window.setView(view);
            playerX-=deltaTime*speed;
        }
        if(keyStatus[3] == true) {
            view.move(deltaTime*speed,0);
            window.setView(view);
            playerX+=deltaTime*speed;
        }
        window.clear(Color::White);

        window.draw(map);

        // if(playerX >= -screenWidth+spriteX &&
        //     playerY >= -screenHeight+spriteY &&
        //     playerX+spriteX <= screenWidth+tileWidth &&
        //     playerY <= screenHeight+tileHeight+spriteY) {
        //     window.draw(bg);
        // }

        window.display();
    }

    return 0;
}