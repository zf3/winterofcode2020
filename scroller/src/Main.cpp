
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

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


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // Define some constants
    const int gameWidth = 1400;
    const int gameHeight = 1400;
    // Key status
    bool UP=false,DOWN=false,LEFT=false,RIGHT=false;

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    View view(sf::FloatRect(0.f, 0.f, 600.f, 600.f));
    window.setView(view);

    // Load the sounds used in the game
    sf::SoundBuffer ballSoundBuffer;
    if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
        return EXIT_FAILURE;
    sf::Sound ballSound(ballSoundBuffer);

    // Load tilemap
    vector<int> level0, level1;
    int width, height;
    if (!loadTiledCsv("resources/map_Bottom Layer.csv", level0, &width, &height))
        return -1;
    if (!loadTiledCsv("resources/map_Top Layer.csv", level1, &width, &height))
        return -1;
    cout << "Levels loaded width=" << width << ", height=" << height << endl;
    TileMap map;
    if (!map.load("resources/RPG Nature Tileset.png", sf::Vector2u(32, 32), level0, width, height))
        return -1;
    if (!map.addLayer(level1, width, height))
        return -1;

    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
        return EXIT_FAILURE;

    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(30);
    message.setPosition(100.f, 150.f);
    message.setFillColor(sf::Color::White);
    message.setString("Use W A S D to move arround.");

    sf::Clock clock;
    float speed = 80.f;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

            // Move view, speed is pixels per second
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                bool pressed = event.type == sf::Event::KeyPressed;
                switch (event.key.code) {
                    case Keyboard::A:
                        LEFT = pressed;
                        break;
                    case Keyboard::W:
                        UP = pressed;
                        break;
                    case Keyboard::S:
                        DOWN = pressed;
                        break;
                    case Keyboard::D:
                        RIGHT = pressed;
                        break;
                    default:
                        break;
                }
            }
        }

        if (UP) {
            view.move(0, -deltaTime * speed);
            window.setView(view);
        }
        if (DOWN) {
            view.move(0, deltaTime * speed);
            window.setView(view);
        }
        if (LEFT) {
            view.move(-deltaTime * speed, 0);
            window.setView(view);
        }
        if (RIGHT) {
            view.move(deltaTime * speed, 0);
            window.setView(view);
        }

        // Clear the window
        window.clear(sf::Color(50, 200, 50));

        window.draw(map);

        // Draw the pause message
        window.draw(message);

        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
