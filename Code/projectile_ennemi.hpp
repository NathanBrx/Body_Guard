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
    double xDeplacement;
    double yDeplacement;
    double ecartX;
    double ecartY;
    double partieDecimaleX;
    double partieDecimaleY;
    double correctionX;
    double correctionY;
};