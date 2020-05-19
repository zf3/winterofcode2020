#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include "TileMap.hpp"
#include<math.h>

#define PI 3.14159265

using namespace sf;
using namespace std;

bool hitboxD (vector<int> csv, float mult, float x, float y, int width) {
    int a = floor(x/mult), b = ceil(x/mult), c = floor(y/mult), d = ceil(y/mult);
    if(csv[c*width+a] == 43) {
        return true;
    }
    if(csv[d*width+a] == 43) {
        return true;
    }
    if(csv[c*width+b] == 43) {
        return true;
    }
    if(csv[d*width+b] == 43) {
        return true;
    }
    return false;
}
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
struct weapon {
    int weaponType = 2, handleType = 1, barrelType = 1;
    float firerate = 1;
};
int main()
{
    int shotAmn = 0;
    weapon curr;
    bool isFiring = false;
    float speed = 0.5;
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
    int screenWidth = 1200, screenHeight = 1200;
    Clock clock;
    Clock clock2;
    bool keyStatus[4] = {false};
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Game window");

    View view(FloatRect(0.f, 0.f, 800.f, 800.f));
    window.setView(view);

    Texture texture;
    texture.loadFromFile("resources/PlayerChar1_Small.png", sf::IntRect(0, 0, 110, 230));
    texture.setSmooth(true);
    Texture texture2;
    texture2.loadFromFile("resources/PlayerChar2_Small.png", sf::IntRect(0, 0, 110, 150));
    texture2.setSmooth(true);
    Texture texture3;
    texture3.loadFromFile("resources/Force_Orb.png");
    Texture texture4;
    texture4.loadFromFile("resources/Plasma_Orb.png");
    Sprite player;
    if(curr.weaponType == 1) {
        player.setTexture(texture2);
        player.setOrigin(55, 95);
    }
    else if(curr.weaponType == 2) {
        player.setTexture(texture);
        player.setOrigin(55, 175);
    }
    player.setPosition(500,500);
    player.setScale(0.5,0.5);
    view.move(100,100);
    window.setView(view);

    vector<Sprite> shots;
    vector<float> speeds;
    vector<float> rots;
    vector<int> maxDur;
    vector<float> dur;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed) {
                isFiring = true;
            }
            if (event.type == Event::MouseButtonReleased) {
                isFiring = false;
            }
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
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            float mouseX = localPosition.x;
            float mouseY = localPosition.y;
            float direction = (atan2(mouseY-screenHeight/2, mouseX-screenWidth/2)/PI)*180+90;
            player.setRotation(direction);
        }
        Time time = clock.getElapsedTime();
        float deltaTime = time.asMilliseconds();
        Time time2 = clock2.getElapsedTime();
        float Timer = time2.asSeconds();
        if(Timer >= curr.firerate && isFiring == true) {
            if(curr.barrelType == 1) {
                shots.push_back(Sprite(texture3));
                speeds.push_back(1);
                maxDur.push_back(4000);
            }
            else if(curr.barrelType == 2) {
                shots.push_back(Sprite(texture4));
                speeds.push_back(0.1);
                maxDur.push_back(4000);
            }
            rots.push_back(player.getRotation());
            shots[shots.size()-1].getPosition();
            shots[shots.size()-1].setScale(0.05,0.05);
            shots[shots.size()-1].setPosition(player.getPosition().x,player.getPosition().y);
            dur.push_back(0);
            shotAmn++;
            clock2.restart();
            if(curr.handleType == 2) {
                isFiring = false;
            }
        }
        clock.restart();
        if(keyStatus[0] == true) {
            if(hitboxD(level0,32,player.getPosition().x, player.getPosition().y+deltaTime*speed,50) == false
            && hitboxD(level1,32,player.getPosition().x, player.getPosition().y+deltaTime*speed,50) == false
            && hitboxD(level2,32,player.getPosition().x, player.getPosition().y+deltaTime*speed,50) == false
            && hitboxD(level3,32,player.getPosition().x, player.getPosition().y+deltaTime*speed,50) == false
            && hitboxD(level4,32,player.getPosition().x, player.getPosition().y+deltaTime*speed,50) == false) {
                view.move(0,deltaTime*speed);
                window.setView(view);
                player.move(0,deltaTime*speed);
            }
        }
        if(keyStatus[1] == true) {
            if(hitboxD(level0,32,player.getPosition().x, player.getPosition().y-deltaTime*speed,50) == false
            && hitboxD(level1,32,player.getPosition().x, player.getPosition().y-deltaTime*speed,50) == false
            && hitboxD(level2,32,player.getPosition().x, player.getPosition().y-deltaTime*speed,50) == false
            && hitboxD(level3,32,player.getPosition().x, player.getPosition().y-deltaTime*speed,50) == false
            && hitboxD(level4,32,player.getPosition().x, player.getPosition().y-deltaTime*speed,50) == false) {
                view.move(0,-deltaTime*speed);
                window.setView(view);
                player.move(0,-deltaTime*speed);
            }
        }
        if(keyStatus[2] == true) {
            if(hitboxD(level0,32,player.getPosition().x-deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level1,32,player.getPosition().x-deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level2,32,player.getPosition().x-deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level3,32,player.getPosition().x-deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level4,32,player.getPosition().x-deltaTime*speed, player.getPosition().y,50) == false) {
                view.move(-deltaTime*speed,0);
                window.setView(view);
                player.move(-deltaTime*speed,0);
            }
        }
        if(keyStatus[3] == true) {
            if(hitboxD(level0,32,player.getPosition().x+deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level1,32,player.getPosition().x+deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level2,32,player.getPosition().x+deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level3,32,player.getPosition().x+deltaTime*speed, player.getPosition().y,50) == false
            && hitboxD(level4,32,player.getPosition().x+deltaTime*speed, player.getPosition().y,50) == false) {
                view.move(deltaTime*speed,0);
                window.setView(view);
                player.move(deltaTime*speed,0);
            }
        }
        for(int i = 0; i < shotAmn; i++) {
            if(dur[i] >= maxDur[i]) {
                shots.erase(shots.begin()+i);
                speeds.erase(speeds.begin()+i);
                rots.erase(rots.begin()+i);
                dur.erase(dur.begin()+i);
                maxDur.erase(maxDur.begin()+i);
                shotAmn--;
            }
            double a,b,c;
            a = rots[i]-90;
            b = sin (a*PI/180);
            c = cos (a*PI/180);
            shots[i].move(speeds[i]*deltaTime*c,speeds[i]*deltaTime*b);
            dur[i]+=deltaTime;
        }
        window.clear(Color::White);

        window.draw(map);
        for(int i = 0; i < shotAmn; i++) {
            window.draw(shots[i]);
        }
        window.draw(player);
        window.display();
    }

    return 0;
}