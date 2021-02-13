#ifndef display_h
#define display_h

#include <string>

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
    void renew(float wC, float wCM, float wC2, float wCM2, float hp, float mHP);
    void move(float x, float y) ;
    display(std::string a, std::string b, std::string c, std::string d, int re, int gr, int bl, int x, int y, float scl) ;
};

#endif