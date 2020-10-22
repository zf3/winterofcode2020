#include<SFML/Window.hpp>
#include<vector>
#include<cmath>
using namespace std;
int wallmap[1000][1000];
struct basicChar {
    sf::Sprite body;
    sf::Sprite weapon;
    float weaponLength;
    float damage;
    float attCooldown;
    float attCooldownMax;
    float hp;
    float sightRange;
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
        enemy->body.setRotation(atan((sY-tY)/(sX-tX))/3.1415*180);
        int xM = 10*(cos(enemy->body.getRotation()));
        int yM = 10*(sin(enemy->body.getRotation()));
        enemy->body.move(xM,yM);
    }
}
int main () {
    //definitions
    double speed = 100, deltaTime, playerAngle;
    sf::Time temp;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800,600), "Game window");
    sf::View gameView;
    sf::Sprite player;
    sf::Texture playerTexture;
    //setup
    playerTexture.loadFromFile("resources/playerTexture.png");
    player.setTexture(playerTexture);
    gameView.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
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
            player.move(0,-deltaTime*speed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0,deltaTime*speed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-deltaTime*speed,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(deltaTime*speed,0);
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        playerAngle = atan2(mousePos.y-player.getPosition().y,mousePos.x-player.getPosition().x)/3.1415*180;
        player.setRotation(playerAngle+90);
        //rendering
        window.clear(sf::Color::White);
        window.draw(player);
        window.display();
    }
    return 0;
}