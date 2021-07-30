#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <sstream>
using namespace std;
class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, int tiles[100][100], unsigned int width, unsigned int height)
    {
        if (!m_tileset.loadFromFile(tileset)) return false;
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[j][i];
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        return true;
    }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
//const float pi = 3.1415;
const int h = 1500, w = 1500;
const float pi = 3.1415;
class bullet {
    public:
    float xV;
    float yV;
    float shotDmg;
    float durM;
    float explodeR;
    sf::Time durT;
    sf::Clock durC;
    sf::Texture bodyT;
    sf::Sprite body;
    bullet(string t1, int x, int y, int xVe, int yVe, int shotD, float dM, float eR) {
        xV = xVe;
        yV = yVe;
        shotDmg = shotD;
        bodyT.loadFromFile(t1);
        body.setTexture(bodyT);
        body.setOrigin(7,14);
        body.setPosition(x,y);
        durM = dM;
        explodeR = eR;
    }
};
class missile {
    public:
    float xV;
    float yV;
    float shotDmg;
    float turnRadius;
    float speed;
    float explodeD;
    float durM;
    float explodeR;
    float contactR;
    sf::Time durT;
    sf::Clock durC;
    sf::Texture bodyT;
    sf::Sprite body;
    missile(string t1, int x, int y, int xVe, int yVe, float shotD, float turnR, float spd, float eD, float dM, float eR, float cR) {
        xV = xVe;
        yV = yVe;
        speed = spd;
        shotDmg = shotD;
        turnRadius = turnR;
        explodeD = eD;
        contactR = cR;
        bodyT.loadFromFile(t1);
        body.setTexture(bodyT);
        body.setOrigin(7,30);
        body.setPosition(x,y);
        durM = dM;
        explodeR = eR;
    }
};
class plane {
    public:
    float speed;
    sf::Texture bodyT;
    sf::Sprite body;
    sf::Time shotT;
    sf::Clock shotC;
    sf::Time missileT;
    sf::Clock missileC;
    float shotCooldown;
    float shotSpeed;
    float shotDmg;
    float shotLong;
    float missileTurn;
    float missileDmg;
    float missileSpeed;
    float missileCooldown;
    float missileLong;
    float explodeD;
    float explodeR;
    float explodeR2;
    float contactR;
    float regen;
    float xV;
    float yV;
    float hp;
    float maxHP;
    float maxSpeed;
    float upgrades[9];
    int upgradeAmn[9];
    float costs[10];
    float maxUpgrades;
    int shotAmn;
    int missileAmn;
    int missileAmmo;
    int value;
    vector<bullet> shots;
    vector<missile> missiles;
    string shotTexture;
    string missileTexture;
    void shoot() {
        float ang = (body.getRotation()-90)/180*pi;
        shots.push_back(bullet(shotTexture,body.getPosition().x, body.getPosition().y,shotSpeed*cos(ang),shotSpeed*sin(ang),shotDmg, shotLong,explodeR2));
        shots[shotAmn].body.setRotation(body.getRotation());
        shotAmn++;
    }
    void shoot2() {
        float ang = (body.getRotation()-90)/180*pi;
        for(int i = 0; i < 6; i++) {
            if(missileAmmo > 0) {
                missiles.push_back(missile(missileTexture,body.getPosition().x-cos(ang+pi/2)*(23.0*i-57.5), body.getPosition().y-sin(ang+pi/2)*(23.0*i-57.5),missileSpeed*cos(ang),missileSpeed*sin(ang), missileDmg, missileTurn, missileSpeed, explodeD, missileLong, explodeR, contactR));
                missiles[missileAmn].body.setRotation(body.getRotation());
                missileAmn++;
                missileAmmo--;
            }
        }
    }
    void incr(int which) {
        if(which == 0) {
            hp+=upgrades[0]/maxHP*hp;
            maxHP+=upgrades[0];
        }
        if(which == 1) {
            regen+=upgrades[1];
        }
        if(which == 2) {
            maxSpeed+=upgrades[2]/speed*maxSpeed;
            speed+=upgrades[2];
        }
        if(which == 3) {
            shotCooldown-=upgrades[3];
        }
        if(which == 4) {
            shotDmg+=upgrades[4];
        }
        if(which == 5) {
            shotSpeed+=upgrades[5];
        }
        if(which == 6) {
            missileCooldown-=upgrades[6];
        }
        if(which == 7) {
            missileDmg+=upgrades[7];
        }
        if(which == 8) {
            missileTurn+=upgrades[8];
        }
    }
    plane(string t1, string t2, string t3, float hpM, float rg, float spd, float maxS, int x, int y, float shotM, float shotD, float turnR, float missileD, float missileM, float missileS, float shotS, float eD, float mL, float sL, float eR, float cR, float eR2, int missileA, int val, float upgrs[9], float csts[10], float maxUpgr) {
        speed = spd;
        bodyT.loadFromFile(t1);
        shotTexture = t2;
        missileTexture = t3;
        bodyT.setSmooth(true);
        body.setTexture(bodyT);
        body.setOrigin(290,220);
        body.setScale(0.25,0.25);
        body.setPosition(x,y);
        shotAmn = 0;
        shotSpeed = shotS;
        shotCooldown = shotM;
        shotDmg = shotD;
        missileAmn = 0;
        missileAmmo = 0;
        missileTurn = turnR;
        missileDmg = missileD;
        missileCooldown = missileM;
        missileAmmo = missileA;
        missileSpeed = missileS;
        missileLong = mL;
        shotLong = sL;
        explodeD = eD;
        explodeR = eR;
        explodeR2 = eR2;
        contactR = cR;
        maxSpeed = maxS;
        hp = hpM;
        maxHP = hpM;
        regen = rg;
        value = val;
        xV = 0;
        yV = 0;
        for(int i = 0; i < 9; i++) {
            upgrades[i] = upgrs[i];
            upgradeAmn[i] = 0;
        }
        for(int i = 0; i < 10; i++) {
            costs[i] = csts[i];
        }
        maxUpgrades = maxUpgr;
    }
    plane() {}
};
class spawnPlane {
    public:
    plane spawned;
    float time;
    float x;
    float y;
    spawnPlane (float tme, float xP, float yP, plane sp) {
        spawned = sp;
        time = tme;
        x = xP;
        y = yP;
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(w,h), "Game window");
    sf::View view1(sf::FloatRect(0.f, 0.f, 1500.f, 1500.f));
    window.setFramerateLimit(60);
    int screen = 0;
    const int width = 100, height = 100, sz = 200;
    float upgrTmp[9] = {20,0.1,200,0.02,0.4,600,0.5,2,36};
    float cstTmp[10] = {50,100,150,200,300,0,0,0,0,0};
    float upgrTmpE[9] = {0,0,0,0,0,0,0,0,0};
    float cstTmpE[10] = {0,0,0,0,0,0,0,0,0,0};
    int level[height][width];
    freopen("resources/gameMap1..csv","r",stdin);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            scanf("%d",&level[i][j]);
        }
    }
    TileMap map;
    if (!map.load("resources/Tileset.png", sf::Vector2u(sz, sz), level, width, height)) return -1;
    plane playerTemplate("resources/player.png", "resources/shot.png", "resources/missile.png", 100, 0.5, 2000, 1040, 750, 750, 0.2, 2, 180, 10, 5, 1500, 3000, 10, 10, 2.5, 250, 50, 50, 100, 100, upgrTmp, cstTmp, 5);
    plane player = playerTemplate;
    plane enemyTemplate1("resources/enemy1.png", "resources/shot2.png", "resources/missile.png", 50, 0, 400, 400, 750, 750, 1, 2, 180, 25, 10, 1000, 2000, 30, 5, 1, 125, 25, 50, 100, 25, upgrTmpE,cstTmpE,0);
    plane enemyTemplate2("resources/enemy2.png", "resources/shot3.png", "resources/missile.png", 100, 0, 400, 350, 750, 750, 0.5, 10, 180, 25, 10, 1000, 2000, 30, 5, 1, 125, 25, 75, 100, 50, upgrTmpE,cstTmpE,0);
    plane enemyTemplate3("resources/enemy3.png", "resources/shot4.png", "resources/missile.png", 250, 0, 200, 300, 750, 750, 1, 25, 90, 25, 10, 1000, 1000, 30, 5, 4, 125, 25, 100, 100, 125, upgrTmpE,cstTmpE,0);
    vector<plane> enemies;
    vector<spawnPlane> spawningEnemies;
    int spawningAmn = 15, currEnemy = 0;
    spawningEnemies.push_back(spawnPlane(2,750,750,enemyTemplate1));
    spawningEnemies.push_back(spawnPlane(4,750,750,enemyTemplate1));
    spawningEnemies.push_back(spawnPlane(6,750,750,enemyTemplate1));
    spawningEnemies.push_back(spawnPlane(8,750,750,enemyTemplate1));
    spawningEnemies.push_back(spawnPlane(10,750,750,enemyTemplate1));
    spawningEnemies.push_back(spawnPlane(12,750,750,enemyTemplate2));
    spawningEnemies.push_back(spawnPlane(14,750,750,enemyTemplate2));
    spawningEnemies.push_back(spawnPlane(16,750,750,enemyTemplate2));
    spawningEnemies.push_back(spawnPlane(18,750,750,enemyTemplate2));
    spawningEnemies.push_back(spawnPlane(20,750,750,enemyTemplate2));
    spawningEnemies.push_back(spawnPlane(22,750,750,enemyTemplate3));
    spawningEnemies.push_back(spawnPlane(24,750,750,enemyTemplate3));
    spawningEnemies.push_back(spawnPlane(26,750,750,enemyTemplate3));
    spawningEnemies.push_back(spawnPlane(28,750,750,enemyTemplate3));
    spawningEnemies.push_back(spawnPlane(30,750,750,enemyTemplate3));
    sf::Clock gameTimeC;
    sf::Time gameTimeT;
    sf::Font mainFont;
    mainFont.loadFromFile("resources/sansation.ttf");
    sf::Text deathAmn;
    deathAmn.setFont(mainFont);
    deathAmn.setString("0");
    deathAmn.setCharacterSize(80);
    deathAmn.setFillColor(sf::Color::Black);
    deathAmn.setPosition(sf::Vector2f(363,5));
    sf::Text coinAmn;
    coinAmn.setFont(mainFont);
    coinAmn.setString("0");
    coinAmn.setCharacterSize(80);
    coinAmn.setFillColor(sf::Color::Black);
    coinAmn.setPosition(sf::Vector2f(293,97));
    sf::Texture upgradeScreenT;
    upgradeScreenT.loadFromFile("resources/UpgradeScreen.png");
    sf::Sprite upgradeScreen;
    upgradeScreen.setTexture(upgradeScreenT);
    sf::Time deltaTimeT;
    sf::Clock deltaTimeC;
    sf::Time upgradeT;
    sf::Clock upgradeC;
    sf::Sprite hotBarMain;
    sf::Texture hotBarMainT;
    hotBarMainT.loadFromFile("resources/GameScreen.png");
    hotBarMain.setTexture(hotBarMainT);
    sf::RectangleShape hotBar1(sf::Vector2f(956,97));
    hotBar1.setPosition(543,2);
    hotBar1.setFillColor(sf::Color(224,32,32));
    sf::RectangleShape hotBar2(sf::Vector2f(233,43));
    hotBar2.setPosition(783,107);
    hotBar2.setFillColor(sf::Color(32,32,224));
    sf::RectangleShape hotBar3(sf::Vector2f(233,43));
    hotBar3.setPosition(1023,107);
    hotBar3.setFillColor(sf::Color(224,112,32));
    sf::RectangleShape hotBar4(sf::Vector2f(233,43));
    hotBar4.setPosition(1264,107);
    hotBar4.setFillColor(sf::Color(224,224,32));
    sf::Texture upgradeButtonT;
    upgradeButtonT.loadFromFile("resources/UpgradeButton.png");
    sf::Sprite upgradeButtons[9];
    sf::Text upgradeAmnDisps[9];
    sf::Text upgradeCostDisps[9];
    for(int i = 0; i < 9; i++) {
        int tmp1 = i/3;
        int tmp2 = i%3;
        float posX = 228+tmp2*523;
        float posY = 444+tmp1*465;
        upgradeButtons[i].setTexture(upgradeButtonT);
        upgradeButtons[i].setOrigin(102,102);
        upgradeButtons[i].setPosition(sf::Vector2f(posX,posY));
        upgradeAmnDisps[i].setFont(mainFont);
        upgradeAmnDisps[i].setString("0/5");
        upgradeAmnDisps[i].setCharacterSize(50);
        upgradeAmnDisps[i].setFillColor(sf::Color::Black);
        upgradeAmnDisps[i].setPosition(sf::Vector2f(posX+127,posY-35));
        upgradeCostDisps[i].setFont(mainFont);
        upgradeCostDisps[i].setString("50");
        upgradeCostDisps[i].setCharacterSize(50);
        upgradeCostDisps[i].setFillColor(sf::Color::Black);
        upgradeCostDisps[i].setPosition(sf::Vector2f(posX-222,posY-35));
    }
    float deltaTime, xV = 0, yV = 0, frict = 0.15;
    float upgradeCD = 0.25;
    bool mouseButton1 = false;
    bool mouseButton2 = false;
    int enemyAmn = 0;
    int deaths = 0;
    int coins = 0;
    while (window.isOpen()) {
        sf::Event event;
        if(screen == 0) {
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    mouseButton1 = true;
                }
                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    mouseButton1 = false;
                }
                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                    mouseButton2 = true;
                }
                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
                    mouseButton2 = false;
                }
                upgradeT = upgradeC.getElapsedTime();
                if(upgradeT.asSeconds() >= upgradeCD && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                    screen = 1;
                    upgradeC.restart();
                }
                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            //bullet shooting
            player.shotT = player.shotC.getElapsedTime();
            if(mouseButton1 == true && player.shotT.asSeconds() >= player.shotCooldown) {
                player.shoot();
                player.shots[player.shotAmn-1].body.setTexture(player.shots[player.shotAmn-1].bodyT);
                player.shotC.restart();
            }
            //missile shooting
            player.missileT = player.missileC.getElapsedTime();
            if(mouseButton2 == true && player.missileT.asSeconds() >= player.missileCooldown) {
                player.shoot2();
                for(int i = 0; i < player.missileAmn; i++) {
                    player.missiles[i].body.setTexture(player.missiles[player.missileAmn-1].bodyT);
                }
                player.missileC.restart();
            }
            //deltaTime
            deltaTimeT = deltaTimeC.getElapsedTime();
            deltaTime = deltaTimeT.asSeconds();
            deltaTimeC.restart();
            //player regen
            player.hp=min(player.maxHP,player.hp+player.regen*deltaTime);
            //enemy spawning
            gameTimeT = gameTimeC.getElapsedTime();
            while(currEnemy < spawningAmn && gameTimeT.asSeconds() >= spawningEnemies[currEnemy].time) {
                enemies.push_back(spawningEnemies[currEnemy].spawned);
                enemyAmn++;
                currEnemy++;
                for(int i = 0; i < enemyAmn; i++) {
                    enemies[i].body.setTexture(enemies[i].bodyT);
                }
            }
            //enemy AI
            bool bulletDel = false;
            for(int i = 0; i < enemyAmn; i++) {
                //regen
                enemies[i].hp= min(enemies[i].maxHP,enemies[i].hp+enemies[i].regen*deltaTime);
                //movement
                float px = player.body.getPosition().x;
                float py = player.body.getPosition().y;
                float bx = enemies[i].body.getPosition().x;
                float by = enemies[i].body.getPosition().y;
                float angle = atan2(py-by,px-bx)*180/pi;
                float currA = enemies[i].body.getRotation()-90;
                float changeA = 0;
                float tmp1 = angle+360-currA;
                float tmp2 = currA-angle+360;
                if(tmp1 > 360) tmp1-=360;
                if(tmp2 > 360) tmp2-=360;
                if(tmp1 < tmp2) {
                    changeA = currA+min(tmp1,enemies[i].missileTurn*deltaTime)+360;
                    if(changeA > 360) changeA -= 360;
                }
                if(tmp2 < tmp1) {
                    changeA = currA+max(-tmp2,-enemies[i].missileTurn*deltaTime)+360;
                    if(changeA > 360) changeA -= 360;
                }
                enemies[i].body.setRotation(changeA+90);
                enemies[i].xV = enemies[i].speed*cos((changeA)/180*pi);
                enemies[i].yV = enemies[i].speed*sin((changeA)/180*pi);
                enemies[i].body.move(enemies[i].xV*deltaTime,enemies[i].yV*deltaTime);
                //shooting
                enemies[i].shotT = enemies[i].shotC.getElapsedTime();
                if(changeA == angle && enemies[i].shotT.asSeconds() >= enemies[i].shotCooldown) {
                    enemies[i].shoot();
                    enemies[i].shots[enemies[i].shotAmn-1].body.setTexture(enemies[i].shots[enemies[i].shotAmn-1].bodyT);
                    enemies[i].shotC.restart();
                }
                //bullets
                for(int j = 0; j < enemies[i].shotAmn; j++) {
                    enemies[i].shots[j].body.move(enemies[i].shots[j].xV*deltaTime,enemies[i].shots[j].yV*deltaTime);
                    float sx = enemies[i].shots[j].body.getPosition().x;
                    float sy = enemies[i].shots[j].body.getPosition().y;
                    float px = player.body.getPosition().x;
                    float py = player.body.getPosition().y;
                    enemies[i].shots[j].durT = enemies[i].shots[j].durC.getElapsedTime();
                    if(sqrtf((px-sx)*(px-sx)+(py-sy)*(py-sy)) <= enemies[i].shots[j].explodeR) {
                        player.hp-=enemies[i].shots[j].shotDmg;
                        enemies[i].shots.erase(enemies[i].shots.begin()+j);
                        enemies[i].shotAmn--;
                        for(int l = 0; l < enemies[i].shotAmn; l++) {
                            enemies[i].shots[l].body.setTexture(enemies[i].shots[l].bodyT);
                        }
                    }
                    if((enemies[i].shots[j].durT.asSeconds() >= enemies[i].shots[j].durM) && bulletDel == false) {
                        enemies[i].shots.erase(enemies[i].shots.begin()+j);
                        enemies[i].shotAmn--;
                        for(int l = 0; l < enemies[i].shotAmn; l++) {
                            enemies[i].shots[l].body.setTexture(enemies[i].shots[l].bodyT);
                        }
                        bulletDel = true;
                    }
                }
                //death
                if(enemies[i].hp <= 0) {
                    enemies.erase(enemies.begin()+i);
                    enemyAmn--;
                    for(int j = 0; j < enemyAmn; j++) {
                        enemies[j].body.setTexture(enemies[j].bodyT);
                    }
                    coins+=enemies[i].value;
                    string tmp1;
                    stringstream tmp2;
                    tmp2 << coins;
                    tmp2 >> tmp1;
                    coinAmn.setString(tmp1);
                }
            }
            //bullet AI
            for(int i = 0; i < player.shotAmn; i++) {
                player.shots[i].body.move(player.shots[i].xV*deltaTime,player.shots[i].yV*deltaTime);
                float px = player.shots[i].body.getPosition().x;
                float py = player.shots[i].body.getPosition().y;
                player.shots[i].durT = player.shots[i].durC.getElapsedTime();
                for(int j = 0; j < enemyAmn; j++) {
                    float ex = enemies[j].body.getPosition().x;
                    float ey = enemies[j].body.getPosition().y;
                    if(sqrtf((ex-px)*(ex-px)+(ey-py)*(ey-py)) <= player.shots[i].explodeR) {
                        enemies[j].hp-=player.shots[i].shotDmg;
                        player.shots.erase(player.shots.begin()+i);
                        player.shotAmn--;
                        for(int l = 0; l < player.shotAmn; l++) {
                            player.shots[l].body.setTexture(player.shots[l].bodyT);
                        }
                        break;
                    }
                }
                if(player.shots[i].durT.asSeconds() >= player.shots[i].durM) {
                    player.shots.erase(player.shots.begin()+i);
                    player.shotAmn--;
                    for(int j = 0; j < player.shotAmn; j++) {
                        player.shots[j].body.setTexture(player.shots[j].bodyT);
                    }
                }
            }
            //missile AI
            for(int i = 0; i < player.missileAmn; i++) {
                float mx = sf::Mouse::getPosition(window).x+view1.getCenter().x-w/2;
                float my = sf::Mouse::getPosition(window).y+view1.getCenter().y-h/2;
                float bx = player.missiles[i].body.getPosition().x;
                float by = player.missiles[i].body.getPosition().y;
                float angle = atan2(my-by,mx-bx)*180/pi;
                float currA = player.missiles[i].body.getRotation()-90;
                float changeA;
                float tmp1 = angle+360-currA;
                float tmp2 = currA+360-angle;
                if(tmp1 > 360) tmp1 -= 360;
                if(tmp2 > 360) tmp2 -= 360;
                if(tmp1 < tmp2) {
                    changeA = currA+min(tmp1,player.missiles[i].turnRadius*deltaTime)+360;
                }
                if(tmp2 < tmp1) {
                    changeA = max(currA-player.missiles[i].turnRadius*deltaTime,angle);
                }
                player.missiles[i].body.setRotation(changeA+90);
                player.missiles[i].xV = player.missiles[i].speed*cos((changeA)/180*pi);
                player.missiles[i].yV = player.missiles[i].speed*sin((changeA)/180*pi);
                player.missiles[i].body.move(player.missiles[i].xV*deltaTime,player.missiles[i].yV*deltaTime);
                player.missiles[i].durT = player.missiles[i].durC.getElapsedTime();
                if(sqrtf((mx-bx)*(mx-bx)+(my-by)*(my-by)) < player.missiles[i].contactR || player.missiles[i].durT.asSeconds() >= player.missiles[i].durM) {
                    for(int j = 0; j < enemyAmn; j++) {
                        float ex = enemies[j].body.getPosition().x;
                        float ey = enemies[j].body.getPosition().y;
                        if(sqrtf((ex-bx)*(ex-bx)+(ey-by)*(ey-by)) <= player.missiles[i].explodeR) {
                            enemies[j].hp-=player.missiles[i].explodeD;
                        }
                    }
                    player.missiles.erase(player.missiles.begin()+i);
                    player.missileAmn--;
                    for(int j = 0; j < player.missileAmn; j++) {
                        player.missiles[j].body.setTexture(player.missiles[j].bodyT);
                    }
                }
            }
            //player AI
            player.body.move(xV*deltaTime,yV*deltaTime);
            view1.move(xV*deltaTime,yV*deltaTime);
            hotBarMain.move(xV*deltaTime,yV*deltaTime);
            hotBar1.move(xV*deltaTime,yV*deltaTime);
            hotBar2.move(xV*deltaTime,yV*deltaTime);
            hotBar3.move(xV*deltaTime,yV*deltaTime);
            hotBar4.move(xV*deltaTime,yV*deltaTime);
            deathAmn.move(xV*deltaTime,yV*deltaTime);
            coinAmn.move(xV*deltaTime,yV*deltaTime);
            upgradeScreen.move(xV*deltaTime,yV*deltaTime);
            for(int i = 0; i < 9; i++) {
                upgradeButtons[i].move(xV*deltaTime,yV*deltaTime);
                upgradeAmnDisps[i].move(xV*deltaTime,yV*deltaTime);
                upgradeCostDisps[i].move(xV*deltaTime,yV*deltaTime);
            }
            window.setView(view1);
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            float px = player.body.getPosition().x;
            float py = player.body.getPosition().y;
            float angle = atan2(my-py+(view1.getCenter().y-h/2),mx-px+(view1.getCenter().x-w/2))*180/pi;
            player.body.setRotation(angle+90);
            xV+=deltaTime*player.speed*cos(angle/180*pi);
            yV+=deltaTime*player.speed*sin(angle/180*pi);
            xV=xV*powf(frict,deltaTime);
            yV=yV*powf(frict,deltaTime);
            if(player.hp <= 0) {
                player = playerTemplate;
                player.body.setTexture(player.bodyT);
                view1.setCenter(w/2,h/2);
                hotBarMain.setPosition(0,0);
                upgradeScreen.setPosition(0,0);
                for(int i = 0; i < 9; i++) {
                    int tmp1 = i/3;
                    int tmp2 = i%3;
                    float posX = 228+tmp2*523;
                    float posY = 444+tmp1*465;
                    upgradeButtons[i].setPosition(sf::Vector2f(posX,posY));
                    upgradeAmnDisps[i].setPosition(sf::Vector2f(posX+127,posY-35));
                    upgradeCostDisps[i].setPosition(sf::Vector2f(posX-222,posY-35));
                }
                deaths++;
                deathAmn.setPosition(363,5);
                string tmp1;
                stringstream tmp2;
                tmp2 << deaths;
                tmp2 >> tmp1;
                deathAmn.setString(tmp1);
                coinAmn.setPosition(293,97);
            }
            //status bars
            float h1 = player.hp/player.maxHP*956;
            float h2 = sqrtf(xV*xV+yV*yV)/player.maxSpeed*233;
            float h3 = min(player.missileCooldown,player.missileT.asSeconds())/player.missileCooldown*233;
            float h4 = min(player.shotCooldown,player.shotT.asSeconds())/player.shotCooldown*233;
            float vX = view1.getCenter().x-w/2, vY = view1.getCenter().y-h/2;
            hotBar1.setSize(sf::Vector2f(h1,97));
            hotBar1.setPosition(sf::Vector2f(543+956-h1+vX,2+vY));
            hotBar2.setSize(sf::Vector2f(h2,43));
            hotBar2.setPosition(sf::Vector2f(232+783-h2+vX,107+vY));
            hotBar3.setSize(sf::Vector2f(h3,43));
            hotBar3.setPosition(sf::Vector2f(232+1023-h3+vX,107+vY));
            hotBar4.setSize(sf::Vector2f(h4,43));
            hotBar4.setPosition(sf::Vector2f(232+1264-h4+vX,107+vY));
            //rendering
            window.clear(sf::Color(192,192,192));
            window.draw(map);
            for(int i = 0; i < player.shotAmn; i++) {
                window.draw(player.shots[i].body);
            }
            for(int i = 0; i < player.missileAmn; i++) {
                window.draw(player.missiles[i].body);
            }
            for(int i = 0; i < enemyAmn; i++) {
                window.draw(enemies[i].body);
                for(int j = 0; j < enemies[i].shotAmn; j++) {
                    window.draw(enemies[i].shots[j].body);
                }
            }
            window.draw(player.body);
            window.draw(hotBarMain);
            window.draw(hotBar1);
            window.draw(hotBar2);
            window.draw(hotBar3);
            window.draw(hotBar4);
            window.draw(deathAmn);
            window.draw(coinAmn);
            window.display();
        }
        if(screen == 1) {
            while(window.pollEvent(event)) {
                upgradeT = upgradeC.getElapsedTime();
                    float mx = sf::Mouse::getPosition(window).x;
                    float my = sf::Mouse::getPosition(window).y;
                    for(int i = 0; i < 9; i++) {
                        int tmp1 = i/3;
                        int tmp2 = i%3;
                        float minX = 126+tmp2*523;
                        float minY = 342+tmp1*465;
                        float maxX = minX+204;
                        float maxY = minY+204;
                        if(player.upgradeAmn[i] < player.maxUpgrades && player.costs[player.upgradeAmn[i]] <= coins && mx >= minX && my >= minY && mx <= maxX && my <= maxY) {
                            upgradeButtons[i].setScale(1.2,1.2);
                            if(upgradeT.asSeconds() >= upgradeCD && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                coins -= player.costs[player.upgradeAmn[i]];
                                player.incr(i);
                                playerTemplate.incr(i);
                                playerTemplate.upgradeAmn[i]++;
                                player.upgradeAmn[i]++;
                                string tmp1;
                                stringstream tmp2;
                                tmp2 << coins;
                                tmp2 >> tmp1;
                                coinAmn.setString(tmp1);
                                string tmp3;
                                stringstream tmp4;
                                tmp4 << player.upgradeAmn[i] << "/" << player.maxUpgrades;
                                tmp4 >> tmp3;
                                upgradeAmnDisps[i].setString(tmp3);
                                if(player.upgradeAmn[i] < player.maxUpgrades) {
                                    string tmp5;
                                    stringstream tmp6;
                                    tmp6 << player.costs[player.upgradeAmn[i]];
                                    tmp6 >> tmp5;
                                    upgradeCostDisps[i].setString(tmp5);
                                }
                                else {
                                    upgradeCostDisps[i].setString("N/A");
                                }
                                upgradeC.restart();
                                break;
                            }
                        }
                        else {
                            upgradeButtons[i].setScale(1,1);
                        }
                    }
                if(upgradeT.asSeconds() >= upgradeCD && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                    deltaTimeC.restart();
                    screen = 0;
                    upgradeC.restart();
                }
                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear(sf::Color(192,192,192));
            window.draw(upgradeScreen);
            window.draw(coinAmn);
            window.draw(deathAmn);
            for(int i = 0; i < 9; i++) {
                window.draw(upgradeButtons[i]);
                window.draw(upgradeAmnDisps[i]);
                window.draw(upgradeCostDisps[i]);
            }
            window.display();
        }
    }
    fclose(stdin);
    return 0;
}