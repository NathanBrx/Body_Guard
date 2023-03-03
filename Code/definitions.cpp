#include "mainheader.hpp"
using namespace sf;

Perso::Perso(float xOrigin,float yOrigin,float rotation,int pvmax,int speed,int atk,int atkSpeed,Sprite persoSprite) : 
    xOrigin(xOrigin),yOrigin(yOrigin), rotation(rotation), pvmax(pvmax), speed(speed), atk(atk), atkSpeed(atkSpeed),persoSprite(persoSprite)
{
    this->persoSprite.setOrigin(50,50);
    this->persoSprite.setPosition(xOrigin,yOrigin);
}

// Getters

float Perso::GetX(){
    return this->persoSprite.getPosition().x;
}
float Perso::GetY(){
    return this->persoSprite.getPosition().y;
}
int Perso::GetSpeed(){
    return this->speed;
}
int Perso::Getatk(){
    return this->atk;
}
int Perso::Getpv(){
    return this->pv;
}
int Perso::GetatkSpeed(){
    return this->atkSpeed;
}
float Perso::GetRotation(){
    return this->persoSprite.getRotation();
}

// Setters

void Perso::SetX(float x){
    this->persoSprite.setPosition(x,this->GetY());
}
void Perso::SetY(float y){
    this->persoSprite.setPosition(this->GetX(),y);
}
void Perso::SetSpeed(int speed){
    this->speed = speed;
}
void Perso::SetatkSpeed(int atkSpeed){
    this->atkSpeed = atkSpeed;
}
void Perso::SetRotation(float rotation){
    this->persoSprite.setRotation(rotation);
}
void Perso::Setpv(int diffpv){
    this->pv -= diffpv;
    if (this->pv <= 0){
        this->alive = 0;
    }
}

// Methodes

void Perso::damage_taken(int atk){
    this-> pv = pv-atk;
}
bool Perso::checkAlive(){
    return this->alive;
}
void Perso::update(bool upFlag,bool downFlag,bool leftFlag,bool rightFlag,RenderWindow& window){
    float x = this->GetX(), y = this->GetY();
    speed = this->GetSpeed();
    if (leftFlag) x-=speed;
    if (rightFlag) x+=speed;
    if (upFlag) y-=speed;
    if (downFlag) y+=speed;
    this->SetX(x);
    this->SetY(y);
}
void Perso::isInWindow(RenderWindow& window){
    if (this->GetX()<0) this->SetX(0);
    if (this->GetX()>(int)window.getSize().x) this->SetX(window.getSize().x);
    if (this->GetY()<0) this->SetY(0);
    if (this->GetY()>(int)window.getSize().y) this->SetY(window.getSize().y);
}

Projectile::Projectile(float xOrigin,float yOrigin,float direction,int vitesse,Sprite projectileSprite):
   xOrigin(xOrigin),yOrigin(yOrigin),direction(direction),vitesse(vitesse),projectileSprite(projectileSprite)
{
    this->projectileSprite.setPosition(xOrigin,yOrigin);
    this->projectileSprite.setRotation(direction);
    this->projectileSprite.setOrigin(this->projectileSprite.getGlobalBounds().width/2,this->projectileSprite.getGlobalBounds().height/2);
}

// Getters

float Projectile::GetDirection(){
    return this->projectileSprite.getRotation();
}

// Setters

void Projectile::SetDirection(float direction){
    this->projectileSprite.setRotation(direction);
}
void Projectile::SetVitesse(int vitesse){
    this->vitesse = vitesse;
}

// Methodes

void Projectile::update(Projectile& projectile,Perso& A,RenderWindow& window,float direction){
    switch ((int)direction){
        case 270 : projectile.projectileSprite.move(0.f,-(float)A.GetatkSpeed()); break;
        case 90 : projectile.projectileSprite.move(0.f,(float)A.GetatkSpeed()); break;
        case 180 : projectile.projectileSprite.move(-(float)A.GetatkSpeed(),0.f); break;
        case 0 : projectile.projectileSprite.move((float)A.GetatkSpeed(),0.f); break;
        default : break;
    }
}

bool Projectile::isAlive(Projectile& projectile,RenderWindow& window){
    if (projectile.projectileSprite.getPosition().y < 0 || projectile.projectileSprite.getPosition().y > window.getSize().y || projectile.projectileSprite.getPosition().x < 0 || projectile.projectileSprite.getPosition().x > window.getSize().x){
        return false;
    }
    else{
        return true;
    }
}

bool Projectile::hit(Perso& p1){
    if (this->projectileSprite.getGlobalBounds().intersects(p1.persoSprite.getGlobalBounds())){
        return true;
    }
    else{
        return false;
    }
}

void tirer(vector<Projectile*>& projectiles,Perso& A,Sprite projectile1,float direction){
    float x = A.GetX();
    float y = A.GetY();
    projectiles.push_back(new Projectile(x,y,direction,A.GetatkSpeed(),projectile1));
}