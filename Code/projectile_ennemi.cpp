#include "mainheader.hpp"



Projectile_ennemi::Projectile_ennemi(float xOrigin, float yOrigin, float xTarget, float yTarget, int vitesse, int damage, Sprite projectileSprite) :
    xOrigin(xOrigin), yOrigin(yOrigin), vitesse(vitesse), damage(damage), projectileSprite(projectileSprite)
{
    double dx = xTarget - xOrigin;
    double dy = yTarget - yOrigin;
    double distance = sqrt(dx*dx + dy*dy);
    xDeplacement = vitesse * dx / distance;
    yDeplacement = vitesse * dy / distance;

    ecartX = 0;
    ecartY = 0;
    partieDecimaleX = xDeplacement - (int)xDeplacement;
    partieDecimaleY = yDeplacement - (int)yDeplacement;

    xDeplacement = (int)xDeplacement;
    yDeplacement = (int)yDeplacement;
    correctionX = 0;
    correctionY = 0;

    // Initialisation du sprite
    this->projectileSprite.setPosition(xOrigin, yOrigin);
    this->projectileSprite.setOrigin(this->projectileSprite.getGlobalBounds().width / 2, this->projectileSprite.getGlobalBounds().height / 2);
    this->projectileSprite.setRotation(atan2(yTarget - yOrigin, xTarget - xOrigin) * 180 / 3.141593);
}

void Projectile_ennemi::update(RenderWindow& window) {
    ecartX += partieDecimaleX;
    ecartY += partieDecimaleY;

    if (ecartX > 1) {
        correctionX = 1;
        ecartX -= 1;
    }
    else if (ecartX < -1) {
        correctionX = -1;
        ecartX += 1;
    }
    else {
        correctionX = 0;
    }

    if (ecartY > 1) {
        correctionY = 1;
        ecartY -= 1;
    }
    else if (ecartY < -1) {
        correctionY = -1;
        ecartY += 1;
    }
    else {
        correctionY = 0;
    }

    this->projectileSprite.move(xDeplacement + correctionX, yDeplacement + correctionY);
}

    bool Projectile_ennemi::isAlive(RenderWindow& window) {
        if (this->projectileSprite.getPosition().y < 0 || this->projectileSprite.getPosition().y > window.getSize().y || this->projectileSprite.getPosition().x < 0 || this->projectileSprite.getPosition().x > window.getSize().x) {
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

    int Projectile_ennemi::GetDamage() {
        return this->damage;
    }
