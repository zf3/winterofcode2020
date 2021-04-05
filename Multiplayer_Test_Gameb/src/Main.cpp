#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include<vector>
#include<cmath>

#define PI 3.14159265

using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode(2400, 1800), "Test window");
    while(window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    }
    return 0;
}
