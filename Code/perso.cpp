#include "mainheader.hpp"

Perso::Perso(float xOrigin, float yOrigin, float rotation, int pvmax, int speed, int atk, int atkSpeed, Sprite persoSprite) :
    xOrigin(xOrigin), yOrigin(yOrigin), rotation(rotation), pvmax(pvmax), speed(speed), atk(atk), atkSpeed(atkSpeed), persoSprite(persoSprite)
{
    this->persoSprite.setOrigin(persoSprite.getTexture()->getSize().x / 2, persoSprite.getTexture()->getSize().y / 2);
    this->persoSprite.setPosition(xOrigin,yOrigin);
    this->shoot_delay = sf::milliseconds(500);
}

// Getters

sf::Time Perso::GetDelay(){
   return this->shoot_delay;
}
float Perso::GetX() {
    return this->persoSprite.getPosition().x;
}
float Perso::GetY() {
    return this->persoSprite.getPosition().y;
}
int Perso::GetSpeed() {
    return this->speed;
}
int Perso::Getatk() {
    return this->atk;
}
int Perso::Getpv() {
    return this->pv;
}
int Perso::Getpvmax() {
    return this->pvmax;
}
int Perso::GetatkSpeed() {
    return this->atkSpeed;
}
float Perso::GetRotation() {
    return this->rotation;
}

// Setters

void Perso::Reset(){
    this->pv = pvmax;
    this->persoSprite.setPosition(xOrigin, yOrigin);
    this->alive = 1;
}
void Perso::SetX(float x) {
    this->persoSprite.setPosition(x, this->GetY());
}
void Perso::SetY(float y) {
    this->persoSprite.setPosition(this->GetX(), y);
}
void Perso::SetSpeed(int speed) {
    this->speed = speed;
}
void Perso::SetatkSpeed(int atkSpeed) {
    this->atkSpeed = atkSpeed;
}
void Perso::Setatk(int atk){
    this->atk = atk;
}
void Perso::SetRotation(float rotation) {
    this->rotation = rotation;
}
void Perso::Setpvdamage(int diffpv) {
    this->pv -= diffpv;
    if (this->pv <= 0) {
        this->alive = 0;
    }
}
void Perso::SetPV(int pv){
    this->pv = pv;
}
void Perso::SetDelay(sf::Time shoot_delay){
    this->shoot_delay = shoot_delay;
}

// Methodes

bool Perso::checkAlive() {
    return this->alive;
}
void Perso::update(bool upFlag, bool downFlag, bool leftFlag, bool rightFlag, RenderWindow& window) {
    float x = this->GetX(), y = this->GetY();
    speed = this->GetSpeed();
    if (leftFlag) x -= speed;
    if (rightFlag) x += speed;
    if (upFlag) y -= speed;
    if (downFlag) y += speed;
    this->SetX(x);
    this->SetY(y);
}
void Perso::isInWindow(RenderWindow& window) {
    if (this->GetX() < 0) this->SetX(0);
    if (this->GetX() > (int)window.getSize().x) this->SetX(window.getSize().x);
    if (this->GetY() < 0) this->SetY(0);
    if (this->GetY() > (int)window.getSize().y) this->SetY(window.getSize().y);
}

void Perso::damage(Texture& texturehit, Texture& texturebase, RenderWindow& window) {
    int compteur = 0;
    this->persoSprite.setTexture(texturehit);
    window.draw(this->persoSprite);
    while (compteur < 100) {
        compteur++;
    }
    this->persoSprite.setTexture(texturebase);
}

//Destructeur
Perso::~Perso() {}

