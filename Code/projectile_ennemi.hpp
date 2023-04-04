#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Projectile_ennemi {
public:
    Projectile_ennemi(float xOrigin, float yOrigin, float xTarget, float yTarget, int vitesse, Sprite projectileSprite);
    void update(RenderWindow& window);
    bool isAlive(Projectile_ennemi& projectile, RenderWindow& window);
    bool hit(Perso& p1);
    Sprite projectileSprite;

private:
    float xOrigin;
    float yOrigin;
    int vitesse;
    float rotation;
};