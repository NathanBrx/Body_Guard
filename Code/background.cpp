#include "mainheader.hpp"

Background::Background(Sprite backgroundSprite) :
    backgroundSprite(backgroundSprite)
{
    this->portes =
    {sf::IntRect(890, 0, 180, 20),
    sf::IntRect(1900, 455, 20, 175),
    sf::IntRect(890, 1010, 235, 20),
    sf::IntRect(0, 400, 20, 240)};

    this->borduresPoints = 
    {{0, 390}, {78, 415}, {276, 279}, {400, 234},{730, 195},{815, 160}, {882, 66}, {890, 0}, {1070, 0}, {1280, 220},{1720, 148},{1840,400},{1920, 480},{1920, 660},{1136, 1080},{886, 1080},{0, 678}};

    this->isFlipX = false;
    this->isFlipY = false;
}

RectangleShape Background::CreateRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight)
{
    // Calculer la longueur et l'angle du rectangle
    float length = sqrt(pow(bottomRight.x - bottomLeft.x, 2) + pow(bottomRight.y - bottomLeft.y, 2));
    float angle = atan2(bottomRight.y - bottomLeft.y, bottomRight.x - bottomLeft.x);

    // Cr�er le rectangle
    RectangleShape rectangle;
    rectangle.setSize(Vector2f(length, 1.f));
    rectangle.setRotation(angle * 180.f / 3.14159f);

    // Positionner le rectangle en utilisant le coin inf�rieur gauche
    rectangle.setPosition(bottomLeft.x, bottomLeft.y - rectangle.getSize().y);

    return rectangle;
}

void Background::MakeRectangles() {
    for (size_t i = 0; i < this->borduresPoints.size() - 1; i += 1) {
        Vector2f bottomLeft = this->borduresPoints[i];
        Vector2f bottomRight = this->borduresPoints[i + 1];
        RectangleShape rectangle = this->CreateRectangle(bottomLeft, bottomRight);
        this->rectangles.push_back(rectangle);
    }
}

void Background::ChangeMap(int porteTouchee, Perso& A,RenderWindow& window,float ScaleX,float ScaleY){


    float moveXPerso;
    float moveYPerso;

    switch (porteTouchee)
    {
        case 0:

            moveXPerso = ((this->portes[2].left + this->portes[2].width/2)-A.GetX())/36;
            moveYPerso = ((this->portes[2].top + this->portes[2].height/2)-A.GetY())/36;

            // Animation de transition
            for(int i=0; i<36;i+=1){
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(0, 30));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(ScaleX,-ScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(ScaleX,ScaleY);
                A.persoSprite.move(sf::Vector2f(moveXPerso,moveYPerso));
                window.draw(A.persoSprite);
                window.display();
                usleep(1);
            }

            //A.SetX(this->portes[2].left + this->portes[2].width/2);
            //A.SetY(this->portes[2].top + this->portes[2].height/2);
            this->backgroundSprite.setScale(ScaleX,-ScaleY);
            this->isFlipX = !(this->isFlipX);
            break;

        case 1:
            MoveRight();
            break;
        case 2:
            MoveDown();
            break;
        case 3:
            MoveLeft();
            break;
        default:
            cerr << "Porte inexistante";
            break;
    }
}

void Background::MoveUp(Perso& A, RenderWindow& window,float ScaleX,float ScaleY){

    A.SetX(this->portes[2].left + this->portes[2].width/2);
    A.SetY(this->portes[2].top + this->portes[2].height/2);

    // Animation de transition
    for(int i; i<36;i+=1){
        window.clear();
        this->backgroundSprite.move(sf::Vector2f(0, 30));
        window.draw(this->backgroundSprite);
        //this->backgroundSprite.setScale(ScaleX,-ScaleY);
        //window.draw(this->backgroundSprite);
        //this->backgroundSprite.setScale(ScaleX,ScaleY);
        window.display();
        usleep(1);
    }

    this->backgroundSprite.setScale(ScaleX,-ScaleY);
    this->isFlipX = !(this->isFlipX);
}

void Background::MoveDown(){
    this->isFlipX = !(this->isFlipX);
}

void Background::MoveLeft(){
    this->isFlipY = !(this->isFlipY);
}

void Background::MoveRight(){
    this->isFlipY = !(this->isFlipY);
}