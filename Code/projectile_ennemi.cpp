#include "mainheader.hpp"



Projectile_ennemi::Projectile_ennemi(float xOrigin, float yOrigin, float xTarget, float yTarget, int vitesse, Sprite projectileSprite) :
    xOrigin(xOrigin), yOrigin(yOrigin), vitesse(vitesse), projectileSprite(projectileSprite)
{
    // Calcul de l'angle
    if (xTarget == xOrigin) {
        xTarget = xTarget + 1;
    }
    if (yTarget == yOrigin) {
        yTarget = yTarget + 1;
    }
    float dx = xTarget - xOrigin;
    float dy = yTarget - yOrigin;
    float RatioXY=abs(dy/dx);

    xDeplacement=pow((pow(vitesse,2)/(1.0+pow(RatioXY,2))),0.5);
    yDeplacement=RatioXY*xDeplacement;
    if (dx<0) {
        xDeplacement=-xDeplacement;
    }
    if (dy<0) {
        yDeplacement=-yDeplacement;
    }
    ecartX = 0 ;// utilisé pour update, car le déplacement se fait avec un entier, on stock donc le déplacement non effectué (la partie décimale) pour l'effectuer quand la variable dépassera 1
    ecartY = 0 ;
    partieDecimaleX = xDeplacement - (int)xDeplacement; // calcul de la partie décimale
    partieDecimaleY = yDeplacement - (int)yDeplacement;

    xDeplacement = (int)xDeplacement;
    yDeplacement = (int)yDeplacement;
    correctionX=0;//utilisé pour update, quand ecartX dépasse 1, on met correctionX à 1, et on enlève 1 à ecartX. Le déplacement sera donc de xDeplacement+correctionX
    correctionY=0;


    // Initialisation du sprite
    this->projectileSprite.setPosition(xOrigin, yOrigin);
    this->projectileSprite.setOrigin(this->projectileSprite.getGlobalBounds().width / 2, this->projectileSprite.getGlobalBounds().height / 2);
}

void Projectile_ennemi::update(RenderWindow& window) {
    ecartX=ecartX+partieDecimaleX;
    ecartY=ecartY+partieDecimaleY;
    if (ecartX>1) {
        correctionX=1;
        ecartX=0;
    }
    else correctionX=0;


    if (ecartY>1){
        correctionY=1;
        ecartY=0;
    }
    else correctionY=0;

    if (ecartX<-1) {
        correctionX=-1;
        ecartX=0;
    }
    else correctionX=0;

    if (ecartY<-1){
        correctionY=-1;
        ecartY=0;
    }
    else correctionY=0;

    this->projectileSprite.move(xDeplacement+correctionX, yDeplacement+correctionY);
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
