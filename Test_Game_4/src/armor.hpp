#ifndef armor_h
#define armor_h

class basicChar;

class armor {
    public:
    float spdM;
    int hitbox;
    float maxHP;
    sf::Texture icon;
    sf::Texture fIcon;
    sf::Texture description;
    sf::Texture bTexture;
    sf::Texture iTexture;
    void apply(basicChar *target);
    armor(std::string a, std::string b, std::string ic, std::string fic, std::string desc, float sp, float hp, float hb);
    armor();
};

#endif