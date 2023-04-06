#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Projectile_ennemi {
public:
    Projectile_ennemi(float xOrigin, float yOrigin, float xTarget, float yTarget, int vitesse, Sprite projectileSprite);
    void update(RenderWindow& window);
    bool isAlive(RenderWindow& window);
    bool hit(Perso& p1);
    Sprite projectileSprite;

private:
    float xOrigin;
    float yOrigin;
    int vitesse;
    float xDeplacement;
    float yDeplacement;
    float ecartX;
    float ecartY;
    float partieDecimaleX;
    float partieDecimaleY;
    float correctionX;
    float correctionY;
};