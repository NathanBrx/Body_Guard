#include "mainheader.hpp"

Projectile::Projectile(float xOrigin, float yOrigin, float direction, int vitesse, Sprite projectileSprite) :
    xOrigin(xOrigin), yOrigin(yOrigin), direction(direction), vitesse(vitesse), projectileSprite(projectileSprite)
{
    this->projectileSprite.setPosition(xOrigin, yOrigin);
    this->projectileSprite.setRotation(direction);
    this->projectileSprite.setOrigin(this->projectileSprite.getGlobalBounds().width / 2, this->projectileSprite.getGlobalBounds().height / 2);
}

// Getters

float Projectile::GetDirection() {
    return this->projectileSprite.getRotation();
}

// Setters

void Projectile::SetDirection(float direction) {
    this->projectileSprite.setRotation(direction);
}
void Projectile::SetVitesse(int vitesse) {
    this->vitesse = vitesse;
}

// Methodes

void Projectile::update(Projectile& projectile, Perso& A, RenderWindow& window, float direction) {
    switch ((int)direction) {
    case 270: projectile.projectileSprite.move(0.f, -(float)A.GetatkSpeed()); break;
    case 90: projectile.projectileSprite.move(0.f, (float)A.GetatkSpeed()); break;
    case 180: projectile.projectileSprite.move(-(float)A.GetatkSpeed(), 0.f); break;
    case 0: projectile.projectileSprite.move((float)A.GetatkSpeed(), 0.f); break;
    default: break;
    }
}

bool Projectile::isAlive(Projectile& projectile, RenderWindow& window) {
    if (projectile.projectileSprite.getPosition().y < 0 || projectile.projectileSprite.getPosition().y > window.getSize().y || projectile.projectileSprite.getPosition().x < 0 || projectile.projectileSprite.getPosition().x > window.getSize().x) {
        return false;
    }
    else {
        return true;
    }
}

bool Projectile::hit(Perso& p1) {
    if (this->projectileSprite.getGlobalBounds().intersects(p1.persoSprite.getGlobalBounds())) {
        return true;
    }
    else {
        return false;
    }
}
