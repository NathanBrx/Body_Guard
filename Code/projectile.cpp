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

void Projectile::update(RenderWindow& window) {
    switch ((int) this->direction) {
    case 270: this->projectileSprite.move(0.f, -(float)vitesse); break;
    case 90: this->projectileSprite.move(0.f, (float)vitesse); break;
    case 180: this->projectileSprite.move(-(float)vitesse, 0.f); break;
    case 0: this->projectileSprite.move((float)vitesse, 0.f); break;
    default: break;
    }
}

bool Projectile::isAlive(RenderWindow& window) {
    if (this->projectileSprite.getPosition().y < 0 || this->projectileSprite.getPosition().y > window.getSize().y || this->projectileSprite.getPosition().x < 0 || this->projectileSprite.getPosition().x > window.getSize().x) {
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
