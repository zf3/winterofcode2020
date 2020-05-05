
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

bool prompt = true;
const int L = 1, R = 2, U = 3, D = 0;       // corresponding to lines in sprites
const int PER_FRAME = 20;       // distance to move before changing sprite frame
const int TOTAL_FRAMES = 3;

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
    int winWidth = 1400;
    int winHeight = 1400;
    float scale = 2.f;      // increase to magnify

    // Key status
    bool UP=false,DOWN=false,LEFT=false,RIGHT=false;
    float distance = 0.f;
    int direction = R;

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight, 32), "SFML Pong",
                            sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    View view(sf::FloatRect(0.f, 0.f, winWidth / scale, winHeight / scale));
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

    // Init our character
    Texture t;
    if (!t.loadFromFile("resources/Pipoya/Female/Female 01-1.png"))
        return -1;
    Sprite character;
    character.setTexture(t);
    character.setTextureRect(IntRect(0, 64, 32, 32));

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

            if (event.type == sf::Event::Resized) {
                cout << "Resized" << endl;
                Vector2u s = window.getSize();
                view.setSize(s.x / scale, s.y / scale);
                window.setView(view);
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

        float tomove = deltaTime * speed;
        int frame = 0;
        if (UP || DOWN || LEFT || RIGHT) {
            // We are walking
            prompt = false;
            int newDirection = R;
            if (UP)
                newDirection = U;
            else if (DOWN)
                newDirection = D;
            if (RIGHT)
                newDirection = R;
            else if (LEFT)
                newDirection = L;
            distance += tomove;
            if (direction != newDirection) {
                direction = newDirection;
                distance = 0.f;
            }
            frame = (int)distance / PER_FRAME % TOTAL_FRAMES;
            cout << "direction=" << direction << ", frame=" << frame << endl;
            character.setTextureRect(IntRect(32 * frame, 32 * direction, 32, 32));
        }
        if (UP) {
            view.move(0, -tomove);
            window.setView(view);
        }
        if (DOWN) {
            view.move(0, tomove);
            window.setView(view);
        }
        if (LEFT) {
            view.move(-tomove, 0);
            window.setView(view);
        }
        if (RIGHT) {
            view.move(tomove, 0);
            window.setView(view);
        }

        // Clear the window
        window.clear(sf::Color(50, 200, 50));

        window.draw(map);

        character.setPosition(view.getCenter());
        window.draw(character);

        // Draw the pause message
        if (prompt)
            window.draw(message);

        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
