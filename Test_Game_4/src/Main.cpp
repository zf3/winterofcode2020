#include<iostream>
#include<vector>
using namespace std;
//enum or constant definitions
const float PI = 3.1415;
//classes
//tilemap class
class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        if (!m_tileset.loadFromFile(tileset))
            return false;
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
class display {
    public:
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Sprite display1;
    sf::Sprite display2;
    sf::Sprite display3;
    sf::Sprite display4;
    sf::RectangleShape block1;
    sf::RectangleShape block2;
    sf::RectangleShape block3;
    float scale;
    void renew(float wC, float wCM, float wC2, float wCM2, float hp, float mHP) {
        float e,f;
        if((1-wC2/wCM2) > 0) {
            e = 1-wC2/wCM2;
        }
        else {
            e = 0;
        }
        if((1-wC/wCM) > 0) {
            f = 1-wC/wCM;
        }
        else {
            f = 0;
        }
        block1.setSize(sf::Vector2f(593*f*scale,200*scale));
        block2.setSize(sf::Vector2f(-(593*e*scale),200*scale));
        block3.setSize(sf::Vector2f(462*scale,462*(1-hp/mHP)*scale));
    }
    void move(float x, float y) {
        display1.move(x,y);
        display2.move(x,y);
        display3.move(x,y);
        display4.move(x,y);
        block1.move(x,y);
        block2.move(x,y);
        block3.move(x,y);
    }
    display(string a, string b, string c, string d, int re, int gr, int bl, int x, int y, float scl) {
        scale = scl;
        texture1.loadFromFile(a);
        texture1.setSmooth(true);
        texture2.loadFromFile(b);
        texture2.setSmooth(true);
        texture3.loadFromFile(c);
        texture3.setSmooth(true);
        texture4.loadFromFile(d);
        texture4.setSmooth(true);
        display1.setTexture(texture1);
        display1.setScale(sf::Vector2f(scl,scl));
        display2.setTexture(texture2);
        display2.setScale(sf::Vector2f(scl,scl));
        display3.setTexture(texture3);
        display3.setScale(sf::Vector2f(scl,scl));
        display4.setTexture(texture4);
        display4.setScale(sf::Vector2f(scl,scl));
        block1.setFillColor(sf::Color(re,gr,bl));
        block1.setSize(sf::Vector2f(593*scl,200*scl));
        block2.setFillColor(sf::Color(re,gr,bl));
        block2.setSize(sf::Vector2f(-593*scl,200*scl));
        block3.setFillColor(sf::Color(re,gr,bl));
        block3.setSize(sf::Vector2f(462*scl,462*scl));
        display1.setPosition(x-608,y+309);
        display2.setPosition(x-608,y+309);
        display3.setPosition(x-608,y+309);
        display4.setPosition(x-608,y+309);
        block1.setPosition(x-608+373/2,y+309+264/2);
        block2.setPosition(x-608+2048/2,y+309+253/2);
        block3.setPosition(x-608+983/2,y+309+84/2);
    }
};
class basicChar {
    public:
    int atkAnimStage;
    int atkAnimStage2;
    int hitbox;
    float atkDist;
    bool atkActive;
    bool atkActive2;
    bool damaged;
    sf::Clock wCooldownClock;
    sf::Clock animClock;
    sf::Clock wCooldownClock2;
    sf::Clock animClock2;
    sf::Time wCooldownT;
    sf::Time animTime;
    sf::Time wCooldownT2;
    sf::Time animTime2;
    float spd;
    float wCooldownM;
    float wCooldown;
    float wCooldownM2;
    float wCooldown2;
    float hp;
    float maxHP;
    float dmg;
    float dmg2;
    float atkD;
    float atkD2;
    float atk2Spd;
    float atk2Rot;
    sf::Texture atkAnims[7];
    sf::Texture atkAnims2[20];
    sf::Vector2f tipPos[7];
    sf::Vector2f tipPos2[20];
    int totalCycles;
    int totalCycles2;
    sf::Sprite body;
    sf::Sprite weapon;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarBack;
    sf::Texture bTexture;
    sf::Texture bTexture2;
    sf::Texture wTexture;
    //wall collision detection
    bool objCollisions(float xM, float yM, const int *tilemap, int xL, int *objs, int n) {
        float px = body.getPosition().x+xM, py = body.getPosition().y+yM;
        int c1x = (px+(hitbox-1))/hitbox/2, c1y = (py+(hitbox-1))/hitbox/2;
        int c2x = (px-(hitbox-1))/hitbox/2, c2y = (py+(hitbox-1))/hitbox/2;
        int c3x = (px+(hitbox-1))/hitbox/2, c3y = (py-(hitbox-1))/hitbox/2;
        int c4x = (px-(hitbox-1))/hitbox/2, c4y = (py-(hitbox-1))/hitbox/2;
        for(int i = 0; i < n; i++) {
            if(*(tilemap+c1x+c1y*xL) == *(objs+i))
                return true;
            if(*(tilemap+c2x+c2y*xL) == *(objs+i))
                return true;
            if(*(tilemap+c3x+c3y*xL) == *(objs+i))
                return true;
            if(*(tilemap+c4x+c4y*xL) == *(objs+i))
                return true;
        }
        return false;
    }
    //animation cycles
    void basicCollisionDetection (basicChar *target) {
        float bx = body.getPosition().x, by = body.getPosition().y;
        float br = body.getRotation()/180*PI;
        float tx = target->body.getPosition().x, ty = target->body.getPosition().y;
        float wx = bx+cos(br)*tipPos[atkAnimStage].x+cos(br-PI/2)*tipPos[atkAnimStage].y
        , wy = by+sin(br)*tipPos[atkAnimStage].x+sin(br-PI/2)*tipPos[atkAnimStage].y;
        if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= target->hitbox && target->damaged == false) {
            target->hp-=dmg;
            target->damaged = true;
            target->body.setTexture(target->bTexture2);
        }
    }
    void loadAnim(int enemyCount, vector<basicChar> &enemies) {
        animTime = animClock.getElapsedTime();
        if(animTime.asSeconds() >= atkD/totalCycles && atkAnimStage < totalCycles) {
            animClock.restart();
            weapon.setTexture(atkAnims[atkAnimStage]);
            atkAnimStage++;
            for(int i = 0; i < enemyCount; i++) {
                basicCollisionDetection(&enemies[i]);
            }
        }
        else if(animTime.asSeconds() >= atkD/totalCycles && atkAnimStage >= totalCycles) {
            weapon.setTexture(wTexture);
            atkAnimStage = 0;
            atkActive = false;
            weapon.setOrigin(312,312);
            for(int i = 0; i < enemyCount; i++) {
                enemies[i].damaged = false;
                enemies[i].body.setTexture(enemies[i].bTexture);
            }
        }
    }
    void basicCollisionDetection2 (basicChar *target) {
        float bx = body.getPosition().x, by = body.getPosition().y;
        float br = body.getRotation()/180*PI;
        float tx = target->body.getPosition().x, ty = target->body.getPosition().y;
        float wx = wx = bx+cos(br)*tipPos2[atkAnimStage].x+cos(br-PI/2)*tipPos[atkAnimStage].y
        , wy = by+sin(br)*tipPos2[atkAnimStage].x+sin(br-PI/2)*tipPos[atkAnimStage].y;
        if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= hitbox && target->damaged == false) {
            target->hp-=dmg2;
            target->damaged = true;
            target->body.setTexture(target->bTexture2);
        }
    }
    void loadAnim2(int enemyCount, vector<basicChar> &enemies, float deltaTime, sf::View *gameView, sf::RenderWindow *window, const int *tilemap,int xL,int *objs, int n, display *playerHUD) {
        animTime2 = animClock2.getElapsedTime();
        float xM = deltaTime*atk2Spd*cos(body.getRotation()/180*PI);
        float yM = deltaTime*atk2Spd*sin(body.getRotation()/180*PI);
        if(objCollisions(xM,0,tilemap,xL,objs,n) == false) {
            body.move(xM,0);
            weapon.move(xM,0);
            hpBar.move(xM,0);
            hpBarBack.move(xM,0);
            playerHUD->move(xM,0);
            gameView->move(xM,0);
            window->setView(*gameView);
        }
        if(objCollisions(0,yM,tilemap,xL,objs,n) == false) {
            body.move(0,yM);
            weapon.move(0,yM);
            hpBar.move(0,yM);
            hpBarBack.move(0,yM);
            playerHUD->move(0,yM);
            gameView->move(0,yM);
            window->setView(*gameView);
        }
        body.rotate(deltaTime*atk2Rot);
        weapon.rotate(deltaTime*atk2Rot);
        hpBar.rotate(deltaTime*atk2Rot);
        hpBarBack.rotate(deltaTime*atk2Rot);
        if(animTime2.asSeconds() >= atkD2/totalCycles2 && atkAnimStage2 < totalCycles2) {
            animClock2.restart();
            weapon.setTexture(atkAnims2[atkAnimStage2]);
            atkAnimStage2++;
            for(int i = 0; i < enemyCount; i++) {
                basicCollisionDetection2(&enemies[i]);
            }
        }
        else if(animTime2.asSeconds() >= atkD2/totalCycles2 && atkAnimStage2 >= totalCycles2) {
            weapon.setTexture(wTexture);
            atkAnimStage2 = 0;
            atkActive2 = false;
            weapon.setOrigin(312,312);
            for(int i = 0; i < enemyCount; i++) {
                enemies[i].damaged = false;
                enemies[i].body.setTexture(enemies[i].bTexture);
            }
        }
    }
    void move(float x, float y) {
        body.move(x,y);
        weapon.move(x,y);
        hpBar.move(x,y);
        hpBarBack.move(x,y);
    }
    //constructor
    basicChar (int sp, int re,int gr,int bl,int x,int y) {
        body.setOrigin(sf::Vector2f(312,312));
        body.setPosition(sf::Vector2f(x,y));
        weapon.setOrigin(sf::Vector2f(312,312));
        weapon.setPosition(sf::Vector2f(x,y));
        atkActive = false;
        atkActive2 = false;
        atkAnimStage = 0;
        atkAnimStage2 = 0;
        atkDist = 0;
        wCooldown = 0;
        wCooldown2 = 0;
        damaged = false;
        spd = sp;
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
class weapon {
    public:
    float spdM;
    float wCooldownM;
    float wCooldownM2;
    float dmg;
    float dmg2;
    float atkD;
    float atkD2;
    float atk2Spd;
    float atk2Rot;
    sf::Texture atkAnims[7];
    sf::Texture atkAnims2[20];
    sf::Vector2f tipPos[7];
    sf::Vector2f tipPos2[20];
    int totalCycles;
    int totalCycles2;
    float atkDist;
    sf::Texture wTexture;
    void apply(basicChar *target) {
        target->atkDist = atkDist;
        target->spd = target->spd*spdM;
        target->wCooldownM = wCooldownM;
        target->wCooldownM2 = wCooldownM2;
        target->dmg = dmg;
        target->dmg2 = dmg2;
        target->atkD = atkD;
        target->atkD2 = atkD2;
        target->atk2Spd = atk2Spd;
        target->atk2Rot = atk2Rot;
        target->totalCycles = totalCycles;
        target->totalCycles2 = totalCycles2;
        target->weapon.setTexture(wTexture);
        target->wTexture = wTexture;
        for(int i = 0; i < totalCycles; i++) {
            target->atkAnims[i] = atkAnims[i];
            target->tipPos[i] = tipPos[i];
        }
        for(int i = 0; i < totalCycles2; i++) {
            target->atkAnims2[i] = atkAnims2[i];
            target->tipPos2[i] = tipPos2[i];
        }
    }
    weapon(string a, string *textures, string *textures2, sf::Vector2f *tPos, sf::Vector2f *tPos2, int n, int n2, float sp, float cM, float cM2, float dm, float dm2, float aD, float aD2, float a2S, float a2R, float atkDi) {
        for(int i = 0; i < n; i++) {
            atkAnims[i].loadFromFile(*(textures+i));
            tipPos[i] = *(tPos+i);
        }
        for(int i = 0; i < n2; i++) {
            atkAnims2[i].loadFromFile(*(textures2+i));
            tipPos2[i] = *(tPos2+i);
        }
        spdM = sp;
        wTexture.loadFromFile(a);
        wTexture.setSmooth(true);
        totalCycles = n;
        totalCycles2 = n2;
        wCooldownM = cM;
        wCooldownM2 = cM2;
        dmg = dm;
        dmg2 = dm2;
        atkD = aD;
        atkD2 = aD2;
        atk2Spd = a2S;
        atk2Rot = a2R;
        atkDist = atkDi;
    }
};
class armor {
    public:
    float spdM;
    int hitbox;
    float maxHP;
    sf::Texture bTexture;
    sf::Texture iTexture;
    void apply(basicChar *target) {
        target->hp = maxHP;
        target->maxHP = maxHP;
        target->hitbox = hitbox;
        target->spd = target->spd*spdM;
        target->atk2Spd = target->atk2Spd*spdM;
        target->body.setTexture(bTexture);
        target->bTexture = bTexture;
        target->bTexture2 = iTexture;
    }
    armor(string a, string b, float sp, float hp, float hb) {
        bTexture.loadFromFile(a);
        bTexture.setSmooth(true);
        iTexture.loadFromFile(b);
        iTexture.setSmooth(true);
        spdM = sp;
        maxHP = hp;
        hitbox = hb;
    }
};
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
    int enemyCount = 0;
    int objs[1];
    float deltaTime;
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
    weapon sword("resources/Weapon1/1a.png",arr,arr2,tipPos,tipPos2,7,20,1,0.5,5,10,50,0.5,1,500,0,275);
    weapon dagger("resources/Weapon2/2a.png",arr3,arr4,tipPos3,tipPos4,3,20,1.25,0.25,2.5,2.5,25,0.25,1,750,-90,190);
    weapon axe("resources/Weapon3/3a.png",arr5,arr6,tipPos5,tipPos6,7,20,0.75,0.75,7.5,25,75,0.75,1,0,-360,200);
    armor plate("resources/Armor1/1a.png","resources/Armor1/1b.png",0.75,125,75);
    armor chain("resources/Armor2/2a.png","resources/Armor2/2b.png",1,100,75);
    armor leather("resources/Armor3/3a.png","resources/Armor3/3b.png",1.25,75,75);
    display playerHUD("resources/Display1.png","resources/Display2.png","resources/Display3.png","resources/Display4.png",192,192,192,sx,sy,0.5);
    basicChar player(100,0,255,0,sx,sy);
    vector<basicChar> enemies;
    //enemy spawning (just for tests)
    basicChar temp(100,255,0,0,0,0);
    sword.apply(&player);
    chain.apply(&player);
    axe.apply(&temp);
    plate.apply(&temp);
    for(int i = 0; i < 1; i++) {
        temp.body.setPosition(i*-25,i*-25);
        temp.weapon.setPosition(i*-25,i*-25);
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
            //armor swapping (temporary, will be swapped for inventory system later)
            if (event.type == sf::Event::KeyPressed) {
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
        }
        }
        //movement
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
                enemies[i].weapon.move(xM,0);
                enemies[i].hpBar.move(xM,0);
                enemies[i].hpBarBack.move(xM,0);
            }
            if(enemies[i].objCollisions(0,yM,level,tL,objs,1) == false) {
                enemies[i].body.move(0,yM);
                enemies[i].weapon.move(0,yM);
                enemies[i].hpBar.move(0,yM);
                enemies[i].hpBarBack.move(0,yM);
            }
            if(enemies[i].hp <= 0) {
                enemies.erase(enemies.begin()+i);
                enemyCount--;
                //respawning code (just for tests)
                temp.body.setPosition(0,0);
                temp.weapon.setPosition(0,0);
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
            player.weapon.setPosition(sx,sy);
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
        window.clear(sf::Color(255,255,255));

        window.draw(map);
        for(int i = 0; i < enemyCount; i++) {
            window.draw(enemies[i].weapon);
            window.draw(enemies[i].body);
            window.draw(enemies[i].hpBarBack);
            window.draw(enemies[i].hpBar);
        }
        window.draw(player.weapon);
        window.draw(player.body);
        window.draw(playerHUD.display2);
        window.draw(playerHUD.display3);
        window.draw(playerHUD.display4);
        window.draw(playerHUD.block1);
        window.draw(playerHUD.block2);
        window.draw(playerHUD.block3);
        window.draw(playerHUD.display1);

        window.display();
        }
    }
    return 0;
}