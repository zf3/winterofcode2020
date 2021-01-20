#include<iostream>
#include<vector>
using namespace std;
//structs
struct basicChar {
    int spd;
    sf::Clock wCooldownClock;
    sf::Time wCooldownT;
    float wCooldownM;
    float wCooldown;
    float hp;
    float dmg;
    sf::Sprite body;
    sf::Sprite weapon;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarBack;
};
//classes
//functions
int main () {
    //window
    sf::RenderWindow window(sf::VideoMode(800,600),"game window",sf::Style::Default);
    //views
    sf::View gameView(sf::FloatRect(0,0,800,600));
    window.setView(gameView);
    //textures
    sf::Texture playerTexture;
    playerTexture.loadFromFile("resources/playerTexture.png");
    playerTexture.setSmooth(true);
    sf::Texture playerWeaponTexture;
    playerWeaponTexture.loadFromFile("resources/weaponTexture.png");
    playerWeaponTexture.setSmooth(true);
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("resources/enemyTexture.png");
    enemyTexture.setSmooth(true);
    sf::Texture enemyWeaponTexture;
    enemyWeaponTexture.loadFromFile("resources/enemyWeaponTexture.png");
    enemyWeaponTexture.setSmooth(true);
    //variables
    bool status[256];
    for(int i = 0; i < 256; i++) {
        status[i] = false;
    }
    bool mouseStatus = false;
    int enemyCount = 0;
    //fonts
    //texts
    //shapes
    sf::RectangleShape block(sf::Vector2f(100,100));
    block.setFillColor(sf::Color(0,0,0));
    block.setPosition(sf::Vector2f(100,100));
    //clocks
    sf::Clock deltaClock;
    //player presets
    basicChar player;
    player.body.setOrigin(sf::Vector2f(100,100));
    player.body.setPosition(sf::Vector2f(400,300));
    player.body.setTexture(playerTexture);
    player.weapon.setOrigin(sf::Vector2f(100,100));
    player.weapon.setPosition(sf::Vector2f(400,300));
    player.weapon.setTexture(playerWeaponTexture);
    player.spd = 100;
    player.wCooldownM = 1;
    player.hp = 100;
    player.dmg = 10;
    player.hpBar.setSize(sf::Vector2f(5,player.hp/2));
    player.hpBar.setFillColor(sf::Color(0,255,0));
    player.hpBar.setOrigin(sf::Vector2f(25,25));
    player.hpBar.setPosition(400,300);
    player.hpBarBack.setSize(sf::Vector2f(5,50));
    player.hpBarBack.setFillColor(sf::Color(255,255,255));
    player.hpBarBack.setOutlineThickness(5);
    player.hpBarBack.setOutlineColor(sf::Color(0,0,0));
    player.hpBarBack.setOrigin(sf::Vector2f(25,25));
    player.hpBarBack.setPosition(400,300);
    //enemy presets & definition template
    vector<basicChar> enemies;
    basicChar temp;
    temp.spd = 100;
    temp.wCooldown = 0;
    temp.wCooldownM = 1;
    temp.body.setTexture(enemyTexture);
    temp.weapon.setTexture(enemyWeaponTexture);
    temp.body.setPosition(sf::Vector2f(0,0));
    temp.weapon.setPosition(sf::Vector2f(0,0));
    temp.body.setOrigin(sf::Vector2f(100,100));
    temp.weapon.setOrigin(sf::Vector2f(100,100));
    temp.hp = 100;
    temp.dmg = 10;
    temp.hpBar.setSize(sf::Vector2f(5,temp.hp/2));
    temp.hpBar.setFillColor(sf::Color(255,0,0));
    temp.hpBar.setOrigin(sf::Vector2f(25,25));
    temp.hpBar.setPosition(0,0);
    temp.hpBarBack.setSize(sf::Vector2f(5,50));
    temp.hpBarBack.setFillColor(sf::Color(255,255,255));
    temp.hpBarBack.setOutlineThickness(5);
    temp.hpBarBack.setOutlineColor(sf::Color(0,0,0));
    temp.hpBarBack.setOrigin(sf::Vector2f(25,25));
    temp.hpBarBack.setPosition(0,0);
    enemies.push_back(temp);
    enemyCount++;
    //texture loading
    //font loading
    //main loop
    while (window.isOpen()) {
        sf::Event event;
        //event detection
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                mouseStatus = true;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseStatus = false;
            }
            if (event.type == sf::Event::KeyPressed) {
                status[event.key.code] = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                status[event.key.code] = false;
            }
        }
        //time
        sf::Time deltaTimeT = deltaClock.getElapsedTime();
        player.wCooldownT = player.wCooldownClock.getElapsedTime();
        float deltaTime = deltaTimeT.asSeconds();
        player.wCooldown = player.wCooldownT.asSeconds();
        for(int i = 0; i < enemyCount; i++) {
            enemies[i].wCooldownT = enemies[i].wCooldownClock.getElapsedTime();
            enemies[i].wCooldown = enemies[i].wCooldownT.asSeconds();
        }
        //rotation
        sf::Vector2i mP = sf::Mouse::getPosition(window);
        float ang = atan2(mP.y-300.0,mP.x-400.0)*180/3.1415;
        player.body.setRotation(ang);
        player.weapon.setRotation(ang);
        player.hpBar.setRotation(ang);
        player.hpBarBack.setRotation(ang);
        for(int i = 0; i < enemyCount; i++) {
            float xD = player.body.getPosition().x-enemies[i].body.getPosition().x;
            float yD = player.body.getPosition().y-enemies[i].body.getPosition().y;
            ang = atan2(yD,xD)*180/3.1415;
            enemies[i].body.setRotation(ang);
            enemies[i].weapon.setRotation(ang);
            enemies[i].hpBar.setRotation(ang);
            enemies[i].hpBarBack.setRotation(ang);
        }
        //movement
        deltaClock.restart();
        if(status[sf::Keyboard::A] == true) {
            player.body.move(sf::Vector2f(deltaTime*-player.spd,0));
            player.weapon.move(sf::Vector2f(deltaTime*-player.spd,0));
            player.hpBar.move(sf::Vector2f(deltaTime*-player.spd,0));
            player.hpBarBack.move(sf::Vector2f(deltaTime*-player.spd,0));
            gameView.move(sf::Vector2f(deltaTime*-player.spd,0));
            window.setView(gameView);
        }
        if(status[sf::Keyboard::D] == true) {
            player.body.move(sf::Vector2f(deltaTime*player.spd,0));
            player.weapon.move(sf::Vector2f(deltaTime*player.spd,0));
            player.hpBar.move(sf::Vector2f(deltaTime*player.spd,0));
            player.hpBarBack.move(sf::Vector2f(deltaTime*player.spd,0));
            gameView.move(sf::Vector2f(deltaTime*player.spd,0));
            window.setView(gameView);
        }
        if(status[sf::Keyboard::W] == true) {
            player.body.move(sf::Vector2f(0,deltaTime*-player.spd));
            player.weapon.move(sf::Vector2f(0,deltaTime*-player.spd));
            player.hpBar.move(sf::Vector2f(0,deltaTime*-player.spd));
            player.hpBarBack.move(sf::Vector2f(0,deltaTime*-player.spd));
            gameView.move(sf::Vector2f(0,deltaTime*-player.spd));
            window.setView(gameView);
        }
        if(status[sf::Keyboard::S] == true) {
            player.body.move(sf::Vector2f(0,deltaTime*player.spd));
            player.weapon.move(sf::Vector2f(0,deltaTime*player.spd));
            player.hpBar.move(sf::Vector2f(0,deltaTime*player.spd));
            player.hpBarBack.move(sf::Vector2f(0,deltaTime*player.spd));
            gameView.move(sf::Vector2f(0,deltaTime*player.spd));
            window.setView(gameView);
        }
        for(int i = 0; i < enemyCount; i++) {
            float xM = deltaTime*enemies[i].spd*cos(enemies[i].body.getRotation()/180*3.1415);
            float yM = deltaTime*enemies[i].spd*sin(enemies[i].body.getRotation()/180*3.1415);
            enemies[i].body.move(xM,yM);
            enemies[i].weapon.move(xM,yM);
            enemies[i].hpBar.move(xM,yM);
            enemies[i].hpBarBack.move(xM,yM);
        }
        //attacks
        if(mouseStatus == true && player.wCooldown >= player.wCooldownM) {
            cout << "whackity!" << endl;
            enemies[0].hp-=player.dmg;
            player.wCooldownClock.restart();
        }
        for(int i = 0; i < enemyCount; i++) {
            if(enemies[i].wCooldown >= enemies[i].wCooldownM) {
                float xD = (enemies[i].body.getPosition().x-player.body.getPosition().x);
                float yD = (enemies[i].body.getPosition().y-player.body.getPosition().y);
                if(sqrtf(xD*xD+yD*yD) <= 50) {
                    cout << "ouchity!" << endl;
                    player.hp-=enemies[i].dmg;
                    enemies[i].wCooldownClock.restart();
                }
            }
        }
        //hp bar setting
        player.hpBar.setSize(sf::Vector2f(5,player.hp/2));
        for(int i = 0; i < enemyCount; i++) {
            enemies[i].hpBar.setSize(sf::Vector2f(5,enemies[i].hp/2));
        }
        //drawing
        window.clear(sf::Color(255,255,255));
        for(int i = 0; i < enemyCount; i++) {
            window.draw(enemies[i].body);
            window.draw(enemies[i].weapon);
            window.draw(enemies[i].hpBarBack);
            window.draw(enemies[i].hpBar);
        }
        window.draw(player.body);
        window.draw(player.weapon);
        window.draw(player.hpBarBack);
        window.draw(player.hpBar);
        window.draw(block);

        window.display();
    }
    return 0;
}