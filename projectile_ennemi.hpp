#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Projectile_ennemi {
    private:
        float xOrigin;
        float yOrigin;
        int vitesse;
        int damage;
        double xDeplacement;
        double yDeplacement;
        double ecartX;
        double ecartY;
        double partieDecimaleX;
        double partieDecimaleY;
        double correctionX;
        double correctionY;

    public:
        Projectile_ennemi(float xOrigin, float yOrigin, float xTarget, float yTarget, int vitesse, int damage, Sprite projectileSprite);
        void update(RenderWindow& window);
        bool isAlive(RenderWindow& window);
        bool hit(Perso& p1);
        int GetDamage();
        Sprite projectileSprite;
};