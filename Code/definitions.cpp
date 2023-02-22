#include "mainheader.hpp"
#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace sf;

Perso::Perso(float x,float y,float rotation,int pvmax,int speed,int atk,Sprite persoSprite) : 
    x(x), y(y), rotation(rotation), pvmax(pvmax), speed(speed), atk(atk), persoSprite(persoSprite)
{
    persoSprite.setPosition(x,y);
}

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
void Perso::update(float x,float y,RenderWindow& window){
    if (x<0) x=0;
    if (x>(int)window.getSize().x) x=window.getSize().x;
    if (y<0) y=0;
    if (y>(int)window.getSize().y) y=window.getSize().y;
    else this->persoSprite.setPosition(x,y);
}
Projectile::Projectile(float xOrigin,float yOrigin,float direction,int vitesse,Sprite projectileSprite):
   xOrigin(xOrigin),yOrigin(yOrigin),direction(direction),vitesse(vitesse),projectileSprite(projectileSprite)
{
    this->projectileSprite.setPosition(xOrigin,yOrigin);
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
void tirer(vector<Projectile*>& projectiles,Perso& A,Sprite projectile1,float rotation){
    float x = A.GetX();
    float y = A.GetY();
    projectiles.push_back(new Projectile(x,y,rotation,A.GetSpeed(),projectile1));
}