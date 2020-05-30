#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include "TileMap.hpp"
#include<math.h>
#include <stdlib.h>

#define PI 3.14159265

using namespace sf;
using namespace std;

//player-object collision detection
bool hitboxD (vector<int> csv, float mult, float x, float y, int width, int targ) {
    int a = floor(x/mult), b = ceil(x/mult), c = floor(y/mult), d = ceil(y/mult);
    if(csv[c*width+a] == targ) {
        return true;
    }
    if(csv[d*width+a] == targ) {
        return true;
    }
    if(csv[c*width+b] == targ) {
        return true;
    }
    if(csv[d*width+b] == targ) {
        return true;
    }
    return false;
}
//shot-object collision detection
bool hitboxD2(vector<int> csv, float mult, float x, float y, int width, int targ) {
    int a = x/mult, b = y/mult;
    if(csv[b*width+a] == targ) {
        return true;
    }
    return false;
}
//tilemap operations function
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
//struct initialization
struct handle {
	float accuracy = 10, weight = 10, type;
};
struct barrel {
	float damage = 10, energyUsage = 10, type, weight = 10;
};
struct scope {
	float range = 1000,weight = 10, type;
};
struct aimer {
	float accuracy = 10, energyUsage = 10, weight = 10, damage = 5, type;
};
struct output {
	float reloadTime = 2, energyOutput = 20, weight = 10, maxEnergy = 100;
};
struct pistol {
	handle h;
	barrel b;
	output o;
	bool isFiring = false, isReloading = false;
    float weight = h.weight+b.weight+o.weight, energyUsage = b.energyUsage,
    damageM = b.damage, accuracy = h.accuracy, maxEnergy = o.maxEnergy, energy = maxEnergy,
    energyOutput = o.energyOutput, reloadTime = o.reloadTime, firerate = energyUsage/energyOutput;
};
struct rifle {
	handle h;
	barrel b;
	output o;
	aimer a;
	scope s;
	bool isFiring = false, isReloading = false;
    float weight = h.weight+b.weight+o.weight+a.weight+s.weight, energyUsage = a.energyUsage+b.energyUsage,
    damageM = a.damage+b.damage, accuracy = h.accuracy+a.accuracy, maxEnergy = o.maxEnergy, energy = maxEnergy,
    energyOutput = o.energyOutput, reloadTime = o.reloadTime, firerate = energyUsage/energyOutput;
};
struct shot {
	Sprite s;
	float dur, speed, rotation;
	int maxDur, type;
};
int main () {
	//variable definitions
	int screenWidth = 1200, screenHeight = 1200,holding = 1, shotAmn = 0;
    rifle primary;
    pistol secondary;
    vector<int> level0, level1;
    vector<shot> shots;
	bool keyStatus[4] = {false};
    int width, height;
    float playerSpeed = 2, deltaTime;
	//texture downloads
    Texture playerT1;
    playerT1.loadFromFile("resources/PlayerChar1_Small.png", sf::IntRect(0, 0, 110, 230));
    playerT1.setSmooth(true);
    Texture playerT2;
    playerT2.loadFromFile("resources/PlayerChar2_Small.png", sf::IntRect(0, 0, 110, 150));
    playerT2.setSmooth(true);
    Texture shotT1;
    shotT1.loadFromFile("resources/Force_Orb.png");
    Texture shotT2;
    shotT2.loadFromFile("resources/Plasma_Orb.png");
    Texture shotT3;
    shotT3.loadFromFile("resources/Pulse-Impact.png");
	//tilemap operations
    if (!loadTiledCsv("resources/TileMap2_Tile Layer 1.csv", level0, &width, &height))
        return -1;
    if (!loadTiledCsv("resources/TileMap2_Tile Layer 2.csv", level1, &width, &height))
        return -1;
    TileMap map;
    if (!map.load("resources/RPG Nature Tileset.png", sf::Vector2u(32, 32), level0, width, height))
        return -1;
    if (!map.addLayer(level1, width, height))
        return -1;
	//window and view initialization
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Game window");
	View view(FloatRect(0.f, 0.f, 800.f, 800.f));
    window.setView(view);
	//clock initialization
	Clock clock;
	Clock clock2;
	Clock clock3;
	//player initialization
	Sprite player;
    if(holding == 2) {
        player.setTexture(playerT2);
        player.setOrigin(55, 95);
    }
    else if(holding == 1) {
        player.setTexture(playerT1);
        player.setOrigin(55, 175);
    }
    player.setPosition(400,400);
    player.setScale(0.5,0.5);
    //reload bar initialization
    sf::RectangleShape barBack(sf::Vector2f(50,10));
    barBack.setFillColor(sf::Color(255, 255, 255));
    barBack.setOutlineThickness(2.f);
    barBack.setOutlineColor(sf::Color(0, 0, 0));
    barBack.setPosition(375,350);
    sf::RectangleShape bar(sf::Vector2f(0,6));
    bar.setFillColor(sf::Color(0, 192, 0));
    bar.setPosition(377,352);
    //main game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            //event reactions
            if (event.type == Event::MouseButtonPressed) {
                if(holding == 1) {
                    primary.isFiring = true;
                }
                if(holding == 2) {
                    secondary.isFiring = true;
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                if(holding == 1) {
                    primary.isFiring = false;
                }
                if(holding == 2) {
                    secondary.isFiring = false;
                }
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
                if (event.key.code == sf::Keyboard::R)
                {
                    if(holding == 1) {
                        primary.isReloading = true;
                    }
                    if(holding == 2) {
                        secondary.isReloading = true;
                    }
                    clock3.restart();
                }
                if (event.key.code == sf::Keyboard::Num1) {
                    holding = 1;
                    player.setTexture(playerT1);
                    player.setOrigin(55, 175);
                    secondary.isFiring = false;
                    secondary.isReloading = false;
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    holding = 2;
                    player.setTexture(playerT2);
                    player.setOrigin(55, 95);
                    primary.isFiring = false;
                    primary.isReloading = false;
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
        //player direction
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        float mouseX = localPosition.x;
        float mouseY = localPosition.y;
        float direction = (atan2(mouseY-screenHeight/2, mouseX-screenWidth/2)/PI)*180+90;
        player.setRotation(direction);
        //Timer setting
        Time time = clock.getElapsedTime();
        deltaTime = time.asMilliseconds();
        Time time2 = clock2.getElapsedTime();
        float Timer = time2.asSeconds();
        Time time3 = clock3.getElapsedTime();
        float Timer2 = time3.asSeconds();
        clock.restart();
        //bar length
        if(holding == 1) {
            bar.setSize(sf::Vector2f(46*Timer2/primary.reloadTime,6));
        }
        if(holding == 2) {
            bar.setSize(sf::Vector2f(46*Timer2/secondary.reloadTime,6));
        }
        //reloading
        if(holding == 1 && primary.isReloading == true && Timer2 >= primary.reloadTime) {
            primary.energy = primary.maxEnergy;
            primary.isReloading = false;
            clock3.restart();
        }
        if(holding == 2 && secondary.isReloading == true && Timer2 >= secondary.reloadTime) {
            secondary.energy = secondary.maxEnergy;
            secondary.isReloading = false;
            clock3.restart();
        }
        //S movement
        if(keyStatus[0] == true) {
            if(hitboxD(level0,32,player.getPosition().x-16, player.getPosition().y+deltaTime*playerSpeed-16,50,43) == false) {
                view.move(0,deltaTime*playerSpeed);
                window.setView(view);
                player.move(0,deltaTime*playerSpeed);
                bar.move(0,deltaTime*playerSpeed);
                barBack.move(0,deltaTime*playerSpeed);
            }
        }
        //W movement
        if(keyStatus[1] == true) {
            if(hitboxD(level0,32,player.getPosition().x-16, player.getPosition().y-deltaTime*playerSpeed-16,50,43) == false) {
                view.move(0,-deltaTime*playerSpeed);
                window.setView(view);
                player.move(0,-deltaTime*playerSpeed);
                bar.move(0,-deltaTime*playerSpeed);
                barBack.move(0,-deltaTime*playerSpeed);
            }
        }
        //A movement
        if(keyStatus[2] == true) {
            if(hitboxD(level0,32,player.getPosition().x-deltaTime*playerSpeed-16, player.getPosition().y-16,50,43) == false) {
                view.move(-deltaTime*playerSpeed,0);
                window.setView(view);
                player.move(-deltaTime*playerSpeed,0);
                bar.move(-deltaTime*playerSpeed,0);
                barBack.move(-deltaTime*playerSpeed,0);
            }
        }
        //D movement
        if(keyStatus[3] == true) {
            if(hitboxD(level0,32,player.getPosition().x+deltaTime*playerSpeed-16, player.getPosition().y-16,50,43) == false) {
                view.move(deltaTime*playerSpeed,0);
                window.setView(view);
                player.move(deltaTime*playerSpeed,0);
                bar.move(deltaTime*playerSpeed,0);
                barBack.move(deltaTime*playerSpeed,0);
            }
        }
        //shooting
        if(holding == 1 && primary.isFiring == true && Timer >= primary.firerate && primary.energy-primary.energyUsage >= 0 && primary.isReloading == false) {
            primary.energy-=primary.energyUsage;
            shot temp;
            int range = 21-primary.accuracy;
            int rc = rand() % range;
            float trc = rc/2.0;
            float tr = range/4.0;
            temp.s.setTexture(shotT1);
            temp.s.setPosition(player.getPosition().x,player.getPosition().y);
            temp.s.setRotation(player.getRotation()+tr-trc);
            temp.s.setScale(0.05,0.05);
            temp.dur = 0;
            temp.rotation = player.getRotation()+tr-trc;
            temp.maxDur = 10000;
            temp.speed = 10;
            temp.type = 1;
            shotAmn++;
            shots.push_back(temp);
            clock2.restart();
        }
        if(holding == 2 && secondary.isFiring == true && Timer >= secondary.firerate && secondary.energy-secondary.energyUsage >= 0 && secondary.isReloading == false) {
            secondary.energy-=secondary.energyUsage;
            shot temp;
            int range = 21-secondary.accuracy;
            int rc = rand() % range;
            float trc = rc/2.0;
            float tr = range/4.0;
            temp.s.setTexture(shotT1);
            temp.s.setPosition(player.getPosition().x,player.getPosition().y);
            temp.s.setRotation(player.getRotation()+tr-trc);
            temp.s.setScale(0.05,0.05);
            temp.dur = 0;
            temp.rotation = player.getRotation()+tr-trc;
            temp.maxDur = 10000;
            temp.speed = 10;
            temp.type = 1;
            shotAmn++;
            shots.push_back(temp);
            clock2.restart();
        }
        for(int i = 0; i < shotAmn; i++) {
            shots[i].dur+=deltaTime;
            if(shots[i].dur>= shots[i].maxDur || hitboxD2(level0,32,shots[i].s.getPosition().x,shots[i].s.getPosition().y,50,43) == true) {
                shots.erase(shots.begin()+i);
                shotAmn--;
            }
            shots[i].s.move(shots[i].speed*deltaTime*cos ((shots[i].rotation-90)*PI/180),shots[i].speed*deltaTime*sin ((shots[i].rotation-90)*PI/180));
        }
        //clear
        window.clear(Color::White);
        //draw map
        window.draw(map);
        //draw player
        window.draw(player);
        //draw shots
        for(int i = 0; i < shotAmn; i++) {
            window.draw(shots[i].s);
        }
        //draw reload bar
        if(primary.isReloading == true || secondary.isReloading) {
            window.draw(barBack);
            window.draw(bar);
        }
        //display
        window.display();
    }
}