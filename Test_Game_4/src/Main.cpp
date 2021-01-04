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
class basicChar {
    public:
    int spd;
    int atkAnimStage;
    int atkAnimStage2;
    int hitbox;
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
    sf::Texture atkAnims[3];
    sf::Texture atkAnims2[10];
    sf::Vector2f tipPos[3];
    sf::Vector2f tipPos2[10];
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
        int c1x = (px+(hitbox-1))/100, c1y = (py+(hitbox-1))/100;
        int c2x = (px-(hitbox-1))/100, c2y = (py+(hitbox-1))/100;
        int c3x = (px+(hitbox-1))/100, c3y = (py-(hitbox-1))/100;
        int c4x = (px-(hitbox-1))/100, c4y = (py-(hitbox-1))/100;
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
        float wx = bx+cos(br)*tipPos[atkAnimStage].x, wy = by+sin(br)*tipPos[atkAnimStage].y;
        if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= hitbox && target->damaged == false) {
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
            weapon.setOrigin(200,200);
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
        float wx = bx+cos(br)*tipPos2[atkAnimStage2].x, wy = by+sin(br)*tipPos2[atkAnimStage2].y;
        if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= hitbox && target->damaged == false) {
            target->hp-=dmg2;
            target->damaged = true;
            target->body.setTexture(target->bTexture2);
        }
    }
    void loadAnim2(int enemyCount, vector<basicChar> &enemies, float deltaTime, sf::View *gameView, sf::RenderWindow *window, const int *tilemap,int xL,int *objs, int n) {
        animTime2 = animClock2.getElapsedTime();
        float xM = deltaTime*atk2Spd*cos(body.getRotation()/180*PI);
        float yM = deltaTime*atk2Spd*sin(body.getRotation()/180*PI);
        if(objCollisions(xM,0,tilemap,xL,objs,n) == false) {
            body.move(xM,0);
            weapon.move(xM,0);
            hpBar.move(xM,0);
            hpBarBack.move(xM,0);
            gameView->move(xM,0);
            window->setView(*gameView);
        }
        if(objCollisions(0,yM,tilemap,xL,objs,n) == false) {
            body.move(0,yM);
            weapon.move(0,yM);
            hpBar.move(0,yM);
            hpBarBack.move(0,yM);
            gameView->move(0,yM);
            window->setView(*gameView);
        }
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
            weapon.setOrigin(200,200);
            for(int i = 0; i < enemyCount; i++) {
                enemies[i].damaged = false;
                enemies[i].body.setTexture(enemies[i].bTexture);
            }
        }
    }
    //constructor
    basicChar (string a, string b, int sp, int re,int gr,int bl,int x,int y, int hb, float h) {
        bTexture.loadFromFile(a);
        bTexture.setSmooth(true);
        bTexture2.loadFromFile(b);
        bTexture2.setSmooth(true);
        body.setOrigin(sf::Vector2f(200,200));
        body.setPosition(sf::Vector2f(x,y));
        body.setTexture(bTexture);
        weapon.setOrigin(sf::Vector2f(200,200));
        weapon.setPosition(sf::Vector2f(x,y));
        hitbox = hb;
        hp = h;
        maxHP = h;
        atkActive = false;
        atkActive2 = false;
        atkAnimStage = 0;
        atkAnimStage2 = 0;
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
    int spdM;
    float wCooldownM;
    float wCooldownM2;
    float dmg;
    float dmg2;
    float atkD;
    float atkD2;
    float atk2Spd;
    sf::Texture atkAnims[3];
    sf::Texture atkAnims2[10];
    sf::Vector2f tipPos[3];
    sf::Vector2f tipPos2[10];
    int totalCycles;
    int totalCycles2;
    sf::Texture wTexture;
    void apply(basicChar *target) {
        target->spd = target->spd*spdM;
        target->wCooldownM = wCooldownM;
        target->wCooldownM2 = wCooldownM2;
        target->dmg = dmg;
        target->dmg2 = dmg2;
        target->atkD = atkD;
        target->atkD2 = atkD2;
        target->atk2Spd = atk2Spd;
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
    weapon(string a, string *textures, string *textures2, sf::Vector2f *tPos, sf::Vector2f *tPos2, int n, int n2, int sp, float cM, float cM2, float dm, float dm2, float aD, float aD2, float a2S) {
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
    string arr[3] = {"resources/weaponTexture2.png","resources/weaponTexture3.png","resources/weaponTexture2.png"};
    sf::Vector2f tipPos[3] = {{sf::Vector2f(111,2)},{sf::Vector2f(106,65)},{sf::Vector2f(111,2)}};
    string arr2[10] = {"resources/weaponTexture4.png","resources/weaponTexture4.png","resources/weaponTexture4.png","resources/weaponTexture4.png","resources/weaponTexture4.png"
    ,"resources/weaponTexture4.png","resources/weaponTexture4.png","resources/weaponTexture4.png","resources/weaponTexture4.png","resources/weaponTexture4.png"};
    sf::Vector2f tipPos2[10] = {{sf::Vector2f(150,35)},{sf::Vector2f(150,35)},{sf::Vector2f(150,35)},{sf::Vector2f(150,35)},{sf::Vector2f(150,35)}
    ,{sf::Vector2f(150,35)},{sf::Vector2f(150,35)},{sf::Vector2f(150,35)},{sf::Vector2f(150,35)},{sf::Vector2f(150,35)}};
    weapon a("resources/weaponTexture.png",arr,arr2,tipPos,tipPos2,3,10,1,0.5,5,10,50,0.5,1,500);
    basicChar player("resources/playerTexture.png","resources/playerInjuredTexture.png",100,0,255,0,400,300,50,100);
    vector<basicChar> enemies;
    //enemy spawning (just for tests)
    basicChar temp("resources/enemyTexture.png","resources/enemyInjuredTexture.png",100,255,0,0,0,0,50,100);
    a.apply(&player);
    a.apply(&temp);
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
    if (!map.load("resources/Tileset.png", sf::Vector2u(100, 100), level, tL, tH))
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
        }
        }
        //movement
        {
        deltaClock.restart();
        if(player.atkActive2 == false) {
            if(status[sf::Keyboard::A] == true && player.objCollisions(deltaTime*-player.spd,0,level,tL,objs,1) == false) {
                player.body.move(sf::Vector2f(deltaTime*-player.spd,0));
                player.weapon.move(sf::Vector2f(deltaTime*-player.spd,0));
                player.hpBar.move(sf::Vector2f(deltaTime*-player.spd,0));
                player.hpBarBack.move(sf::Vector2f(deltaTime*-player.spd,0));
                gameView.move(sf::Vector2f(deltaTime*-player.spd,0));
                window.setView(gameView);
            }
            if(status[sf::Keyboard::D] == true && player.objCollisions(deltaTime*player.spd,0,level,tL,objs,1) == false) {
                player.body.move(sf::Vector2f(deltaTime*player.spd,0));
                player.weapon.move(sf::Vector2f(deltaTime*player.spd,0));
                player.hpBar.move(sf::Vector2f(deltaTime*player.spd,0));
                player.hpBarBack.move(sf::Vector2f(deltaTime*player.spd,0));
                gameView.move(sf::Vector2f(deltaTime*player.spd,0));
                window.setView(gameView);
            }
            if(status[sf::Keyboard::W] == true && player.objCollisions(0,deltaTime*-player.spd,level,tL,objs,1) == false) {
                player.body.move(sf::Vector2f(0,deltaTime*-player.spd));
                player.weapon.move(sf::Vector2f(0,deltaTime*-player.spd));
                player.hpBar.move(sf::Vector2f(0,deltaTime*-player.spd));
                player.hpBarBack.move(sf::Vector2f(0,deltaTime*-player.spd));
                gameView.move(sf::Vector2f(0,deltaTime*-player.spd));
                window.setView(gameView);
            }
            if(status[sf::Keyboard::S] == true && player.objCollisions(0,deltaTime*player.spd,level,tL,objs,1) == false) {
                player.body.move(sf::Vector2f(0,deltaTime*player.spd));
                player.weapon.move(sf::Vector2f(0,deltaTime*player.spd));
                player.hpBar.move(sf::Vector2f(0,deltaTime*player.spd));
                player.hpBarBack.move(sf::Vector2f(0,deltaTime*player.spd));
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
            player.loadAnim2(enemyCount, enemies,deltaTime,&gameView,&window,level,tL,objs,1);
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
                if(sqrtf(xD*xD+yD*yD) <= 125) {
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
            player.body.setPosition(400,300);
            player.weapon.setPosition(400,300);
            player.hp = player.maxHP;
            player.atkActive = false;
            player.atkAnimStage = 0;
            player.atkAnimStage2 = 0;
            player.hpBar.setPosition(400,300);
            player.hpBarBack.setPosition(400,300);
            gameView.setCenter(400,300);
        }
        }
        //hp bar setting
        {
        player.hpBar.setSize(sf::Vector2f(5,50*player.hp/player.maxHP));
        for(int i = 0; i < enemyCount; i++) {
            enemies[i].hpBar.setSize(sf::Vector2f(5,50*enemies[i].hp/enemies[i].maxHP));
        }
        }
        //drawing
        {
        window.clear(sf::Color(255,255,255));
        window.draw(map);
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

        window.display();
        }
    }
    return 0;
}