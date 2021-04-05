#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace sf;
int main()
{
    Texture playerT;
    if (!playerT.loadFromFile("image.png"))
    {
        // error...
    }
    Sprite playerS;
    playerS.setTexture(playerT);
    playerS.setPosition(400,300);
    double playerXV = 0,playerYV = 0;
    RenderWindow window(VideoMode(800, 600), "My window");
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
