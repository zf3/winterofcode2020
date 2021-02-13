#include<weapon.hpp>
#include<armor.hpp>
class inventorySlot;
class floorItem {
    public:
    weapon w;
    armor a;
    int type;
    bool active;
    float x, y;
    sf::Texture fIcon;
    //type = 1 - weapon, type = 2 - armor
    void include(basicChar *obj, float xP, float yP);
    void apply(inventorySlot *target);
    floorItem();
};