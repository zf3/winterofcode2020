#include<SFML/Window.hpp>
#include<vector>
#include<cmath>
using namespace std;
int wallmap[1000][1000];
double deltaTime;
struct basicChar {
    sf::Sprite body;
    sf::Sprite weapon;
    float weaponLength;
    float damage;
    float attCooldown;
    float attCooldownMax;
    float hp;
    float sightRange;
    float speed;
};
bool isSeen(basicChar *target, basicChar *spotter) {
    float sX = spotter->body.getPosition().x;
    float sY = spotter->body.getPosition().y;
    float tX = target->body.getPosition().x;
    float tY = target->body.getPosition().y;
    if(sqrt((sX-tX)*(sX-tX)+(sY-tY)*(sY-tY)) <= spotter->sightRange) {
        if(sX == tX) {
            for(int i = min(floor(sY/10)*10,floor(tY/10)*10); i <= max(floor(sY/10)*10,floor(tY/10)*10); i+=10) {
                int temp = sX;
                if(wallmap[temp/10][i/10] > 0) {
                    return false;
                }
            }
            return true;
        }
        for(int i = min(floor(sX/10)*10,floor(tX/10)*10); i <= max(floor(sX/10)*10,floor(tX/10)*10); i+=10) {
            int checkY = floor(((tY-sY)/(tX-sX)*(i-sX)+sY)/10);
            if(checkY >= 0 && wallmap[i/10][checkY] > 0) {
                return false;
            }
        }
        return true;
    };
    return false;
};
void enemyAI(basicChar *target, basicChar *enemy) {
    float sX = enemy->body.getPosition().x;
    float sY = enemy->body.getPosition().y;
    float tX = target->body.getPosition().x;
    float tY = target->body.getPosition().y;
    if(isSeen(target,enemy) == true && ((sX-tX)*(sX-tX)+(sY-tY)*(sY-tY)) >= 10) {
        enemy->body.setRotation(atan((sY-tY)/(sX-tX))/3.1415*180+90);
        enemy->weapon.setRotation(atan((sY-tY)/(sX-tX))/3.1415*180+90);
        float xM = deltaTime*enemy->speed*cos(enemy->body.getRotation()-90);
        float yM = deltaTime*enemy->speed*sin(enemy->body.getRotation()-90);
        enemy->body.move(xM,yM);
        enemy->weapon.move(xM,yM);
    }
}
int main () {
    //definitions
    int enemyCount = 0;
    basicChar player, temp2;
    vector<basicChar> enemies;
    sf::Time temp;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800,600), "Game window");
    sf::View gameView;
    sf::Texture playerTexture;
    sf::Texture weaponTexture;
    //setup
    playerTexture.loadFromFile("resources/playerTexture.png");
    weaponTexture.loadFromFile("resources/weaponTexture.png");
    player.speed = 100;
    player.body.setTexture(playerTexture);
    player.weapon.setTexture(weaponTexture);
    player.body.setOrigin(100,100);
    player.weapon.setOrigin(100,100);
    player.body.setPosition(400,300);
    player.weapon.setPosition(400,300);
    gameView.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    temp2.speed = 100;
    temp2.body.setTexture(playerTexture);
    temp2.weapon.setTexture(weaponTexture);
    temp2.body.setOrigin(100,100);
    temp2.weapon.setOrigin(100,100);
    temp2.sightRange = 1000;
    enemies.push_back(temp2);
    enemyCount++;
    while(window.isOpen()) {
        //special events
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        //player movement and direction
        temp = clock.getElapsedTime();
        clock.restart();
        deltaTime = temp.asSeconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.body.move(0,-deltaTime*player.speed);
            player.weapon.move(0,-deltaTime*player.speed);
            gameView.move(0,-deltaTime*player.speed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.body.move(0,deltaTime*player.speed);
            player.weapon.move(0,deltaTime*player.speed);
            gameView.move(0,deltaTime*player.speed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.body.move(-deltaTime*player.speed,0);
            player.weapon.move(-deltaTime*player.speed,0);
            gameView.move(-deltaTime*player.speed,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.body.move(deltaTime*player.speed,0);
            player.weapon.move(deltaTime*player.speed,0);
            gameView.move(deltaTime*player.speed,0);
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        player.body.setRotation(atan2(mousePos.y-player.body.getPosition().y,mousePos.x-player.body.getPosition().x)/3.1415*180+90);
        player.weapon.setRotation(atan2(mousePos.y-player.body.getPosition().y,mousePos.x-player.body.getPosition().x)/3.1415*180+90);
        //rendering
        window.clear(sf::Color::White);
        for(int i = 0; i < enemyCount; i++) {
            enemyAI(&player,&enemies[i]);
            window.draw(enemies[i].body);
            window.draw(enemies[i].weapon);
        }
        window.draw(player.body);
        window.draw(player.weapon);
        window.display();
    }
    return 0;
}