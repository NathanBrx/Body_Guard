#include "mainheader.hpp"
#include <iostream>
#include <SFML/System/String.hpp>
using namespace sf;
using namespace std;

Perso::Perso(float xOrigin,float yOrigin,float rotation,int pvmax,int speed,int atk,int atkSpeed,Sprite persoSprite) : 
    xOrigin(xOrigin),yOrigin(yOrigin), rotation(rotation), pvmax(pvmax), speed(speed), atk(atk), atkSpeed(atkSpeed),persoSprite(persoSprite)
{   
    this->hitbox=persoSprite.getGlobalBounds();
    this->persoSprite.setOrigin(persoSprite.getGlobalBounds().width/2,persoSprite.getGlobalBounds().height/2);
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

// Methodes

void Perso::damage_taken(int atk){
    this-> pv = pv-atk;
}
void Perso::checkAlive(){
    if(this->pv <= 0){
        this->alive = 0;
    }
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

void tirer(vector<Projectile*>& projectiles,Perso& A,Sprite projectile1,float direction){
    float x = A.GetX();
    float y = A.GetY();
    projectiles.push_back(new Projectile(x,y,direction,A.GetatkSpeed(),projectile1));
}

//Background

Background::Background(Sprite backgroundSprite,string backgroundImage ,std::vector<sf::Vector2f> borduresPoints):
    backgroundSprite(backgroundSprite), backgroundImage(backgroundImage), borduresPoints(borduresPoints)
{}

sf::RectangleShape Background::CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight)
{
    // Calculer la longueur et l'angle du rectangle
    float length = std::sqrt(std::pow(bottomRight.x - bottomLeft.x, 2) + std::pow(bottomRight.y - bottomLeft.y, 2));
    float angle = std::atan2(bottomRight.y - bottomLeft.y, bottomRight.x - bottomLeft.x);

    // Créer le rectangle
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(length, 1.f));
    rectangle.setRotation(angle * 180.f / 3.14159f);

    // Positionner le rectangle en utilisant le coin inférieur gauche
    rectangle.setPosition(bottomLeft.x, bottomLeft.y - rectangle.getSize().y);

    return rectangle;
}

void Background::MakeRectangles(){
    for(std::size_t i = 0; i < this->borduresPoints.size() - 1; i += 1){
        sf::Vector2f bottomLeft = this->borduresPoints[i];
        sf::Vector2f bottomRight = this->borduresPoints[i + 1];
        sf::RectangleShape rectangle = this->CreateRectangle(bottomLeft, bottomRight);
        this->rectangles.push_back(rectangle);
    }
}


void Background::SetBackground(){ // Met l'image de background dans la texture
    if (!this->backgroundTexture.loadFromFile(this->backgroundImage)){
        cerr << "failed to load map texture" << endl;
        exit(1);
    }
}

void Background::SetTexture(float ScaleX, float ScaleY){ //Met la texture dans le sprite
    this->backgroundSprite.setTexture(this->backgroundTexture); // Set textures
    this->backgroundSprite.setScale(ScaleX, ScaleY);    // Set scales
    this->backgroundTexture.setRepeated(false);
}