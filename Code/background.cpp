#include "mainheader.hpp"

Background::Background(Sprite backgroundSprite,float ScaleX,float ScaleY) :
    backgroundSprite(backgroundSprite),ScaleX(ScaleX),ScaleY(ScaleY)
{
    this->portes =
    {
    sf::IntRect(0, 0, 1920*this->ScaleX, 20*this->ScaleY),
    sf::IntRect(1900*this->ScaleX, 0, 20*this->ScaleX, 1080*this->ScaleY),
    sf::IntRect(0, 1060*this->ScaleY, 1920*this->ScaleX, 20*this->ScaleY),
    sf::IntRect(0, 0, 20*this->ScaleX, 1080*this->ScaleY)
    };

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

void Background::ChangeMap(int porteTouchee, Perso& A,RenderWindow& window){


    float moveXPerso;
    float moveYPerso;

    switch (porteTouchee)
    {
        case 0:

            moveYPerso = ((this->portes[2].top - 35*this->ScaleY )-A.GetY())/36;
            // Animation de transition
            for(int i=0; i<36;i+=1){
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(0, 30*this->ScaleY));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(this->ScaleX,-(this->ScaleY));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                A.persoSprite.move(sf::Vector2f(0,moveYPerso));
                window.draw(A.persoSprite);
                window.display();
                usleep(1);
            }

            if(!(this->isFlipX)){
                this->backgroundSprite.setScale(this->ScaleX,-(this->ScaleY));
                this->backgroundSprite.setOrigin({0, this->backgroundSprite.getLocalBounds().height });
            }else{
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                this->backgroundSprite.setOrigin({0, 0});
            }
            this->backgroundSprite.setPosition(0,0);
            this->isFlipX = !(this->isFlipX);
            break;

        case 1:
            moveXPerso = ((this->portes[3].left - 35*this->ScaleX )-A.GetX())/36;
            // Animation de transition
            for(int i=0; i<36;i+=1){
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(-30*this->ScaleX, 0));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(-(this->ScaleX),this->ScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                A.persoSprite.move(sf::Vector2f(moveXPerso,0));
                window.draw(A.persoSprite);
                window.display();
                usleep(1);
            }

            if(!(this->isFlipY)){
                this->backgroundSprite.setScale(-(this->ScaleX),this->ScaleY);
                this->backgroundSprite.setOrigin({this->backgroundSprite.getLocalBounds().width, 0});
            }else{
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                this->backgroundSprite.setOrigin({0, 0});
            }
            this->backgroundSprite.setPosition(0,0);
            this->isFlipY = !(this->isFlipY);
            break;
        case 2:
            moveYPerso = ((this->portes[0].top + 35*this->ScaleY)-A.GetY())/36;
            // Animation de transition
            for(int i=0; i<36;i+=1){
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(0, -30*this->ScaleY));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(this->ScaleX,-(this->ScaleY));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                A.persoSprite.move(sf::Vector2f(0,moveYPerso));
                window.draw(A.persoSprite);
                window.display();
                usleep(1);
            }

            if(!(this->isFlipX)){
                this->backgroundSprite.setScale(-(this->ScaleX),this->ScaleY);
                this->backgroundSprite.setOrigin({this->backgroundSprite.getLocalBounds().width, 0});
            }else{
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                this->backgroundSprite.setOrigin({0, 0});
            }
            this->backgroundSprite.setPosition(0,0);
            this->isFlipX = !(this->isFlipX);
            break;

        case 3:
            moveXPerso = ((this->portes[1].left + 35*this->ScaleX)-A.GetX())/36;
            // Animation de transition
            for(int i=0; i<36;i+=1){
                window.clear();
                this->backgroundSprite.move(sf::Vector2f(-30*this->ScaleX, 0));
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(-(this->ScaleX),this->ScaleY);
                window.draw(this->backgroundSprite);
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                A.persoSprite.move(sf::Vector2f(moveXPerso,0));
                window.draw(A.persoSprite);
                window.display();
                usleep(1);
            }

            if(!(this->isFlipY)){
                this->backgroundSprite.setScale(-(this->ScaleX),this->ScaleY);
                this->backgroundSprite.setOrigin({this->backgroundSprite.getLocalBounds().width, 0});
            }else{
                this->backgroundSprite.setScale(this->ScaleX,this->ScaleY);
                this->backgroundSprite.setOrigin({0, 0});
            }
            this->backgroundSprite.setPosition(0,0);
            this->isFlipY = !(this->isFlipY);
            break;

        default:
            cerr << "Porte inexistante";
            break;
    }
}