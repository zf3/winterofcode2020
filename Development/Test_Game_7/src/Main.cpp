#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <sstream>
using namespace std;
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        if (!m_tileset.loadFromFile(tileset)) return false;
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width];
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
    sf::Time durT;
    sf::Clock durC;
    sf::Texture bodyT;
    sf::Sprite body;
    missile(string t1, int x, int y, int xVe, int yVe, float shotD, float turnR, float spd, float eD, float dM, float eR) {
        xV = xVe;
        yV = yVe;
        speed = spd;
        shotDmg = shotD;
        turnRadius = turnR;
        explodeD = eD;
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
    float regen;
    float xV;
    float yV;
    float hp;
    float maxHP;
    float maxSpeed;
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
                missiles.push_back(missile(missileTexture,body.getPosition().x-cos(ang+pi/2)*(23.0*i-57.5), body.getPosition().y-sin(ang+pi/2)*(23.0*i-57.5),missileSpeed*cos(ang),missileSpeed*sin(ang), missileDmg, missileTurn, missileSpeed, explodeD, missileLong, explodeR));
                missiles[missileAmn].body.setRotation(body.getRotation());
                missileAmn++;
                missileAmmo--;
            }
        }
    }
    plane(string t1, string t2, string t3, float hpM, float rg, float spd, float maxS, int x, int y, float shotM, float shotD, float turnR, float missileD, float missileM, float missileS, float shotS, float eD, float mL, float sL, float eR, float eR2, int missileA, int val) {
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
        maxSpeed = maxS;
        hp = hpM;
        maxHP = hpM;
        regen = rg;
        value = val;
        xV = 0;
        yV = 0;
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(w,h), "Game window");
    sf::View view1(sf::FloatRect(0.f, 0.f, 1500.f, 1500.f));
    window.setFramerateLimit(60);
    const int width = 32, height = 16, sz = 200;
    const int level[] =
    {
        0,0,0,0,0,2,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,2,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,2,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,2,6,4,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        5,5,5,5,5,5,19,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        3,3,3,3,3,2,6,4,3,3,3,3,3,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,2,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,2,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,2,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,24,5,5,7,7,10,7,7,7,10,7,7,7,10,7,
        0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,24,5,26,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,0,25,5,5,5,5,5,5,5,5,26,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8,9,0,9,8,9,0,9,8,9,
    };
    TileMap map;
    if (!map.load("resources/Tileset.png", sf::Vector2u(sz, sz), level, width, height)) return -1;
    plane player("resources/player.png", "resources/shot.png", "resources/missile.png", 100, 0.5, 2000, 1040, 750, 750, 0.2, 2, 180, 50, 5, 1500, 3000, 30, 10, 2, 250, 50, 100, 100);
    vector<plane> enemies;
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
    sf::Time deltaTimeT;
    sf::Clock deltaTimeC;
    sf::Time enemyT;
    sf::Clock enemyC;
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
    float enemyM = 10;
    float deltaTime, xV = 0, yV = 0, frict = 0.15;
    bool mouseButton1 = false;
    bool mouseButton2 = false;
    int enemyAmn = 0;
    int deaths = 0;
    int coins = 0;
    while (window.isOpen()) {
        sf::Event event;
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
        enemyT = enemyC.getElapsedTime();
        if(enemyT.asSeconds() >= enemyM) {
            enemies.push_back(plane("resources/enemy.png", "resources/shot2.png", "resources/missile.png", 10, 0, 400, 400, 750, 750, 1, 2, 180, 25, 10, 1000, 2000, 30, 5, 1, 125, 50, 100, 10));
            enemyAmn++;
            for(int i = 0; i < enemyAmn; i++) {
                enemies[i].body.setTexture(enemies[i].bodyT);
            }
            enemyC.restart();
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
            if(sqrtf((mx-bx)*(mx-bx)+(my-by)*(my-by)) < player.missiles[i].explodeD || player.missiles[i].durT.asSeconds() >= player.missiles[i].durM) {
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
            player = plane("resources/player.png", "resources/shot.png", "resources/missile.png", 100, 0.5, 2000, 1037, 750, 750, 0.2, 2, 180, 50, 5, 1500, 3000, 30, 10, 2, 250, 50, 100, 100);
            player.body.setTexture(player.bodyT);
            view1.setCenter(w/2,h/2);
            hotBarMain.setPosition(0,0);
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
    return 0;
}