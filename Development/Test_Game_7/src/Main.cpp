#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
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
    sf::Texture bodyT;
    sf::Sprite body;
    bullet(string t1, int x, int y, int xVe, int yVe) {
        xV = xVe;
        yV = yVe;
        bodyT.loadFromFile(t1);
        body.setTexture(bodyT);
        body.setOrigin(7,14);
        body.setPosition(x,y);
    }
};
class plane {
    public:
    float speed;
    sf::Texture bodyT;
    sf::Sprite body;
    sf::Time shotT;
    sf::Clock shotC;
    float shotCooldown;
    float shotSpeed;
    int shotAmn;
    vector<bullet> shots;
    string shotTexture;
    void shoot() {
        float ang = (body.getRotation()-90)/180*pi;
        shots.push_back(bullet(shotTexture,body.getPosition().x, body.getPosition().y,shotSpeed*cos(ang),shotSpeed*sin(ang)));
        shots[shotAmn].body.setRotation(body.getRotation());
        shotAmn++;
    }
    plane(string t1, string t2, float spd, int x, int y, float shotM, int shotS) {
        speed = spd;
        bodyT.loadFromFile(t1);
        shotTexture = t2;
        bodyT.setSmooth(true);
        body.setTexture(bodyT);
        body.setOrigin(290,220);
        body.setScale(0.25,0.25);
        body.setPosition(x,y);
        shotAmn = 0;
        shotSpeed = shotS;
        shotCooldown = shotM;
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(w,h), "Tilemap");
    sf::View view1(sf::FloatRect(0.f, 0.f, 1500.f, 1500.f));
    window.setFramerateLimit(60);
    const int level[] =
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };
    TileMap map;
    if (!map.load("resources/grass.png", sf::Vector2u(100, 100), level, 32, 32)) return -1;
    plane player("resources/player.png", "resources/shot.png", 2000, 750, 750, 0.2, 3000);
    sf::Time deltaTimeT;
    sf::Clock deltaTimeC;
    float deltaTime, xV = 0, yV = 0, frict = 0.15;
    bool mouseButton = false, shootA = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                mouseButton = true;
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                mouseButton = false;
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                shootA = true;
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
                shootA = false;
            }
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        //bullet shooting
        player.shotT = player.shotC.getElapsedTime();
        if(shootA == true && player.shotT.asSeconds() >= player.shotCooldown) {
            player.shoot();
            player.shotC.restart();
        }
        //deltaTime
        deltaTimeT = deltaTimeC.getElapsedTime();
        deltaTime = deltaTimeT.asSeconds();
        deltaTimeC.restart();
        //bullet AI
        for(int i = 0; i < player.shotAmn; i++) {
            player.shots[i].body.move(player.shots[i].xV*deltaTime,player.shots[i].yV*deltaTime);
        }
        //player AI
        player.body.move(xV*deltaTime,yV*deltaTime);
        view1.move(xV*deltaTime,yV*deltaTime);
        window.setView(view1);
        float mx = sf::Mouse::getPosition(window).x;
        float my = sf::Mouse::getPosition(window).y;
        float px = player.body.getPosition().x;
        float py = player.body.getPosition().y;
        float angle = atan2(my-py+(view1.getCenter().y-h/2),mx-px+(view1.getCenter().x-w/2))*180/pi;
        player.body.setRotation(angle+90);
        if(mouseButton == true) {
            xV+=deltaTime*player.speed*cos(angle/180*pi);
            yV+=deltaTime*player.speed*sin(angle/180*pi);
        }
        xV=xV*powf(frict,deltaTime);
        yV=yV*powf(frict,deltaTime);
        //rendering
        window.clear(sf::Color(192,192,192));
        window.draw(map);
        for(int i = 0; i < player.shotAmn; i++) {
            player.shots[i].body.setTexture(player.shots[i].bodyT);
            window.draw(player.shots[i].body);
        }
        window.draw(player.body);
        window.display();
    }
    return 0;
}