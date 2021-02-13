#include "weapon.hpp"
#include "armor.hpp"
class inventorySlot {
    public:
    weapon w;
    armor a;
    int type;
    bool active;
    //type = 1 - weapon, type = 2 - armor
    void include(weapon obj);
    void include(armor obj);
    void apply(basicChar *target);
    inventorySlot();
};