#include<iostream>
#include<vector>
#include "basicChar.hpp"
#include "display.hpp"
#include "TileMap.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "inventorySlot.hpp"
#include "floorItem.hpp"
using namespace std;
//enum or constant definitions
const float PI = 3.1415;
//functions
int main () {
    //window
    int w = 2000, h = 1236, sx = 600, sy = 500;
    sf::RenderWindow window(sf::VideoMode(w,h),"game window",sf::Style::Default);
    //views
    sf::View gameView(sf::FloatRect(0,0,w,h));
    gameView.setCenter(sx,sy);
    window.setView(gameView);
    //variables
    bool status[256];
    for(int i = 0; i < 256; i++) {
        status[i] = false;
    }
    bool mouseStatus = false;
    bool mouseStatus2 = false;
    bool inventoryOn = false;
    int enemyCount = 0;
    int objs[1];
    float deltaTime;
    float pickupRange = 100;
    int lootChanceNumer = 2;
    int lootChanceDenom = 2;
    int currDescX = -1;
    int currDescY = -1;
    objs[0] = 3;
    //fonts
    //texts
    //shapes
    //clocks
    sf::Clock deltaClock;
    //player presets
    string arr[7] = {"resources/Weapon1/1b.png","resources/Weapon1/1c.png","resources/Weapon1/1d.png","resources/Weapon1/1e.png","resources/Weapon1/1d.png","resources/Weapon1/1c.png","resources/Weapon1/1b.png"};
    string arr2[20] = {"resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png"
    ,"resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png"
    ,"resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png"
    ,"resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png","resources/Weapon1/1Sa.png"};
    string arr3[3] = {"resources/Weapon2/2b.png","resources/Weapon2/2c.png","resources/Weapon2/2b.png"};
    string arr4[20] = {"resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png"
    ,"resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png"
    ,"resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png"
    ,"resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png","resources/Weapon2/2Sa.png"};
    string arr5[7] = {"resources/Weapon3/3b.png","resources/Weapon3/3c.png","resources/Weapon3/3d.png","resources/Weapon3/3e.png","resources/Weapon3/3d.png","resources/Weapon3/3c.png","resources/Weapon3/3b.png"};
    string arr6[20] = {"resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png"
    ,"resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png"
    ,"resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png"
    ,"resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png","resources/Weapon3/3Sa.png"};
    sf::Vector2f tipPos[7] = {{sf::Vector2f(263,44)},{sf::Vector2f(284,-11)},{sf::Vector2f(281,-52)},{sf::Vector2f(268,-105)},{sf::Vector2f(281,-52)},{sf::Vector2f(284,-11)},{sf::Vector2f(263,44)}};
    sf::Vector2f tipPos2[20] = {{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)}
    ,{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)}
    ,{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)}
    ,{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)},{sf::Vector2f(300,12)}};
    sf::Vector2f tipPos3[3] = {{sf::Vector2f(149,-75)},{sf::Vector2f(193,-62)},{sf::Vector2f(149,-75)}};
    sf::Vector2f tipPos4[20] = {{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,-215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)}
    ,{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)}
    ,{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,-215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)}
    ,{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)},{sf::Vector2f(-5,215)}};
    sf::Vector2f tipPos5[7] = {{sf::Vector2f(184,28)},{sf::Vector2f(200,65)},{sf::Vector2f(200,98)},{sf::Vector2f(192,140)},{sf::Vector2f(200,98)},{sf::Vector2f(200,65)},{sf::Vector2f(184,28)}};
    sf::Vector2f tipPos6[20] = {{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)}
    ,{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)}
    ,{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)}
    ,{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)},{sf::Vector2f(187,104)}};
    weapon sword("resources/Weapon1/1a.png","resources/Icons/W1.png","resources/FloorIcons/W1.png","resources/Descriptions/W1.png",arr,arr2,tipPos,tipPos2,7,20,1,0.5,5,10,50,0.5,1,500,0,275);
    weapon dagger("resources/Weapon2/2a.png","resources/Icons/W2.png","resources/FloorIcons/W2.png","resources/Descriptions/W2.png",arr3,arr4,tipPos3,tipPos4,3,20,1.25,0.25,2.5,2.5,25,0.25,1,750,0,190);
    weapon axe("resources/Weapon3/3a.png","resources/Icons/W3.png","resources/FloorIcons/W3.png","resources/Descriptions/W3.png",arr5,arr6,tipPos5,tipPos6,7,20,0.75,0.75,7.5,25,75,0.75,1,0,-360,200);
    armor plate("resources/Armor1/1a.png","resources/Armor1/1b.png","resources/Icons/A1.png","resources/FloorIcons/A1.png","resources/Descriptions/A1.png",0.75,125,75);
    armor chain("resources/Armor2/2a.png","resources/Armor2/2b.png","resources/Icons/A2.png","resources/FloorIcons/A2.png","resources/Descriptions/A2.png",1,100,75);
    armor leather("resources/Armor3/3a.png","resources/Armor3/3b.png","resources/Icons/A3.png","resources/FloorIcons/A3.png","resources/Descriptions/A3.png",1.25,75,75);
    display playerHUD("resources/Display/Display1.png","resources/Display/Display2.png","resources/Display/Display3.png","resources/Display/Display4.png",192,192,192,sx,sy,0.5);
    inventorySlot inventory[4][4];
    vector<floorItem> dropped;
    vector<sf::Sprite> droppedObjs;
    int droppedSize = 0;
    sf::Sprite iconRenders[4][4];
    sf::Sprite inventoryBackground;
    sf::Sprite temp1;
    sf::Texture inventoryBackgroundT;
    sf::Sprite shownDesc;
    inventoryBackgroundT.loadFromFile("resources/Icons/InventoryScreen.png");
    inventoryBackgroundT.setSmooth(true);
    inventoryBackground.setTexture(inventoryBackgroundT);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            iconRenders[i][j].setPosition(sf::Vector2f(20+j*220,20+i*220));
            iconRenders[i][j].setScale(232/314.0,232/314.0);
        }
    }
    sf::Texture temp10;
    inventory[0][0].include(dagger);
    iconRenders[0][0].setTexture(inventory[0][0].w.icon);
    inventory[0][2].include(axe);
    iconRenders[0][2].setTexture(inventory[0][2].w.icon);
    inventory[0][3].include(plate);
    iconRenders[0][3].setTexture(inventory[0][3].a.icon);
    inventory[0][1].include(leather);
    iconRenders[0][1].setTexture(inventory[0][1].a.icon);
    basicChar player(100,0,255,0,sx,sy);
    vector<basicChar> enemies;
    //enemy spawning (just for tests)
    basicChar temp(100,255,0,0,0,0);
    inventory[0][0].apply(&player);
    inventory[0][1].apply(&player);
    inventory[0][2].apply(&temp);
    inventory[0][3].apply(&temp);
    inventory[0][2].active = false;
    inventory[0][3].active = false;
    for(int i = 0; i < 1; i++) {
        temp.body.setPosition(i*-25,i*-25);
        temp.heldWeapon.setPosition(i*-25,i*-25);
        temp.hpBar.setPosition(i*-25,i*-25);
        temp.hpBarBack.setPosition(i*-25,i*-25);
        enemies.push_back(temp);
        enemyCount++;
    }
    //texture loading
    //font loading
    //map loading
    int tL = 16, tH = 8;
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 0, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 0, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 0, 0, 2, 2, 3, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    TileMap map;
    if (!map.load("resources/Tileset/Tileset.png", sf::Vector2u(150, 150), level, tL, tH))
        return -1;
    //main loop
    while (window.isOpen()) {
        sf::Event event;
        //event detection
        {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(inventoryOn == false) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                    mouseStatus = true;
                }
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left) {
                    mouseStatus = false;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right) {
                    mouseStatus2 = true;
                }
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right) {
                    mouseStatus2 = false;
                }
            }
            else {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right) {
                    int mX = sf::Mouse::getPosition(window).x;
                    int mY = sf::Mouse::getPosition(window).y;
                    if(mX%310 >= 77/2.0 && mY%310 >= 77/2.0 && mX/310 < 4 && mY/310 < 4) {
                        inventory[mY/310][mX/310].apply(&player);
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                    int mX = sf::Mouse::getPosition(window).x;
                    int mY = sf::Mouse::getPosition(window).y;
                    if(mX%310 >= 77/2.0 && mY%310 >= 77/2.0 && mX/310 < 4 && mY/310 < 4) {
                        //I flipped the directions here because the array storage has directions changed
                        currDescX = mY/310;
                        currDescY = mX/310;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::I) {
                    inventoryOn = !inventoryOn;
                    currDescX = -1;
                    currDescY = -1;
                }
                status[event.key.code] = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                status[event.key.code] = false;
            }
        }
        }
        //time
        {
        sf::Time deltaTimeT = deltaClock.getElapsedTime();
        player.wCooldownT = player.wCooldownClock.getElapsedTime();
        player.wCooldownT2 = player.wCooldownClock2.getElapsedTime();
        deltaTime = deltaTimeT.asSeconds();
        player.wCooldown = player.wCooldownT.asSeconds();
        player.wCooldown2 = player.wCooldownT2.asSeconds();
        for(int i = 0; i < enemyCount; i++) {
            enemies[i].wCooldownT = enemies[i].wCooldownClock.getElapsedTime();
            enemies[i].wCooldown = enemies[i].wCooldownT.asSeconds();
        }
        }
        //rotation
        {
        if(player.atkActive2 == false) {
            sf::Vector2i mP = sf::Mouse::getPosition(window);
            float ang = atan2(mP.y-h/2.0,mP.x-w/2.0)*180/PI;
            player.body.setRotation(ang);
            player.heldWeapon.setRotation(ang);
            player.hpBar.setRotation(ang);
            player.hpBarBack.setRotation(ang);
            for(int i = 0; i < enemyCount; i++) {
                float xD = player.body.getPosition().x-enemies[i].body.getPosition().x;
                float yD = player.body.getPosition().y-enemies[i].body.getPosition().y;
                ang = atan2(yD,xD)*180/PI;
                enemies[i].body.setRotation(ang);
                enemies[i].heldWeapon.setRotation(ang);
                enemies[i].hpBar.setRotation(ang);
                enemies[i].hpBarBack.setRotation(ang);
            }
        }
        }
        //keypress reactions
        {
        deltaClock.restart();
        if(player.atkActive2 == false) {
            if(status[sf::Keyboard::A] == true && player.objCollisions(deltaTime*-player.spd,0,level,tL,objs,1) == false) {
                player.move(deltaTime*-player.spd,0);
                playerHUD.move(deltaTime*-player.spd,0);
                gameView.move(sf::Vector2f(deltaTime*-player.spd,0));
                window.setView(gameView);
            }
            if(status[sf::Keyboard::D] == true && player.objCollisions(deltaTime*player.spd,0,level,tL,objs,1) == false) {
                player.move(deltaTime*player.spd,0);
                playerHUD.move(deltaTime*player.spd,0);
                gameView.move(sf::Vector2f(deltaTime*player.spd,0));
                window.setView(gameView);
            }
            if(status[sf::Keyboard::W] == true && player.objCollisions(0,deltaTime*-player.spd,level,tL,objs,1) == false) {
                player.move(0,deltaTime*-player.spd);
                playerHUD.move(0,deltaTime*-player.spd);
                gameView.move(sf::Vector2f(0,deltaTime*-player.spd));
                window.setView(gameView);
            }
            if(status[sf::Keyboard::S] == true && player.objCollisions(0,deltaTime*player.spd,level,tL,objs,1) == false) {
                player.move(0,deltaTime*player.spd);
                playerHUD.move(0,deltaTime*player.spd);
                gameView.move(sf::Vector2f(0,deltaTime*player.spd));
                window.setView(gameView);
            }
        }
        if(status[sf::Keyboard::F] == true) {
            for(int i = 0; i < droppedSize; i++) {
                float pX = player.body.getPosition().x;
                float pY = player.body.getPosition().y;
                if(sqrtf((pX-dropped[i].x)*(pX-dropped[i].x)+(pY-dropped[i].y)*(pY-dropped[i].y)) <= pickupRange) {
                    bool found = false;
                    for(int j = 0; j < 4; j++) {
                        for(int l = 0; l < 4; l++) {
                            if(inventory[j][l].active == false && found == false) {
                                dropped[i].apply(&inventory[j][l]);
                                sf::Texture temp2;
                                int used = inventory[j][l].type;
                                if(used == 1) {
                                    iconRenders[j][l].setTexture(dropped[i].w.icon);
                                }
                                else {
                                    iconRenders[j][l].setTexture(dropped[i].a.icon);
                                }
                                dropped.erase(dropped.begin()+i);
                                droppedObjs.erase(droppedObjs.begin()+i);
                                droppedSize--;
                                found = true;
                                break;
                            }
                        }
                        if(found) {
                            break;
                        }
                    }
                    if(found) {
                        break;
                    }
                }
            }
        }
        }
        //attacks
        {
        if(mouseStatus == true && player.atkActive2 == false && player.wCooldown >= player.wCooldownM) {
            player.atkActive = true;
            player.wCooldownClock.restart();
        }
        if(mouseStatus2 == true && player.atkActive == false && player.wCooldown2 >= player.wCooldownM2) {
            player.atkActive2 = true;
            player.wCooldownClock2.restart();
        }
        if(player.atkActive) {
            player.loadAnim(enemyCount, enemies);
        }
        if(player.atkActive2) {
            player.loadAnim2(enemyCount, enemies,deltaTime,&gameView,&window,level,tL,objs,1,&playerHUD);
        }
        }
        //enemy management
        {
        for(int i = 0; i < enemyCount; i++) {
            float xM = deltaTime*enemies[i].spd*cos(enemies[i].body.getRotation()/180*PI);
            float yM = deltaTime*enemies[i].spd*sin(enemies[i].body.getRotation()/180*PI);
            if(enemies[i].objCollisions(xM,0,level,tL,objs,1) == false) {
                enemies[i].body.move(xM,0);
                enemies[i].heldWeapon.move(xM,0);
                enemies[i].hpBar.move(xM,0);
                enemies[i].hpBarBack.move(xM,0);
            }
            if(enemies[i].objCollisions(0,yM,level,tL,objs,1) == false) {
                enemies[i].body.move(0,yM);
                enemies[i].heldWeapon.move(0,yM);
                enemies[i].hpBar.move(0,yM);
                enemies[i].hpBarBack.move(0,yM);
            }
            if(enemies[i].hp <= 0) {
                //checking if is miniboss/boss via hp bar
                if(enemies[i].maxHP > 50) {
                    int included = rand()%lootChanceDenom;
                    if(included <= lootChanceNumer-1) {
                        floorItem temp;
                        temp.include(&enemies[i], enemies[i].body.getPosition().x, enemies[i].body.getPosition().y);
                        dropped.push_back(temp);
                        sf::Sprite temp2;
                        droppedObjs.push_back(temp2);
                        if(temp.type == 1) {
                            droppedObjs[droppedSize].setTexture(enemies[i].fIconW);
                        }
                        if(temp.type == 2) {
                            droppedObjs[droppedSize].setTexture(enemies[i].fIconA);
                        }
                        droppedObjs[droppedSize].setScale(100/314.0,100/314.0);
                        droppedObjs[droppedSize].setOrigin(50,50);
                        droppedObjs[droppedSize].setPosition(sf::Vector2f(temp.x,temp.y));
                        droppedObjs[droppedSize].setRotation(rand()%360);
                        droppedSize++;
                    }
                }
                enemies.erase(enemies.begin()+i);
                enemyCount--;
                //respawning code (just for tests)
                temp.body.setPosition(0,0);
                temp.heldWeapon.setPosition(0,0);
                temp.hpBar.setPosition(0,0);
                temp.hpBarBack.setPosition(0,0);
                enemies.push_back(temp);
                enemyCount++;
            }
            if(enemies[i].wCooldown >= enemies[i].wCooldownM) {
                float xD = (enemies[i].body.getPosition().x-player.body.getPosition().x);
                float yD = (enemies[i].body.getPosition().y-player.body.getPosition().y);
                if(sqrtf(xD*xD+yD*yD) <= enemies[i].atkDist) {
                    enemies[i].atkActive = true;
                    enemies[i].wCooldownClock.restart();
                }
            }
            if(enemies[i].atkActive) {
                vector<basicChar> temp2;
                temp2.push_back(player);
                enemies[i].loadAnim(1,temp2);
                player.hp = temp2[0].hp;
                player.damaged = temp2[0].damaged;
                if(temp2[0].damaged == true) {
                    player.body.setTexture(player.bTexture2);
                }
                else {
                    player.body.setTexture(player.bTexture);
                }
            }
        }
        }
        //player respawning
        {
        if(player.hp <= 0) {
            player.body.setPosition(sx,sy);
            player.heldWeapon.setPosition(sx,sy);
            player.hp = player.maxHP;
            player.atkActive = false;
            player.atkAnimStage = 0;
            player.atkAnimStage2 = 0;
            playerHUD.display1.setPosition(sx-608,sy+309);
            playerHUD.display2.setPosition(sx-608,sy+309);
            playerHUD.display3.setPosition(sx-608,sy+309);
            playerHUD.display4.setPosition(sx-608,sy+309);
            playerHUD.block1.setPosition(sx-608+373/2,sy+309+264/2);
            playerHUD.block2.setPosition(sx-608+2048/2,sy+309+253/2);
            playerHUD.block3.setPosition(sx-608+983/2,sy+309+84/2);
            gameView.setCenter(sx,sy);
        }
        }
        //hp bar setting
        {
        for(int i = 0; i < enemyCount; i++) {
            enemies[i].hpBar.setSize(sf::Vector2f(5,50*enemies[i].hp/enemies[i].maxHP));
        }
        playerHUD.renew(player.wCooldown,player.wCooldownM,player.wCooldown2,player.wCooldownM2,player.hp,player.maxHP);
        }
        //drawing
        {
        if(inventoryOn == false) {
            window.clear(sf::Color(255,255,255));
            window.draw(map);
            for(int i = 0; i < droppedSize; i++) {
                if(dropped[i].active == true) {
                    window.draw(droppedObjs[i]);
                }
            }
            for(int i = 0; i < enemyCount; i++) {
                window.draw(enemies[i].heldWeapon);
                window.draw(enemies[i].body);
                window.draw(enemies[i].hpBarBack);
                window.draw(enemies[i].hpBar);
            }
            window.draw(player.heldWeapon);
            window.draw(player.body);
            window.draw(playerHUD.display2);
            window.draw(playerHUD.display3);
            window.draw(playerHUD.display4);
            window.draw(playerHUD.block1);
            window.draw(playerHUD.block2);
            window.draw(playerHUD.block3);
            window.draw(playerHUD.display1);
            temp1.setTexture(inventory[1][2].a.icon);
            window.draw(temp1);
        }
        if(inventoryOn == true) {
            window.clear(sf::Color(128,128,128));
            inventoryBackground.setPosition(sf::Vector2f(player.body.getPosition().x-w/2,player.body.getPosition().y-h/2));
            window.draw(inventoryBackground);
            if(currDescX > -1 && currDescY > -1) {
                shownDesc.setPosition(sf::Vector2f(player.body.getPosition().x-w/2+1276,player.body.getPosition().y-h/2+39));
                if(inventory[currDescX][currDescY].type == 1) {
                    shownDesc.setTexture(inventory[currDescX][currDescY].w.description);
                }
                else {
                    shownDesc.setTexture(inventory[currDescX][currDescY].a.description);
                }
                window.draw(shownDesc);
            }
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    iconRenders[i][j].setPosition(sf::Vector2f(player.body.getPosition().x+77/2.0+j*310-w/2,player.body.getPosition().y+77/2.0+i*310-h/2));
                    if(inventory[i][j].type == 1) {
                        iconRenders[i][j].setTexture(inventory[i][j].w.icon);
                    }
                    if(inventory[i][j].type == 2) {
                        iconRenders[i][j].setTexture(inventory[i][j].a.icon);
                    }
                    if(inventory[i][j].active) {
                        window.draw(iconRenders[i][j]);
                    }
                }
            }
        }
        window.display();
        }
    }
    return 0;
}