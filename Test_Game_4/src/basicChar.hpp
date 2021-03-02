#ifndef basicChar_h
#define basicChar_h

#include <vector>

#include "display.hpp"
#include "armor.hpp"
#include "weapon.hpp"

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
    float weaponM;
    float armorM;
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
    sf::Vector2f tipPosA[7];
    sf::Vector2f tipPos2A[20];
    sf::Vector2f tipPosB[7];
    sf::Vector2f tipPos2B[20];
    int totalCycles;
    int totalCycles2;
    sf::Sprite body;
    sf::Sprite heldWeapon;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarBack;
    sf::Texture bTexture;
    sf::Texture bTexture2;
    sf::Texture wTexture;
    sf::Texture fIconA;
    sf::Texture fIconW;
    weapon eqpWeapon;
    armor eqpArmor;
    //wall collision detection
    bool objCollisions(float xM, float yM, const int *tilemap, int xL, int *objs, int n);
    //animation cycles
    void basicCollisionDetection (basicChar *target);
    void loadAnim(int enemyCount, std::vector<basicChar> &enemies);
    void basicCollisionDetection2 (basicChar *target);
    void loadAnim2(int enemyCount, std::vector<basicChar> &enemies, float deltaTime, sf::View *gameView, sf::RenderWindow *window, const int *tilemap,int xL,int *objs, int n, display *playerHUD);
    void move(float x, float y);
    //constructor
    basicChar (int sp, int re,int gr,int bl,int x,int y);
};

#endif