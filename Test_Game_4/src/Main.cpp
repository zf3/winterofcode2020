#include<iostream>
#include<vector>
using namespace std;
//classes
const float PI = 3.1415;
class basicChar {
    public:
    int spd;
    int atkAnimStage;
    int hitbox;
    bool atkActive;
    sf::Clock wCooldownClock;
    sf::Clock animClock;
    sf::Time wCooldownT;
    sf::Time animTime;
    float wCooldownM;
    float wCooldown;
    float hp;
    float dmg;
    float atkD;
    float atkS;
    sf::Sprite body;
    sf::Sprite weapon;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarBack;
    sf::Texture bTexture;
    sf::Texture wTexture;
    //animation cycles; work in progress
    void basicCollisionDetection (basicChar *target, sf::Vector2f *tipPos) {
        float bx = body.getPosition().x, by = body.getPosition().y;
        float br = body.getRotation()/180*PI;
        float tx = target->body.getPosition().x, ty = target->body.getPosition().y;
        float wx = bx+cos(br)*tipPos[atkAnimStage].x, wy = by+sin(br)*tipPos[atkAnimStage].y;
        if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= hitbox) {
            target->hp-=dmg;
        }
    }
    void loadAnim(sf::Texture *atkTextures, int n, int enemyCount, vector<basicChar> &enemies, sf::Vector2f *tipPos) {
        animTime = animClock.getElapsedTime();
        //printf("1\n");
        if(animTime.asSeconds() >= atkD/n && atkAnimStage < n) {
            animClock.restart();
            weapon.setTexture(*(atkTextures+atkAnimStage));
            atkAnimStage++;
            for(int i = 0; i < enemyCount; i++) {
                basicCollisionDetection(&enemies[i], tipPos);
            }
        }
        else if(animTime.asSeconds() >= atkD/n && atkAnimStage >= n) {
            weapon.setTexture(wTexture);
            atkAnimStage = 0;
            atkActive = false;
            weapon.setOrigin(200,200);
        }
    }
    //constructor
    basicChar (string a, string b, int re,int gr,int bl,int x,int y) {
        bTexture.loadFromFile(a);
        bTexture.setSmooth(true);
        wTexture.loadFromFile(b);
        wTexture.setSmooth(true);
        body.setOrigin(sf::Vector2f(200,200));
        body.setPosition(sf::Vector2f(x,y));
        body.setTexture(bTexture);
        weapon.setOrigin(sf::Vector2f(200,200));
        weapon.setPosition(sf::Vector2f(x,y));
        weapon.setTexture(wTexture);
        hitbox = 50;
        spd = 100;
        wCooldownM = 0.5;
        hp = 100;
        dmg = 10;
        atkActive = false;
        atkAnimStage = 0;
        atkD = 0.5;
        hpBar.setSize(sf::Vector2f(5,hp/2));
        hpBar.setFillColor(sf::Color(re,gr,bl));
        hpBar.setOrigin(sf::Vector2f(25,25));
        hpBar.setPosition(x,y);
        hpBarBack.setSize(sf::Vector2f(5,50));
        hpBarBack.setFillColor(sf::Color(255,255,255));
        hpBarBack.setOutlineThickness(5);
        hpBarBack.setOutlineColor(sf::Color(0,0,0));
        hpBarBack.setOrigin(sf::Vector2f(25,25));
        hpBarBack.setPosition(x,y);
    }
};
//functions
int main () {
    //window
    sf::RenderWindow window(sf::VideoMode(800,600),"game window",sf::Style::Default);
    //views
    sf::View gameView(sf::FloatRect(0,0,800,600));
    window.setView(gameView);
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
    basicChar player("resources/playerTexture.png","resources/weaponTexture.png",0,255,0,400,300);
    vector<basicChar> enemies;
    //enemy spawning (just for tests)
    // for(int i = 0; i < 10; i++) {
    //     temp.body.setPosition(i*-25,i*-25);
    //     temp.weapon.setPosition(i*-25,i*-25);
    //     temp.hpBar.setPosition(i*-25,i*-25);
    //     temp.hpBarBack.setPosition(i*-25,i*-25);
    //     enemies.push_back(temp);
    //     enemyCount++;
    // }
    //texture loading
    sf::Texture anims[5];
    anims[0].loadFromFile("resources/weaponTexture2.png");
    anims[1].loadFromFile("resources/weaponTexture3.png");
    anims[2].loadFromFile("resources/weaponTexture2.png");
    sf::Vector2f tipPos[3] = {{sf::Vector2f(111,2)},{sf::Vector2f(106,65)},{sf::Vector2f(111,2)}};
    sf::Texture enemyAnims[3];
    enemyAnims[0].loadFromFile("resources/enemyWeaponTexture2.png");
    enemyAnims[1].loadFromFile("resources/enemyWeaponTexture3.png");
    enemyAnims[2].loadFromFile("resources/enemyWeaponTexture2.png");
    sf::Vector2f enemyTipPos[3] = {{sf::Vector2f(111,2)},{sf::Vector2f(106,65)},{sf::Vector2f(111,2)}};
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
        float ang = atan2(mP.y-300.0,mP.x-400.0)*180/PI;
        player.body.setRotation(ang);
        player.weapon.setRotation(ang);
        player.hpBar.setRotation(ang);
        player.hpBarBack.setRotation(ang);
        for(int i = 0; i < enemyCount; i++) {
            float xD = player.body.getPosition().x-enemies[i].body.getPosition().x;
            float yD = player.body.getPosition().y-enemies[i].body.getPosition().y;
            ang = atan2(yD,xD)*180/PI;
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
            float xM = deltaTime*enemies[i].spd*cos(enemies[i].body.getRotation()/180*PI);
            float yM = deltaTime*enemies[i].spd*sin(enemies[i].body.getRotation()/180*PI);
            enemies[i].body.move(xM,yM);
            enemies[i].weapon.move(xM,yM);
            enemies[i].hpBar.move(xM,yM);
            enemies[i].hpBarBack.move(xM,yM);
        }
        //attacks
        if(mouseStatus == true && player.wCooldown >= player.wCooldownM) {
            player.atkActive = true;
            player.wCooldownClock.restart();
        }
        if(player.atkActive) {
            player.loadAnim(anims,3, enemyCount, enemies, tipPos);
        }
        //enemy management
        for(int i = 0; i < enemyCount; i++) {
            if(enemies[i].hp <= 0) {
                enemies.erase(enemies.begin()+i);
                enemyCount--;
                //respawning code (just for tests)
                // temp.body.setPosition(0,0);
                // temp.weapon.setPosition(0,0);
                // temp.hpBar.setPosition(0,0);
                // temp.hpBarBack.setPosition(0,0);
                // enemies.push_back(temp);
                // enemyCount++;
            }
            if(enemies[i].wCooldown >= enemies[i].wCooldownM) {
                float xD = (enemies[i].body.getPosition().x-player.body.getPosition().x);
                float yD = (enemies[i].body.getPosition().y-player.body.getPosition().y);
                if(sqrtf(xD*xD+yD*yD) <= 125) {
                    enemies[i].atkActive = true;
                    enemies[i].wCooldownClock.restart();
                }
            }
            if(enemies[i].atkActive) {
                vector<basicChar> temp2;
                temp2.push_back(player);
                enemies[i].loadAnim(enemyAnims,3,1,temp2,enemyTipPos);
                player.hp = temp2[0].hp;
            }
        }
        //player respawning
        if(player.hp <= 0) {
            player.body.setPosition(400,300);
            player.weapon.setPosition(400,300);
            player.hp = 100;
            player.atkActive = false;
            player.atkAnimStage = 0;
            player.hpBar.setPosition(400,300);
            player.hpBarBack.setPosition(400,300);
            gameView.setCenter(400,300);
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