#include "mainheader.hpp"
#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace sf;

Perso::Perso(float x,float y,float rotation,int pvmax,int speed,int atk,Sprite persoSprite) : 
    x(x), y(y), rotation(rotation), pvmax(pvmax), speed(speed), atk(atk), persoSprite(persoSprite)
{}

void Perso::damage_taken(int atk){
    this-> pv = pv-atk;
}
void Perso::SetX(float x){
    this->x = x;
}
void Perso::SetY(float y){
    this->y = y;
}
float Perso::GetX(){
    return this->x;
}
float Perso::GetY(){
    return this->y;
}
float Perso::GetRotation(){
    return this->rotation;
}
int Perso::GetSpeed(){
    return this->speed;
}
void Perso::checkAlive(){
    if(this->pv <= 0){
        this->alive = 0;
    }
}
void Perso::speed_modif(int speed){
    this->speed = speed;
}

Projectile::Projectile(float xOrigin,float yOrigin,float direction,int vitesse,Sprite projectileSprite):
   xOrigin(xOrigin),yOrigin(yOrigin),direction(direction),vitesse(vitesse),projectileSprite(projectileSprite)
{
    projectileSprite.setPosition(xOrigin,yOrigin);
}
float Projectile::getDirection(){
    return this->direction;
}
void Projectile::setDirection(float direction){
    this->direction = direction;
}
void Projectile::setVitesse(int vitesse){
    this->vitesse = vitesse;
}
/*
void Projectile::tirer(){
    this->projectileSprite.move(0.f,5.f);
}
Vector2f Projectile::getPos(){
    return this->projectileSprite.getPosition();
}
*/