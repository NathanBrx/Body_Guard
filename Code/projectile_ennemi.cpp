#include "mainheader.hpp"



Projectile_ennemi::Projectile_ennemi(float xOrigin, float yOrigin, float xTarget, float yTarget, int vitesse, Sprite projectileSprite) :
    xOrigin(xOrigin), yOrigin(yOrigin), vitesse(vitesse), projectileSprite(projectileSprite)
{
    // Calcul de l'angle
    float dx = xTarget - xOrigin;
    float dy = yTarget - yOrigin;
    float rotation = (atan2(dx, dy) * 180 / M_PI);

    // Initialisation du sprite
    this->projectileSprite.setPosition(xOrigin, yOrigin);
    this->projectileSprite.setRotation(rotation);
    this->projectileSprite.setOrigin(this->projectileSprite.getGlobalBounds().width / 2, this->projectileSprite.getGlobalBounds().height / 2);
}

void Projectile_ennemi::update(RenderWindow& window) {

    // Calcul de l'angle
    float dx = this->projectileSprite.getPosition().x - this->xOrigin;
    float dy = this->projectileSprite.getPosition().y - this->yOrigin;
    this->rotation = atan2(dy, dx) * 180 / M_PI;

    // Déplacement du projectile dans la direction de l'angle
    float deltaX = cos(this->rotation * M_PI / 180) * this->vitesse;
    float deltaY = sin(this->rotation * M_PI / 180) * this->vitesse;
    this->projectileSprite.move(deltaX, deltaY);
}

bool Projectile_ennemi::isAlive(Projectile_ennemi& projectile, RenderWindow& window) {
    if (projectile.projectileSprite.getPosition().y < 0 || projectile.projectileSprite.getPosition().y > window.getSize().y || projectile.projectileSprite.getPosition().x < 0 || projectile.projectileSprite.getPosition().x > window.getSize().x) {
        return false;
    }
    else {
        return true;
    }
}

bool Projectile_ennemi::hit(Perso& p1) {
    if (this->projectileSprite.getGlobalBounds().intersects(p1.persoSprite.getGlobalBounds())) {
        return true;
    }
    else {
        return false;
    }
}
